/*
	通信タスク
*/
#include <stdio.h>
#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include <ctype.h>
#include <string.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                // SYS function prototypes
#include "moni.h" 
#include "gpioexp.h" 
#include "rtc.h" 
#include "w25q128jv.h"
void DLCMatTimerInt();
void DLCMatState();
void command_main();
void _GO_IDLE(){	command_main();DLCMatState();SYS_Tasks();}
void Moni();
void DLCMatConfigDefault(),DLCMatStatusDefault(),DLCMatReortDefault();
void DLCMatPostConfig(),DLCMatPostStatus(),DLCMatPostReport();
void DLCMatTimerset(int tmid,int cnt );
void DLCMatWgetFile();	// fota FOTAファイルwget
extern	char s_command_version[];
int DLCMatRecvDisp();
int DLCMatRecvWriteFota();	// fota FOTAデータ書込み処理
char 	zLogOn=1;
char 	DLC_MatSleep;
char 	DLC_MatResBuf[2000];
int	 	DLC_MatResIdx;
uchar	DLC_MatLineBuf[4000];
int		DLC_MatLineIdx;
uchar	DLC_Matfact,DLC_MatState;
char	DLC_MatDateTime[32];
char	DLC_MatRadioDensty[64];
char	DLC_MatNUM[16];
char	DLC_MatIMEI[16];
int		DLC_MatTmid;
bool	DLC_MatFotaExe=false;	// fota FOTA実行フラグ
// bool	DLC_MatFotaExe=true;	// fota FOTA実行フラグ
bool	DLC_MatFotaWriteNG=false;	// fota FOTA書込みNGフラグ
int	 	DLC_MatSPIFlashAddrFota=0;	// fota SPIフラッシュ書込みアドレス(現状0)
// int	 	DLC_MatSPIFlashAddrFota=0xd60000;	// fota SPIフラッシュ書込みアドレス
int	 	DLC_MatSPIFlashPage=256;	// fota SPIフラッシュ1ページbyte数
int	 	DLC_MatSPIRemaindataFota;	// fota 1ページ未満の半端byte数→保持して次回書込み
int	 	DLC_MatSPIWritePageFota;	// fota SPI書込みページインデックス
char	DLC_MatSPIRemainbufFota[256];	// fota 1ページ未満の半端byte保持バッファ
char	DLC_MatSPICheckbufFota[256];	// fota ベリファイ用バッファ
static	char wget_Head[] = "GET /wpfm.bin HTTP/1.1\r\nHost:harvest-files.soracom.io\r\nUser-Agent: Wget\r\nConnection: close\r\n\r\n";	// fota FOTAデータ指定
// static char wget_Head[] = "GET /2048.bin HTTP/1.1\r\nHost:harvest-files.soracom.io\r\nUser-Agent: Wget\r\nConnection: close\r\n\r\n";	// fota
// static char wget_Head[] = "GET /256.bin HTTP/1.1\r\nHost:harvest-files.soracom.io\r\nUser-Agent: Wget\r\nConnection: close\r\n\r\n";	// fota

struct {
	int	cnt;
} DLC_MatTimer;
char getch()
{
	char	c;
	while(1){
		if( SERCOM0_USART_Read( (unsigned char*)&c,1 ) ){
			putch(c);
			return c;
		}
		_GO_IDLE();
	}
}
void putch( char c )
{
	while(1){
		if( SERCOM0_USART_Write( (unsigned char*)&c,1 ) == 1 )
			return;
	}
}
/* 
	Function:通信タスクの変数初期化、TC5(内部タイマー)のコールバック登録
*/
void DLCMatInit()
{
	DLCMatConfigDefault();
	DLCMatStatusDefault();
	DLCMatReortDefault();
	TC5_TimerCallbackRegister( (TC_TIMER_CALLBACK)DLCMatTimerInt, (uintptr_t)0 );
	TC5_TimerStart();
	DLCMatTimerset( 0,3000 );
}
/*
	Function:通信タスクにTO通知
*/
void DLCMatNoty(int tmid)
{
	DLC_MatTmid = tmid;
}
/*
	Function:通信タスクのTO通知の確認
*/
int	DLCMatTmChk(int tmid)
{
	if( DLC_MatTmid ){
		if( DLC_MatTimer.cnt == 0 ){
			DLC_MatTmid = 0;
			return 1;
		}
	}
	return 0;
}
void DLCMatTimerInt()
{
	if( DLC_MatTimer.cnt != 0 ){
		DLC_MatTimer.cnt--;
		if( DLC_MatTimer.cnt == 0 )
			DLCMatNoty(1);
//	putch('t');
	}
}
/*
	Function:通信タスクのタイマー登録
*/
void DLCMatTimerset(int tmid,int cnt )
{
	DLC_MatTimer.cnt = cnt;
}
void DLCMatTimerClr(int tmid )
{
	DLC_MatTimer.cnt = 0;
}
void DLCMatLog(int len)
{
	uchar	c;
	if( zLogOn ){
		for(int i=0;i<len;i++){
			c = DLC_MatLineBuf[DLC_MatLineIdx+i];
			putch( c );
			if( c == '\r')
				putch('\n');
		}
	}
}
void DLCMatSend( char *s )
{
	int i,sz,blk,rmn;
	sz = strlen( s );
	if( sz < 64 ){
		putst( s );putch('\n');
	}
	blk = sz/64;
	rmn = sz%64;
	for( i=0;i<blk;i++){
		SERCOM5_USART_Write( (uint8_t*)&s[i*64],64 );
		APP_delay(100);
	}
	if( rmn ){
		SERCOM5_USART_Write( (uint8_t*)&s[i*64],rmn );
	}
}
int	DLCMatCharInt( char *p,char *title )
{
	char	*q;
	int		len,wk=0;
	len = strlen(title);
	p = strstr( p,title );
	if( p ){
		if( p[len] == '-' ){															/* マイナス */
			q = strchr( p,'\r' );
			if( q ){
				str2int( &p[len+1],&wk );
				wk *= -1;
			}
		}
		else {
			q = strchr( p,'\r' );
			if( q ){
				str2int( &p[len+1],&wk );
			}
		}
	}
	return wk;
}
/* 要因 */
#define		MATC_FACT_RDY	0
#define		MATC_FACT_ERR	1
#define		MATC_FACT_VER	2
#define		MATC_FACT_NUM	3
#define		MATC_FACT_OK	4
#define		MATC_FACT_CON	5
#define		MATC_FACT_TIM	6
#define		MATC_FACT_RSR	7
#define		MATC_FACT_OPN	8
#define		MATC_FACT_CLS	9
#define		MATC_FACT_DATA	10
#define		MATC_FACT_DSC	11
#define		MATC_FACT_TO	12
#define		MATC_FACT_WUP	13
#define		MATC_FACT_FOTA	14
#define		MATC_FACT_FTP	15
#define		MATC_FACT_SLP	16
/* 状態 */
#define		MATC_STATE_INIT	0
#define		MATC_STATE_IDLE	1
#define		MATC_STATE_IMEI	2
#define		MATC_STATE_APN	3
#define		MATC_STATE_SVR	4
#define		MATC_STATE_CONG	5
#define		MATC_STATE_COND	6
#define		MATC_STATE_OPN1	7
#define		MATC_STATE_CNFG	8
#define		MATC_STATE_OPN2	9
#define		MATC_STATE_STAT	10
#define		MATC_STATE_OPN3	11
#define		MATC_STATE_RPT 	12
#define		MATC_STATE_SLP 	13
#define		MATC_STATE_FOTA	14
#define		MATC_STATE_FCON	15
#define		MATC_STATE_FTP  16
#define		MATC_STATE_MNT 	17
#define		MATC_STATE_ERR 	18
void ______(){	DLC_MatLineIdx = 0;};
void MTRdy()
{
	DLC_MatLineIdx = 0;
	DLCMatSend( "AT$VER\r" );
	DLCMatTimerset( 0,300 );
	DLC_MatState = MATC_STATE_IDLE;
}
void MTVrT()
{
	DLC_MatLineIdx = 0;
	DLCMatSend( "AT$VER\r" );
	DLCMatTimerset( 0,100 );
}
void MTVer()
{
	DLC_MatLineIdx = 0;
	DLCMatSend( "AT$IMEI\r" );
	DLCMatSend( "AT$NUM\r" );
	DLCMatTimerset( 0,500 );
	DLC_MatState = MATC_STATE_IMEI;
}
void MTimei()
{
	DLC_MatLineIdx = 0;
	DLCMatSend( "AT$SETAPN,soracom.io,sora,sora,PAP\r" );
	DLCMatTimerset( 0,300 );
	DLC_MatState = MATC_STATE_APN;
}
void MTapn()
{
	DLC_MatLineIdx = 0;
	if (DLC_MatFotaExe == false) {	// fota 運用時
		DLCMatSend( "AT$SETSERVER,beam.soracom.io,8888\r" );
	} else {	// FOTA実行時
		DLCMatSend( "AT$SETSERVER,harvest-files.soracom.io,80\r" );	// fota soracom harvest指定
	}
	DLCMatTimerset( 0,300 );
	DLC_MatState = MATC_STATE_SVR;
}
void MTserv()
{
	DLC_MatLineIdx = 0;
	DLCMatSend( "AT$CONNECT\r" );
	DLCMatTimerset( 0,12000 );
	DLC_MatState = MATC_STATE_CONG;
}
void MTcong()
{
	DLC_MatLineIdx = 0;
	DLCMatSend( "AT$CONNECT?\r" );
	DLCMatTimerset( 0,3000 );
	if (DLC_MatFotaExe == false) {	// fota 運用時
		DLC_MatState = MATC_STATE_COND;
	} else {	//  FOTA実行時
		DLC_MatState = MATC_STATE_FOTA;	// fota FOTA stateへ
	}
}
void MTtime()
{
	memcpy( DLC_MatDateTime,DLC_MatLineBuf,DLC_MatLineIdx );
	DLC_MatLineIdx = 0;
	DLCMatSend( "AT$TIME\r" );
	DLCMatTimerset( 0,300 );
}
void MTrsrp()
{
	DLC_MatLineIdx = 0;
	DLCMatSend( "AT$RSRP\rAT$RSRQ\rAT$RSSI\rAT$SINR\r" );
}
void MTopn1()
{
	memcpy( DLC_MatRadioDensty,DLC_MatLineBuf,DLC_MatLineIdx );
	DLC_MatLineIdx = 0;
	DLCMatSend( "AT$OPEN\r" );
	DLCMatTimerset( 0,1500 );
	DLC_MatState = MATC_STATE_OPN1;
}
void MTopnF()	// fota
{
	DLC_MatLineIdx = 0;
	DLCMatSend( "AT$OPEN\r" );
	DLCMatTimerset( 0,1500 );
}
void MTcnfg()
{
	DLC_MatLineIdx = 0;
	DLCMatPostConfig();
	DLCMatTimerset( 0,3000 );
	DLC_MatState = MATC_STATE_CNFG;
}
void MTwget()	// fota
{
	DLC_MatLineIdx = 0;
	DLCMatWgetFile();
	DLCMatTimerset( 0,3000 );
}
void MTdata()
{
	int	rt;
	rt = DLCMatRecvDisp();
	putst("RecvRet=");puthxs( rt );putcrlf();
	if( rt == 0 ){
		DLC_MatLineIdx = 0;
		zLogOn = 1;
	}
	else {
		DLC_MatLineIdx = 0;
		DLCMatSend( "AT$RECV,1024\r" );
	}
}
void MTfirm()	// fota
{
	int	rt;
	if (DLC_MatFotaWriteNG == false) {	/* 書込みNGなし */
		DLCMatTimerset( 0,1000 );	/* 10秒タイマー起動(値要検討) */
	}
	rt = DLCMatRecvWriteFota();	/* SPIへ受信データ書込み処理 */
	putst("RecvRet=");puthxs( rt );putcrlf();
	if( rt == 0 ){
		DLC_MatLineIdx = 0;
		zLogOn = 1;
	}
	else {
		DLC_MatLineIdx = 0;
		DLCMatSend( "AT$RECV,1024\r" );
	}
}
void MTcls1()
{
	DLC_MatLineIdx = 0;
	DLCMatSend( "AT$OPEN\r" );
	DLC_MatState = MATC_STATE_OPN2;
}
void MTstst()
{
	DLC_MatLineIdx = 0;
	DLCMatPostStatus();
	DLCMatTimerset( 0,3000 );
	DLC_MatState = MATC_STATE_STAT;
}
void MTcls2()
{
	DLC_MatLineIdx = 0;
	DLCMatSend( "AT$OPEN\r" );
	DLC_MatState = MATC_STATE_OPN3;
}
void MTrprt()
{
	DLC_MatLineIdx = 0;
	DLCMatPostReport();
	DLCMatTimerset( 0,3000 );
	DLC_MatState = MATC_STATE_RPT;
}
void MTcls3()
{
	DLC_MatLineIdx = 0;
	DLCMatSend( "AT$DISCONNECT\r" );
	DLCMatTimerset( 0,300 );
}
void MTdisc()
{
	DLC_MatLineIdx = 0;
	DLC_MatSleep = 1;
	DLCMatTimerClr(1);
	PORT_GroupWrite( PORT_GROUP_1,0x1<<10,0 );						/* Sleep! */
	DLC_MatState = MATC_STATE_SLP;
}
void MTslep()
{
	DLC_MatLineIdx = 0;
	putst("【Sleep】\r\n");
	DLCMatTimerset( 0,3000 );										/* For Test afer 30s Go Wake */
}
void MTslp1()
{
	PORT_GroupWrite( PORT_GROUP_1,0x1<<10,-1 );						/* Wake! */
}
void MTwake()
{
	putst("【Wake】\r\n");
	PORT_GroupWrite( PORT_GROUP_1,0x1<<10,-1 );						/* Wake! */
}
void MTtoF()	// fota T/O
{
	// 実行フラグそのままでリセットしリトライ?
}
struct {
	uchar	wx;
	uchar	rx;
	int		msg[0x20];
} DLC_MatMsg;
int	 MatGetMsgStack()
{
	int msg;
	if( DLC_MatMsg.wx != DLC_MatMsg.rx ){
		msg = DLC_MatMsg.msg[DLC_MatMsg.rx++];
		DLC_MatMsg.rx &= 0x1F;
		return msg;
	}
	return -1;
}
void MatMsgSend( int msg )
{
	DLC_MatMsg.msg[DLC_MatMsg.wx] = msg;
	DLC_MatMsg.wx &= 0x1F;
}
void DLCMatClockDisplay(char *s)
{
	RTC_DATETIME dt;
	RTC_getDatetime( &dt );
	sprintf( s,"%02d/%02d/%02d %02d:%02d:%02d",(int)dt.year,(int)dt.month,(int)dt.day,(int)dt.hour,(int)dt.minute,(int)dt.second );
}
void	 (*MTjmp[17][19])() = {
/*					  0         1       2      3       4       5       6       7       8       9       10      11      12      13      14      15      16      17   18     */
/*				  	 INIT    IDLE    IMEI    APN     SVR     CONG    COND    OPN1    CNFG    OPN2    STAT    OPN3    REPT    SLEEP   FOTA    FCON    FTP     MNT     ERR   */
/* MATCORE RDY 0 */{ MTRdy,  MTRdy,  MTRdy,  MTRdy,  MTRdy,  MTRdy,  MTRdy,  MTRdy,  MTRdy,  MTRdy,  MTRdy,  MTRdy,  MTRdy,  MTRdy,  MTRdy,  MTRdy,  MTRdy,  MTRdy,  MTRdy  },
/* ERROR       1 */{ ______, MTVrT,  ______, ______, ______, MTserv, ______, ______, ______, ______, ______, ______, MTcls3, ______, ______, ______, ______, ______, ______ },
/* $VER		   2 */{ ______, MTVer,  ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______ },
/* $NUM		   3 */{ ______, ______, MTimei, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______ },
/* OK          4 */{ ______, ______, ______, MTapn,  MTserv, MTcong, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______ },
/* $CONNECT:1  5 */{ ______, ______, ______, ______, ______, ______, MTtime, ______, ______, ______, ______, ______, ______, ______, MTopnF, ______, ______, ______, ______ },
/* $TIME       6 */{ ______, ______, ______, ______, ______, ______, MTrsrp, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______ },
/* $RSRP       7 */{ ______, ______, ______, ______, ______, ______, MTopn1, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______ },
/* $OPEN       8 */{ ______, ______, ______, ______, ______, ______, ______, MTcnfg, ______, MTstst, ______, MTrprt, ______, MTserv, MTwget, ______, ______, ______, ______ },
/* $CLOSE      9 */{ ______, ______, ______, ______, ______, ______, ______, ______, MTcls1, ______, MTcls2, ______, MTcls3, ______, ______, ______, ______, ______, ______ },
/* $RECVDATA  10 */{ ______, ______, ______, ______, ______, ______, ______, ______, MTdata, ______, MTdata, ______, MTdata, ______, MTfirm, ______, ______, ______, ______ },
/* $CONNECT:0 11 */{ ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, MTdisc, ______, ______, ______, ______, ______, ______ },
/* TimOut     12 */{ MTRdy,  MTVrT,  MTVer,  MTimei, MTapn,  MTserv, ______, ______, ______, ______, ______, ______, ______, MTslp1, MTtoF,  ______, ______, ______, ______ },
/* WAKEUP     13 */{ ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, MTwake, ______, ______, ______, ______, ______ },
/* FOTA       14 */{ ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______ },
/* FTP        15 */{ ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______ },
/* $SLEEP     16 */{ ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, MTslep, ______, ______, ______, ______, ______ },
							};
void DLCMatState()
{
	char	*p,*q;
	int 	len;
	len = SERCOM5_USART_Read( (uint8_t*)&DLC_MatLineBuf[DLC_MatLineIdx],sizeof( DLC_MatLineBuf) );				/* MATcoreから入力 */
	DLCMatLog( len );
	DLC_MatLineIdx += len;
	DLC_Matfact = 0xff;
	if( DLC_MatLineIdx == 6 ){
		if( strstr( (char*)DLC_MatLineBuf,"ERROR\r" )){
			DLC_Matfact = MATC_FACT_ERR;
		}
	}
	if( DLC_MatLineIdx >= 14 ){
		if( strstr( (char*)DLC_MatLineBuf,"MATCORE READY\r" )){
			DLC_Matfact = MATC_FACT_RDY;
		}
	}
	if( DLC_MatLineIdx >= 11 ){								/* $VER:01.04 */
		if( strstr( (char*)DLC_MatLineBuf,"$VER:" )){
			DLC_Matfact = MATC_FACT_VER;
		}
	}
	if( DLC_MatLineIdx >= 21 ){								/* $NUM:022001004788412 */
		p = strstr( (char*)DLC_MatLineBuf,"$NUM:" );
		if( p ){
			q = strchr( p,'\r' );							/* <cr>まで受信済み */
			if( q ){
				*q = 0;
				strcpy( DLC_MatNUM,"81" );
				strcat( DLC_MatNUM, &p[6] );
				DLC_Matfact = MATC_FACT_NUM;
			}
		}
	}
	if( DLC_MatLineIdx >= 22 ){								/* $IMEI:356766100967880 */
		p = strstr( (char*)DLC_MatLineBuf,"$IMEI:" );
		if( p ){
			q = strchr( p,'\r' );							/* <cr>まで受信済み */
			if( q ){
				*q = 0;
				strcpy( DLC_MatIMEI,&q[5] );
				DLC_Matfact = MATC_FACT_NUM;
			}
		}
	}
	if( DLC_MatLineIdx == 4 ){
		if( strstr( (char*)DLC_MatLineBuf,"\rOK\r" )){
			DLC_MatLineIdx -= 4;
			memcpy( DLC_MatLineBuf,&DLC_MatLineBuf[4],DLC_MatLineIdx );
			DLC_Matfact = MATC_FACT_OK;
		}
	}
	if( DLC_MatLineIdx == 3 ){
		if( strstr( (char*)DLC_MatLineBuf,"OK\r" )){
			DLC_MatLineIdx -= 3;
			memcpy( DLC_MatLineBuf,&DLC_MatLineBuf[3],DLC_MatLineIdx );
			DLC_Matfact = MATC_FACT_OK;
		}
	}
	if( DLC_MatLineIdx >= 10 ){
		if( strstr( (char*)DLC_MatLineBuf,"$CONNECT:1\r" ))
			DLC_Matfact = MATC_FACT_CON;
		if( strstr( (char*)DLC_MatLineBuf,"$CONNECT:0\r" ))
			DLC_Matfact = MATC_FACT_DSC;
	}
	if( DLC_MatLineIdx >= 24 ){								/* $TIME:22/08:03,18:16:32 */
		p = strstr( (char*)DLC_MatLineBuf,"$TIME:2" );
		if( p ){
			if( strchr( p,'\r' )){							/* <cr>まで受信済み */
				DLC_Matfact = MATC_FACT_TIM;
				RTC_DATETIME dt;
				dt.year   = (p[6]-'0')*10 + (p[7]-'0');
				dt.month  = (p[9]-'0')*10 + (p[10]-'0');
				dt.day	  = (p[12]-'0')*10 + (p[13]-'0');
				dt.hour	  = (p[15]-'0')*10 + (p[16]-'0');
				dt.minute = (p[18]-'0')*10 + (p[19]-'0');
				dt.second = (p[21]-'0')*10 + (p[22]-'0');
				RTC_setDateTime( dt );
			}
		}
	}
	if( DLC_MatLineIdx >= 37 ){								/* $RSRP:-nn<cr>$RSRQ:-n<cr>$RSSI:-nn<cr>$SINR:nn<cr> */
		DLC_MatLineBuf[DLC_MatLineIdx] = 0;
		p = strstr( (char*)DLC_MatLineBuf,"$SINR:" );
		if( p ){
			if( strchr( p,'\r' )){							/* $SINR:nn<cr>まで受信済み */
				DLC_Matfact = MATC_FACT_RSR;
			}
		}
	}
	if( DLC_MatLineIdx >= 6 ){
		if( strstr( (char*)DLC_MatLineBuf,"$OPEN\r" )){
			DLC_Matfact = MATC_FACT_OPN;
		}
		else if( strstr( (char*)DLC_MatLineBuf,"$RECV\r" )){
			DLC_MatLineIdx = 0;
			zLogOn = 0;
			DLCMatSend( "AT$RECV,1024\r" );
		}
	}
	if( DLC_MatLineIdx >= 7 ){
		if( strstr( (char*)DLC_MatLineBuf,"$CLOSE\r" )){
			DLC_Matfact = MATC_FACT_CLS;
		}
		if( strstr( (char*)DLC_MatLineBuf,"$SLEEP\r" )){
			DLC_Matfact = MATC_FACT_SLP;
		}
	}
	if( DLC_MatLineIdx >= 8 ){
		if( strstr( (char*)DLC_MatLineBuf,"$WAKEUP\r" )){
			DLC_Matfact = MATC_FACT_OPN;
		}
	}
	if( DLC_MatLineIdx >= 15 ){
		DLC_MatLineBuf[DLC_MatLineIdx] = 0;
		if( strstr( (char*)DLC_MatLineBuf,"$RECVDATA:" )){
			p = strchr( (char*)DLC_MatLineBuf,'\"' );
			if( p > 0 ){
				if( strstr( p+2,"\"\r" )){
					DLC_Matfact = MATC_FACT_DATA;
				}
			}
		}
	}
	if( DLC_Matfact == 0xff ){
		if( DLCMatTmChk( 0 ) )
			DLC_Matfact = MATC_FACT_TO;
		else {
			switch( MatGetMsgStack() ){
			case 1:
				DLC_Matfact = MATC_FACT_TO;
				break;
			case 2:
				DLC_Matfact = MATC_FACT_WUP;
				break;
			default:
				return;
			}
		}
	}
	if( DLC_Matfact != 0xff ){
		char	s[20];
		DLCMatClockDisplay(s);putst( s );putst("【");puthxb( DLC_Matfact );putch(':');puthxb( DLC_MatState );putst("】\r\n");
		(*MTjmp[DLC_Matfact][DLC_MatState])();
	}
}
static char help[] = {"\r\nL:LED test \
				  \r\nI:GPIO(in)  \
				  \r\nO:GPIO(out) \
				  \r\nM:MATcoreTest \
				  \r\nF:FlashTest" };
struct  {
	int		LoggerSerialNo;
	int		Interval;
	int		ReprotInterval;
	int		IntervalAlert;
	int		ReprotIntervalAlert;
	int		Select_ch1;
	int		Upper0_ch1;
	int		Lower0_ch1;
	int		AlertSw_U2_ch1;
	float	Upper2_ch1;
	int		AlertSw_U1_ch1;
	float	Upper1_ch1;
	int		AlertSw_L1_ch1;
	float	Lower1_ch1;
	int		lertSw_L21_ch1;
	int		AlertSw_L2_ch1;
	float	Lower2_ch1;
	char	easure_ch1[16];
	char	eaKind_ch1[16];
	int		Chattering_ch1;
	int		Select_ch2;
	int		Upper0_ch2;
	int		Lower0_ch2;
	int		AlertSw_U2_ch2;
	int		Upper2_ch2;
	int		AlertSw_U1_ch2;
	int		Upper1_ch2;
	int		AlertSw_L1_ch2;
	int		Lower1_ch2;
	int		AlertSw_L2_ch2;
	int		Lower2_ch2;
	char	Measure_ch2[16];
	char	MeaKind_ch2[16];
	int	Chattering_ch2;
} DLC_MatConfigPara;
struct {
	int		LoggerSerialNo;
	char	IMEI[16];
	char	MSISDN[16];
	char	Version[16];
	char	LTEVersion[16];
	float	ExtCellPwr1;
	float	ExtCellPwr2;
	int		Batt1Use;
	int		Batt2Use;
	int		RSRP;
	int		RSRQ;
	int		RSSI;
	int		SINR;
	float	Temp;
	float	TxType;
} DLC_MatSgtatusPara;
struct {
	float	Value_ch1;
	float	Value_ch2;
	char	Alert[2];
} DLC_MatReportData[100];
int	DLC_MatReportStack;
void DLCMatConfigDefault()
{
	DLC_MatConfigPara.LoggerSerialNo 		= 1234567;
	DLC_MatConfigPara.Interval 				= 60;
	DLC_MatConfigPara.ReprotInterval 		= 300;
	DLC_MatConfigPara.IntervalAlert 		= 30;
	DLC_MatConfigPara.ReprotIntervalAlert 	= 120;
	DLC_MatConfigPara.Select_ch1 			= 1;
	DLC_MatConfigPara.Upper0_ch1 			= 1;
	DLC_MatConfigPara.Lower0_ch1 			= 0;
	DLC_MatConfigPara.AlertSw_U2_ch1 		= 1;
	DLC_MatConfigPara.Upper2_ch1 			= 0.75;
	DLC_MatConfigPara.AlertSw_U1_ch1 		= 1;
	DLC_MatConfigPara.Upper1_ch1 			= 0.55;
	DLC_MatConfigPara.AlertSw_L1_ch1 		= 1;
	DLC_MatConfigPara.Lower1_ch1 			= 0.25;
	DLC_MatConfigPara.lertSw_L21_ch1 		= 0;
	DLC_MatConfigPara.AlertSw_L2_ch1 		= 1;
	DLC_MatConfigPara.Lower2_ch1 			= 0.15;
	strcpy( DLC_MatConfigPara.easure_ch1,"水圧" );
	strcpy( DLC_MatConfigPara.eaKind_ch1,"MPa" );
	DLC_MatConfigPara.Chattering_ch1 		= 100;
	DLC_MatConfigPara.Select_ch2 			= 1;
	DLC_MatConfigPara.Upper0_ch2 			= 100;
	DLC_MatConfigPara.Lower0_ch2 			= -25;
	DLC_MatConfigPara.AlertSw_U2_ch2 		= 1;
	DLC_MatConfigPara.Upper2_ch2 			= 90;
	DLC_MatConfigPara.AlertSw_U1_ch2 		= 1;
	DLC_MatConfigPara.Upper1_ch2 			= 80;
	DLC_MatConfigPara.AlertSw_L1_ch2 		= 1;
	DLC_MatConfigPara.Lower1_ch2 			= 0;
	DLC_MatConfigPara.AlertSw_L2_ch2 		= 1;
	DLC_MatConfigPara.Lower2_ch2 			= -10;
	strcpy( DLC_MatConfigPara.Measure_ch2,"流量" );
	strcpy( DLC_MatConfigPara.MeaKind_ch2,"m^3/hour" );
	DLC_MatConfigPara.Chattering_ch2 		= 1;
}
void DLCMatStatusDefault()
{
	DLC_MatSgtatusPara.LoggerSerialNo 		= 1234567;
	strcpy( DLC_MatSgtatusPara.IMEI,"440103256497859" );
	strcpy( DLC_MatSgtatusPara.MSISDN,"812001003404286" );
	strcpy( DLC_MatSgtatusPara.Version,"01.04" );
	strcpy( DLC_MatSgtatusPara.LTEVersion,"01.04" );
	DLC_MatSgtatusPara.ExtCellPwr1 			= 123.456;
	DLC_MatSgtatusPara.ExtCellPwr2 			= 123.4556;
	DLC_MatSgtatusPara.Batt1Use 			= 1;
	DLC_MatSgtatusPara.Batt2Use				= 0;
	DLC_MatSgtatusPara.RSRP					= -97;
	DLC_MatSgtatusPara.RSRQ					= -8;
	DLC_MatSgtatusPara.RSSI					= -84;
	DLC_MatSgtatusPara.SINR					= 4;
	DLC_MatSgtatusPara.Temp					= 24.5;
	DLC_MatSgtatusPara.TxType				= 24.5;
}
void DLCMatReortDefault()
{
	for(int i=0;i<100;i++){
		DLC_MatReportData[i].Value_ch1 = i+0.1;
		DLC_MatReportData[i].Value_ch2 = i+0.2;
		DLC_MatReportData[i].Alert[0] = '0';
		DLC_MatReportData[i].Alert[1] = '0';
	}
}
//static char http_Head[] = "POST / HTTP/1.1\r\nConnection: Keep-Alive\r\nHost:beam.soracom.io\r\nContent-Type:application/json\r\nContent-Length:    \r\n\r\n";
static char http_Head[] = "POST / HTTP/1.1\r\nHost:beam.soracom.io\r\nContent-Type:application/json\r\nContent-Length:    \r\n\r\n";
static char http_tmp[2000];
//static char http_tmp[2000] = "PUT / HTTP/1.1\r\nHost: beam.soracom.io:8888\r\nUser-Agent: curl/7.64.0\r\nAccept:.*/*\r\nContent-Type:application/json\r\nContent-Length:0000\r\n\r\n";
char	DLC_MatSendBuff[2000];
void DLCMatPostConfig()
{
	char	tmp[48],n,*p;
	int		i;
	
	strcpy( http_tmp,http_Head );
	strcat( http_tmp,"{\"Config\":{" );
	sprintf( tmp,"\"LoggerSerialNo\":%d,"		,DLC_MatConfigPara.LoggerSerialNo );		strcat( http_tmp,tmp );
	sprintf( tmp,"\"Interval\":%d,"				,DLC_MatConfigPara.Interval );				strcat( http_tmp,tmp );
	sprintf( tmp,"\"ReprotInterval\":%d,"		,DLC_MatConfigPara.ReprotInterval );		strcat( http_tmp,tmp );
	sprintf( tmp,"\"IntervalAlert\":%d,"		,DLC_MatConfigPara.IntervalAlert  );		strcat( http_tmp,tmp );
	sprintf( tmp,"\"ReprotIntervalAlert\":%d,"	,DLC_MatConfigPara.ReprotIntervalAlert );	strcat( http_tmp,tmp );
	sprintf( tmp,"\"Select_ch1\":%d,"			,DLC_MatConfigPara.Select_ch1 );			strcat( http_tmp,tmp );
	sprintf( tmp,"\"Upper0_ch1\":%d,"			,DLC_MatConfigPara.Upper0_ch1 );			strcat( http_tmp,tmp );
	sprintf( tmp,"\"Lower0_ch1\":%d,"			,DLC_MatConfigPara.Lower0_ch1 );			strcat( http_tmp,tmp );
	sprintf( tmp,"\"AlertSw_U2_ch1\":%d,"		,DLC_MatConfigPara.AlertSw_U2_ch1 );		strcat( http_tmp,tmp );
	sprintf( tmp,"\"Upper2_ch1\":%f,"			,DLC_MatConfigPara.Upper2_ch1 );			strcat( http_tmp,tmp );
	sprintf( tmp,"\"AlertSw_U1_ch1\":%d,"		,DLC_MatConfigPara.AlertSw_U1_ch1 );		strcat( http_tmp,tmp );
	sprintf( tmp,"\"Upper1_ch1\":%f,"			,DLC_MatConfigPara.Upper1_ch1 );			strcat( http_tmp,tmp );
	sprintf( tmp,"\"AlertSw_L1_ch1\":%d,"		,DLC_MatConfigPara.AlertSw_L1_ch1 );		strcat( http_tmp,tmp );
	sprintf( tmp,"\"Lower1_ch1\":%f,"			,DLC_MatConfigPara.Lower1_ch1 );			strcat( http_tmp,tmp );
 	sprintf( tmp,"\"lertSw_L21_ch1\":%d,"		,DLC_MatConfigPara.lertSw_L21_ch1 );		strcat( http_tmp,tmp );
	sprintf( tmp,"\"AlertSw_L2_ch1\":%d,"		,DLC_MatConfigPara.AlertSw_L2_ch1 );		strcat( http_tmp,tmp );
	sprintf( tmp,"\"Lower2_ch1\":%f,"			,DLC_MatConfigPara.Lower2_ch1 );			strcat( http_tmp,tmp );
 	sprintf( tmp,"\"easure_ch1\":\"%s\","		,DLC_MatConfigPara.easure_ch1 );			strcat( http_tmp,tmp );
 	sprintf( tmp,"\"eaKind_ch1\":\"%s\","		,DLC_MatConfigPara.eaKind_ch1 );			strcat( http_tmp,tmp );
	sprintf( tmp,"\"Chattering_ch1\":%d,"		,DLC_MatConfigPara.Chattering_ch1 );		strcat( http_tmp,tmp );
	sprintf( tmp,"\"Select_ch2\":%d,"			,DLC_MatConfigPara.Select_ch2 );			strcat( http_tmp,tmp );
	sprintf( tmp,"\"Upper0_ch2\":%d,"			,DLC_MatConfigPara.Upper0_ch2 );			strcat( http_tmp,tmp );
	sprintf( tmp,"\"Lower0_ch2\":%d,"			,DLC_MatConfigPara.Lower0_ch2 );			strcat( http_tmp,tmp );
	sprintf( tmp,"\"AlertSw_U2_ch2\":%d,"		,DLC_MatConfigPara.AlertSw_U2_ch2 );		strcat( http_tmp,tmp );
	sprintf( tmp,"\"Upper2_ch2\":%d,"			,DLC_MatConfigPara.Upper2_ch2 );			strcat( http_tmp,tmp );
	sprintf( tmp,"\"AlertSw_U1_ch2\":%d,"		,DLC_MatConfigPara.AlertSw_U1_ch2 );		strcat( http_tmp,tmp );
	sprintf( tmp,"\"Upper1_ch2\":%d,"			,DLC_MatConfigPara.Upper1_ch2 );			strcat( http_tmp,tmp );
	sprintf( tmp,"\"AlertSw_L1_ch2\":%d,"		,DLC_MatConfigPara.AlertSw_L1_ch2 );		strcat( http_tmp,tmp );
	sprintf( tmp,"\"Lower1_ch2\":%d,"			,DLC_MatConfigPara.Lower1_ch2 );			strcat( http_tmp,tmp );
	sprintf( tmp,"\"AlertSw_L2_ch2\":%d,"		,DLC_MatConfigPara.AlertSw_L2_ch2 );		strcat( http_tmp,tmp );
	sprintf( tmp,"\"Lower2_ch2\":%d,"			,DLC_MatConfigPara.Lower2_ch2 );			strcat( http_tmp,tmp );
	sprintf( tmp,"\"Measure_ch2\":\"%s\","		,DLC_MatConfigPara.Measure_ch2 );			strcat( http_tmp,tmp );
	sprintf( tmp,"\"MeaKind_ch2\":\"%s\","		,DLC_MatConfigPara.MeaKind_ch2 );			strcat( http_tmp,tmp );
	sprintf( tmp,"\"Chattering_ch2\":%d"		,DLC_MatConfigPara.Chattering_ch2  );		strcat( http_tmp,tmp );
	strcat( http_tmp,"}}" );
	i = (int)(strchr(http_tmp,'}')-strstr(http_tmp,"{\"Config\":{"))+1;
	if( i > 0 ){
		p = strstr( http_tmp,"Length:    " );
		if( p < 0 ){
			putst("format err1 \r\n" );
			return;
		}
		sprintf( tmp,"%d",i+1 );
		for( i=0;tmp[i]!=0;i++ )
			p[7+i] = tmp[i];
		putst( http_tmp );putcrlf();
		strcpy( DLC_MatSendBuff,"AT$SEND,\"" );
		tmp[2] = 0;
		for( i=0;http_tmp[i]!=0;i++ ){
			n = http_tmp[i];
			tmp[0] = outhex( n>>4 );
			tmp[1] = outhex( n&0x0f );
			strcat( DLC_MatSendBuff,tmp );
		}
		strcat( DLC_MatSendBuff,"\"\r" );
		DLCMatSend( DLC_MatSendBuff );
	}
}
void DLCMatPostStatus()
{
	char	tmp[48],n,*p;
	int		i;
	DLC_MatSgtatusPara.RSRP					= DLCMatCharInt( DLC_MatRadioDensty,"RSRP:" );
	DLC_MatSgtatusPara.RSRQ					= DLCMatCharInt( DLC_MatRadioDensty,"RSRQ:" );
	DLC_MatSgtatusPara.RSSI					= DLCMatCharInt( DLC_MatRadioDensty,"RSSI:" );
	DLC_MatSgtatusPara.SINR					= DLCMatCharInt( DLC_MatRadioDensty,"SINR:" );
	strcpy( DLC_MatSgtatusPara.MSISDN,DLC_MatNUM );
	strcpy( DLC_MatSgtatusPara.IMEI,DLC_MatIMEI );
	strcpy( http_tmp,http_Head );
	strcat( http_tmp,"{\"Status\":{" );
	sprintf( tmp,"\"LoggerSerialNo\":%d,"		,DLC_MatSgtatusPara.LoggerSerialNo );		strcat( http_tmp,tmp );
	sprintf( tmp,"\"IMEI\":%s,"					,DLC_MatSgtatusPara.IMEI );					strcat( http_tmp,tmp );
	sprintf( tmp,"\"MSISDN\":%s,"				,DLC_MatSgtatusPara.MSISDN );				strcat( http_tmp,tmp );
	sprintf( tmp,"\"Version\":%s,"				,DLC_MatSgtatusPara.Version  );				strcat( http_tmp,tmp );
	sprintf( tmp,"\"LTEVersion\":%s,"			,DLC_MatSgtatusPara.LTEVersion );			strcat( http_tmp,tmp );
	sprintf( tmp,"\"ExtCellPwr1\":%f,"			,DLC_MatSgtatusPara.ExtCellPwr1 );			strcat( http_tmp,tmp );
	sprintf( tmp,"\"ExtCellPwr2\":%f,"			,DLC_MatSgtatusPara.ExtCellPwr2 );			strcat( http_tmp,tmp );
	sprintf( tmp,"\"Batt1Use\":%d,"				,DLC_MatSgtatusPara.Batt1Use );				strcat( http_tmp,tmp );
	sprintf( tmp,"\"Batt2Use\":%d,"				,DLC_MatSgtatusPara.Batt2Use );				strcat( http_tmp,tmp );
	sprintf( tmp,"\"RSRP\":%d,"					,DLC_MatSgtatusPara.RSRP );					strcat( http_tmp,tmp );
	sprintf( tmp,"\"RSRQ\":%d,"					,DLC_MatSgtatusPara.RSRQ );					strcat( http_tmp,tmp );
	sprintf( tmp,"\"RSSI\":%d,"					,DLC_MatSgtatusPara.RSSI );					strcat( http_tmp,tmp );
	sprintf( tmp,"\"SINR\":%d,"					,DLC_MatSgtatusPara.SINR );					strcat( http_tmp,tmp );
	sprintf( tmp,"\"Temp\":%f,"					,DLC_MatSgtatusPara.Temp );					strcat( http_tmp,tmp );
 	sprintf( tmp,"\"TxType\":%f"				,DLC_MatSgtatusPara.TxType );				strcat( http_tmp,tmp );
	strcat( http_tmp,"}}" );
	i = (int)(strchr(http_tmp,'}')-strstr(http_tmp,"{\"Status\":{"))+1;
	if( i > 0 ){
		p = strstr( http_tmp,"Length:    " );
		if( p < 0 ){
			putst("format err1 \r\n" );
			return;
		}
		sprintf( tmp,"%d",i+1 );
		for( i=0;tmp[i]!=0;i++ )
			p[7+i] = tmp[i];
		putst( http_tmp );putcrlf();
		strcpy( DLC_MatSendBuff,"AT$SEND,\"" );
		tmp[2] = 0;
		for( i=0;http_tmp[i]!=0;i++ ){
			n = http_tmp[i];
			tmp[0] = outhex( n>>4 );
			tmp[1] = outhex( n&0x0f );
			strcat( DLC_MatSendBuff,tmp );
		}
		strcat( DLC_MatSendBuff,"\"\r" );
		DLCMatSend( DLC_MatSendBuff );
	}
}
/*
	機能：Reportを通知、SPI-Flashに溜まっているReportを通知
	Parameter:通知する数
*/
void DLCMatPostReport(int num)
{
	char	tmp[48],n,*p;
	char	s[20];	
	int		i;
	strcpy( http_tmp,http_Head );
	strcat( http_tmp,"{\"Report\":{" );
	strcat( http_tmp,"\"LoggerSerialNo\": 3423423}," );
	strcat( http_tmp,"\"ReportList\": [{" );
	DLCMatClockDisplay(s);
	sprintf( tmp,"\"Time\":%s,"			,s );										strcat( http_tmp,tmp );
	sprintf( tmp,"\"Value_ch1\":%f,"	,DLC_MatReportData[0].Value_ch1 );			strcat( http_tmp,tmp );
	sprintf( tmp,"\"Value_ch2\":%f,"	,DLC_MatReportData[0].Value_ch2 );			strcat( http_tmp,tmp );
	sprintf( tmp,"\"Alert\":%c%c,"		,DLC_MatReportData[0].Alert[0],DLC_MatReportData[0].Alert[1] );	strcat( http_tmp,tmp );
	strcat( http_tmp,"},{" );
	DLCMatClockDisplay(s);
	sprintf( tmp,"\"Time\":%s,"			,s );										strcat( http_tmp,tmp );
	sprintf( tmp,"\"Value_ch1\":%f,"	,DLC_MatReportData[0].Value_ch1 );			strcat( http_tmp,tmp );
	sprintf( tmp,"\"Value_ch2\":%f,"	,DLC_MatReportData[0].Value_ch2 );			strcat( http_tmp,tmp );
	sprintf( tmp,"\"Alert\":%c%c,"		,DLC_MatReportData[0].Alert[0],DLC_MatReportData[0].Alert[1] );	strcat( http_tmp,tmp );
	strcat( http_tmp,"},]}" );
	i = (int)(strchr(http_tmp,']')-strstr(http_tmp,"{\"Report\":{"))+1;
	if( i > 0 ){
		p = strstr( http_tmp,"Length:    " );
		if( p < 0 ){
			putst("format err1 \r\n" );
			return;
		}
		sprintf( tmp,"%d",i+1 );
		for( i=0;tmp[i]!=0;i++ )
			p[7+i] = tmp[i];
		putst( http_tmp );putcrlf();
		strcpy( DLC_MatSendBuff,"AT$SEND,\"" );
		tmp[2] = 0;
		for( i=0;http_tmp[i]!=0;i++ ){
			n = http_tmp[i];
			tmp[0] = outhex( n>>4 );
			tmp[1] = outhex( n&0x0f );
			strcat( DLC_MatSendBuff,tmp );
		}
		strcat( DLC_MatSendBuff,"\"\r" );
		DLCMatSend( DLC_MatSendBuff );
	}
}
void DLCMatWgetFile()	// fota
{
	char	tmp[48],n;
	int		i;
	putst("WgetExe!!!");putcrlf();
	strcpy( http_tmp,wget_Head );	/* soracom harvestへwget */
	putst( http_tmp );putcrlf();
	strcpy( DLC_MatSendBuff,"AT$SEND,\"" );
	tmp[2] = 0;
	for( i=0;http_tmp[i]!=0;i++ ){
		n = http_tmp[i];
		tmp[0] = outhex( n>>4 );
		tmp[1] = outhex( n&0x0f );
		strcat( DLC_MatSendBuff,tmp );
	}
	strcat( DLC_MatSendBuff,"\"\r" );
	DLCMatSend( DLC_MatSendBuff );
}
int DLCMatRecvDisp()
{
	char	*p,n;
	int		i,j=0,k;
	if(( p = strstr( (char*)DLC_MatLineBuf,"$RECVDATA:" )) > 0 ){
		p = str2int( &p[10],&i );										/* $RECVDATA,i,j,"...."<cr> */
		if( p < 0 ){													/* p            q  */
			putst( "format err2\r\n" );
			return -2;
		}
		p = str2int( p,&j );
		if( p < 0 ){
			putst( "format err3\r\n" );
			return -3;
		}
		putst("Ln=");puthxs(i);putst(" Rm=");puthxs(j);putcrlf();
		p = strchr( p,'\"' );
		if( p > 0 ){
			p++;
			for( k=0;k<i;k++ ){
				n = inhex( *p++ )<<4;
				n += inhex( *p++ );
				DLC_MatResBuf[DLC_MatResIdx++] = n;
			}
//			if( strstr( DLC_MatResBuf,"HTTP/1.1 200 OK" )){
//				if( strstr( DLC_MatResBuf,"Connection: close" ))
//					return 0;
//			}
// fota			if (strstr(DLC_MatResBuf, "\"LTEVersion\":")) {	// fota StatusでF/W version指定されたらFOTA起動?
// fota				DLC_MatFotaExe = true;
// fota				// フラグを維持したまま再起動したい
// fota			}
			if( j == 0 ){
				DLC_MatResBuf[DLC_MatResIdx] = 0;
				putst( DLC_MatResBuf );
				DLC_MatResIdx = 0;
			}
			else {
//				strcpy( &DLC_MatResBuf[DLC_MatResIdx],"★" );
//				DLC_MatResIdx += 2;
			}
			return j;
		}
		else {
			putst("format err4\r\n");
			return -4;
		}
	}
	else
		putst("format err1\r\n");
	return -1;
}
int DLCMatRecvWriteFota()	// fota SPIへ受信データ書込み処理
{
	char	*p,*fpt,n;
	int		i,j=0,k,len;
	int		fotaaddress=DLC_MatSPIFlashAddrFota;	/* 現状0番地(test) */
	if(( p = strstr( (char*)DLC_MatLineBuf,"$RECVDATA:" )) > 0 ){
		p = str2int( &p[10],&i );										/* $RECVDATA,i,j,"...."<cr> */
		if( p < 0 ){													/* p            q  */
			putst( "format err2\r\n" );
			return -2;
		}
		p = str2int( p,&j );
		if( p < 0 ){
			putst( "format err3\r\n" );
			return -3;
		}
		putst("Ln=");puthxs(i);putst(" Rm=");puthxs(j);putcrlf();
		p = strchr( p,'\"' );
		if( p > 0 ){
			p++;
			memset(DLC_MatResBuf, 0, sizeof(DLC_MatResBuf));	/* 受信バッファ0初期化 */
			for( k=0;k<i;k++ ){
				n = inhex( *p++ )<<4;
				n += inhex( *p++ );
				DLC_MatResBuf[DLC_MatResIdx++] = n;
			}
			DLC_MatResBuf[DLC_MatResIdx] = 0;
//			putst( DLC_MatResBuf );
			DLC_MatResIdx = 0;
			if (strstr(DLC_MatResBuf,"Connection: close") == NULL) {	/* ヘッダにConnection: closeなし=先頭以降の受信データ */
				fpt = DLC_MatResBuf;		/* 受信バッファの先頭アドレス */
				len = DLC_MatSPIRemaindataFota;	/* 半端byteのレングス */
				if (j > 0) {
					putst("RecvData1:\r\n");
//					Dump(DLC_MatResBuf,0x400);putcrlf();
					fotaaddress /= DLC_MatSPIFlashPage;
					if (DLC_MatSPIRemaindataFota != 0) {	/* 半端byteありの場合 */
						memcpy(&DLC_MatSPIRemainbufFota[DLC_MatSPIRemaindataFota], fpt ,sizeof(DLC_MatSPIRemainbufFota) - DLC_MatSPIRemaindataFota);	/* 今回受信データで256byte埋めて */
						if (W25Q128JV_programPage(fotaaddress + DLC_MatSPIWritePageFota, 0, (uint8_t*)DLC_MatSPIRemainbufFota, DLC_MatSPIFlashPage, true) == W25Q128JV_ERR_NONE ){	/* 256byte書込む */
							puthxw(DLC_MatSPIFlashPage * (fotaaddress + DLC_MatSPIWritePageFota));
							putst("_R:OK");putcrlf();
							memset(DLC_MatSPICheckbufFota, 0, sizeof(DLC_MatSPICheckbufFota));
							if (W25Q128JV_readData(DLC_MatSPIFlashPage * (fotaaddress + DLC_MatSPIWritePageFota), (uint8_t*)DLC_MatSPICheckbufFota, DLC_MatSPIFlashPage) == W25Q128JV_ERR_NONE) {
								if (memcmp(DLC_MatSPICheckbufFota, DLC_MatSPIRemainbufFota, DLC_MatSPIFlashPage) == 0) {
									putst("VERFY OK\r\n");
								} else {
									DLC_MatFotaWriteNG = true;
									putst("VERFY NG\r\n");
								}
							} else {
								DLC_MatFotaWriteNG = true;
								putst("READ NG\r\n");
							}
						} else {
							DLC_MatFotaWriteNG = true;
							putst("PROG NG\r\n");
						}
						fpt = &DLC_MatResBuf[sizeof(DLC_MatSPIRemainbufFota) - DLC_MatSPIRemaindataFota];	/* 書込みアドレス進める */
						DLC_MatSPIWritePageFota += 1;	/* 書込みページインデックス進める */
//						putst("BufData1:\r\n");Dump(DLC_MatSPIRemainbufFota, sizeof(DLC_MatSPIRemainbufFota));putcrlf();
					}
					for (k = 0; k < ((0x400 - len) / DLC_MatSPIFlashPage); k++) {	/* 残りのデータを256byte毎書込み */
						if (W25Q128JV_programPage(fotaaddress + k + DLC_MatSPIWritePageFota, 0, (uint8_t*)(fpt + DLC_MatSPIFlashPage * k), DLC_MatSPIFlashPage, true) == W25Q128JV_ERR_NONE ){
							puthxw(DLC_MatSPIFlashPage * (fotaaddress + k + DLC_MatSPIWritePageFota));
							putst(":OK");putcrlf();
							memset(DLC_MatSPICheckbufFota, 0, sizeof(DLC_MatSPICheckbufFota));
							if (W25Q128JV_readData(DLC_MatSPIFlashPage * (fotaaddress + k + DLC_MatSPIWritePageFota), (uint8_t*)DLC_MatSPICheckbufFota, DLC_MatSPIFlashPage) == W25Q128JV_ERR_NONE) {
								if (memcmp(DLC_MatSPICheckbufFota, (fpt + DLC_MatSPIFlashPage * k), DLC_MatSPIFlashPage) == 0) {
									putst("VERFY OK\r\n");
								} else {
									DLC_MatFotaWriteNG = true;
									putst("VERFY NG\r\n");
								}
							} else {
								DLC_MatFotaWriteNG = true;
								putst("READ NG\r\n");
							}
						} else {
							DLC_MatFotaWriteNG = true;
							putst("PROG NG\r\n");
						}
					}
					memset(DLC_MatSPIRemainbufFota, 0, sizeof(DLC_MatSPIRemainbufFota));	/* 半端byte保持バッファ0初期化 */
					DLC_MatSPIRemaindataFota = (0x400 - (DLC_MatSPIFlashPage - len)) - (DLC_MatSPIFlashPage * k);	/* 1ページ未満の半端byte数 */
//					putst("DLC_MatSPIRemaindataFota1:");puthxs(DLC_MatSPIRemaindataFota);putcrlf();
					memcpy(DLC_MatSPIRemainbufFota, fpt + DLC_MatSPIFlashPage * k ,DLC_MatSPIRemaindataFota);	/* 半端byte保持バッファに保持 */
					DLC_MatSPIWritePageFota = k + DLC_MatSPIWritePageFota;	/* SPI書込みページインデックス保持 */
//					putst("RemainData1:\r\n");Dump(DLC_MatSPIRemainbufFota, sizeof(DLC_MatSPIRemainbufFota));putcrlf();
				} else {
					putst("RecvData2:\r\n");
//					Dump(DLC_MatResBuf,i);putcrlf();
					fotaaddress /= DLC_MatSPIFlashPage;
					if (DLC_MatSPIRemaindataFota != 0) {	/* 半端byteありの場合 */
						memcpy(&DLC_MatSPIRemainbufFota[DLC_MatSPIRemaindataFota], fpt ,sizeof(DLC_MatSPIRemainbufFota) - DLC_MatSPIRemaindataFota);	/* 今回受信データで256byte埋めて */
						if (W25Q128JV_programPage(fotaaddress + DLC_MatSPIWritePageFota, 0, (uint8_t*)DLC_MatSPIRemainbufFota, DLC_MatSPIFlashPage, true) == W25Q128JV_ERR_NONE ){	/* 256byte書込む */
							puthxw(DLC_MatSPIFlashPage * (fotaaddress + DLC_MatSPIWritePageFota));
							putst("_R:OK");putcrlf();
							memset(DLC_MatSPICheckbufFota, 0, sizeof(DLC_MatSPICheckbufFota));
							if (W25Q128JV_readData(DLC_MatSPIFlashPage * (fotaaddress + DLC_MatSPIWritePageFota), (uint8_t*)DLC_MatSPICheckbufFota, DLC_MatSPIFlashPage) == W25Q128JV_ERR_NONE) {
								if (memcmp(DLC_MatSPICheckbufFota, DLC_MatSPIRemainbufFota, DLC_MatSPIFlashPage) == 0) {
									putst("VERFY OK\r\n");
								} else {
									DLC_MatFotaWriteNG = true;
									putst("VERFY NG\r\n");
								}
							} else {
								DLC_MatFotaWriteNG = true;
								putst("READ NG\r\n");
							}
						} else {
							DLC_MatFotaWriteNG = true;
							putst("PROG NG\r\n");
						}
						fpt = &DLC_MatResBuf[sizeof(DLC_MatSPIRemainbufFota) - DLC_MatSPIRemaindataFota];	/* 書込みアドレス進める */
						DLC_MatSPIWritePageFota += 1;	/* 書込みページインデックス進める */
//						putst("BufData2:\r\n");Dump(DLC_MatSPIRemainbufFota, sizeof(DLC_MatSPIRemainbufFota));putcrlf();
					}
					for (k = 0; k <= ((i - (DLC_MatSPIFlashPage - len)) / DLC_MatSPIFlashPage); k++) {	/* 残りのデータを256byte毎書込み */
						if (W25Q128JV_programPage(fotaaddress + k + DLC_MatSPIWritePageFota, 0, (uint8_t*)(fpt + DLC_MatSPIFlashPage * k), DLC_MatSPIFlashPage, true) == W25Q128JV_ERR_NONE ){
							puthxw(DLC_MatSPIFlashPage * (fotaaddress + k + DLC_MatSPIWritePageFota));
							putst(":OK");putcrlf();
							memset(DLC_MatSPICheckbufFota, 0, sizeof(DLC_MatSPICheckbufFota));
							if (W25Q128JV_readData(DLC_MatSPIFlashPage * (fotaaddress + k + DLC_MatSPIWritePageFota), (uint8_t*)DLC_MatSPICheckbufFota, DLC_MatSPIFlashPage) == W25Q128JV_ERR_NONE) {
								if (memcmp(DLC_MatSPICheckbufFota, (fpt + DLC_MatSPIFlashPage * k), DLC_MatSPIFlashPage) == 0) {
									putst("VERFY OK\r\n");
								} else {
									DLC_MatFotaWriteNG = true;
									putst("VERFY NG\r\n");
								}
							} else {
								DLC_MatFotaWriteNG = true;
								putst("READ NG\r\n");
							}
						} else {
							DLC_MatFotaWriteNG = true;
							putst("PROG NG\r\n");
						}
					}
					if (DLC_MatFotaWriteNG == false) {	/* 書込みNGなし */
						DLCMatTimerClr( 0 );	/* タイマークリア */
					}
				}
			} else {	/* ヘッダにConnection: closeあり=受信データ先頭 */
				for (k = 0; k < 4; k++) {	/* SPI 256kbyte消去 */
					char line[32];
					W25Q128JV_eraseBlock64(((fotaaddress / 0x10000) + k), true);	/* 現状address:0～ 1ブロック64kbyte*/
					sprintf( line, "%02X0000:ERASE OK\r\n",(unsigned int)((fotaaddress / 0x10000) + k) );
					putst( line );
				}
				memset(DLC_MatSPIRemainbufFota, 0, sizeof(DLC_MatSPIRemainbufFota));	/* 1ページ未満の半端byte保持バッファ0初期化 */
				DLC_MatSPIRemaindataFota = 0;
				fpt = strstr(DLC_MatResBuf,"Connection: close") + strlen("Connection: close\r\n\r\n");	/* FOTAデータの先頭アドレス */
				*(fpt - 1) = 0;	// strlenのため
				len = strlen(DLC_MatResBuf) + 1;	/* ヘッダのレングス */
				if (j > 0) {	/* データが1024byte以上の場合 */
					putst("RecvData3:\r\n");
//					Dump(fpt, 0x400 - len);putcrlf();
					fotaaddress /= DLC_MatSPIFlashPage;
					for (k = 0; k < ((0x400 - len) / DLC_MatSPIFlashPage); k++) {	/* ヘッダを抜いたFOTAデータを256byte毎書込み */
						if (W25Q128JV_programPage(fotaaddress + k, 0, (uint8_t*)(fpt + DLC_MatSPIFlashPage * k), DLC_MatSPIFlashPage, true) == W25Q128JV_ERR_NONE ){
							puthxw(DLC_MatSPIFlashPage * (fotaaddress + k));
							putst(":OK");putcrlf();
							memset(DLC_MatSPICheckbufFota, 0, sizeof(DLC_MatSPICheckbufFota));
							if (W25Q128JV_readData(DLC_MatSPIFlashPage * (fotaaddress + k), (uint8_t*)DLC_MatSPICheckbufFota, DLC_MatSPIFlashPage) == W25Q128JV_ERR_NONE) {
								if (memcmp(DLC_MatSPICheckbufFota, (fpt + DLC_MatSPIFlashPage * k), DLC_MatSPIFlashPage) == 0) {
									putst("VERFY OK\r\n");
								} else {
									DLC_MatFotaWriteNG = true;
									putst("VERFY NG\r\n");
								}
							} else {
								DLC_MatFotaWriteNG = true;
								putst("READ NG\r\n");
							}
						} else {
							DLC_MatFotaWriteNG = true;
							putst("PROG NG\r\n");
						}
					}
					DLC_MatSPIRemaindataFota = (0x400 - len) - (DLC_MatSPIFlashPage * k);	/* 1ページ未満の半端byte数 */
//					putst("DLC_MatSPIRemaindataFota3:");puthxs(DLC_MatSPIRemaindataFota);putcrlf();
					memcpy(DLC_MatSPIRemainbufFota, fpt + DLC_MatSPIFlashPage * k ,DLC_MatSPIRemaindataFota);	/* 半端byte保持バッファに保持 */
					DLC_MatSPIWritePageFota = k;	/* SPI書込みページインデックス保持 */
//					putst("RemainData3:\r\n");Dump(DLC_MatSPIRemainbufFota, sizeof(DLC_MatSPIRemainbufFota));putcrlf();
				} else {	/* データが1024byte未満の場合(現状ありえない) */
					putst("RecvData4:\r\n");
//					Dump(fpt, i - len);putcrlf();
					fotaaddress /= DLC_MatSPIFlashPage;
					for (k = 0; k <= ((i - len) / DLC_MatSPIFlashPage); k++) {
						if (W25Q128JV_programPage(fotaaddress + k, 0, (uint8_t*)(fpt + DLC_MatSPIFlashPage * k), DLC_MatSPIFlashPage, true) == W25Q128JV_ERR_NONE ){
							puthxw(DLC_MatSPIFlashPage * (fotaaddress + k));
							putst(":OK");putcrlf();
							memset(DLC_MatSPICheckbufFota, 0, sizeof(DLC_MatSPICheckbufFota));
							if (W25Q128JV_readData(DLC_MatSPIFlashPage * (fotaaddress + k), (uint8_t*)DLC_MatSPICheckbufFota, DLC_MatSPIFlashPage) == W25Q128JV_ERR_NONE) {
								if (memcmp(DLC_MatSPICheckbufFota, (fpt + DLC_MatSPIFlashPage * k), DLC_MatSPIFlashPage) == 0) {
									putst("VERFY OK\r\n");
								} else {
									DLC_MatFotaWriteNG = true;
									putst("VERFY NG\r\n");
								}
							} else {
								DLC_MatFotaWriteNG = true;
								putst("READ NG\r\n");
							}
						} else {
							DLC_MatFotaWriteNG = true;
							putst("PROG NG\r\n");
						}
					}
					if (DLC_MatFotaWriteNG == false) {	/* 書込みNGなし */
						DLCMatTimerClr( 0 );	/* タイマークリア */
					}
				}
			}
			DLC_MatResIdx = 0;
			return j;
		}
		else {
			putst("format err4\r\n");
			return -4;
		}
	}
	else
		putst("format err1\r\n");
	return -1;
}
void DLCMatBypass()
{
	while(1){
		uint8_t c;
		if( SERCOM0_USART_Read( &c, 1 )){				/* UARTから入力 */
			if( c == 0x03 || c == 0x1b )				/* ESC/CTRL-Cでexit */
				return;
			SERCOM0_USART_Read( &c, 1 );
			SERCOM5_USART_Write( &c, 1 );				/* MATcoreに出力 */
		}
		APP_delay(10);
		if( SERCOM5_USART_Read( &c, 1 )){				/* MATcoreから入力 */
			SERCOM0_USART_Write( &c, 1 );				/* UARTへ出力 */
			if( c == '\r' ){
				c = '\n';
				SERCOM0_USART_Write( &c, 1 );			/* UARTへ出力 */
			}
		}
		APP_delay(10);
	}
}
void DLCMatTest()
{
	char    key;
	while(1){
		putst("\r\nCore>");
		key = toupper( getch() );
		switch( key ){
		case 'A':
			DLCMatSend( "AT$SETAPN,soracom.io,sora,sora,CHAP\r" );
			break;
		case 'B':
			putst("UART<=>MATcore MODE!\r\n");
			DLCMatBypass();
			break;
		case 'C':
			DLCMatSend( "AT$CONNECT\r" );
			break;
		case 'D':
			DLCMatSend( "AT$DISCONNECT\r" );
			break;
		case 'L':
			DLCMatSend( "AT$CLOSE\r" );
			break;
		case  'M':
			putst("Msg=");
			MatMsgSend( c_get32b() );
			break;
		case 'N':
			DLCMatSend( "AT$NUM\r" );
			DLCMatSend( "AT$IMEI\r" );
			DLCMatSend( "AT$TIME\r" );
			break;
		case 'R':
			DLCMatSend( "AT$RSRP\r" );
			DLCMatSend( "AT$RSRQ\r" );
			DLCMatSend( "AT$RSSI\r" );
			DLCMatSend( "AT$SINR\r" );
			break;
		case 'O':
			DLCMatSend( "AT$OPEN\r" );
			break;
		case 'S':
			DLCMatSend( "AT$SETSERVER,karugamosoft.ddo.jp,9999\r" );
			break;
		case 'T':
			DLCMatSend( "AT$SETSERVER,beam.soracom.io,8888\r" );
			break;
		case 'U':
#if 1
			DLCMatPostConfig();
#else
			DLCMatSend( "AT$SEND,\"414243\"\r" );
#endif
			break;
		case 'V':
			DLCMatSend( "AT$RECV,1024\r" );
			break;
		case ' ':
			putst("Stat=");puthxb( DLC_MatState );putcrlf();
			Dump( (char*)DLC_MatLineBuf,64 );
			putst("idx=");puthxb( DLC_MatLineIdx );putcrlf();
			break;
		case '#':
			if( zLogOn ^= 1 )
				putst("LogOn\r\n");
			else
				putst("LogOff\r\n");
			break;
		case '$':
			memset( DLC_MatLineBuf,0,sizeof(DLC_MatLineBuf));
			DLC_MatLineIdx = 0;
			break;
		case '&':
			DLC_MatState = 100;
			break;
		case '!':
			if( DLC_MatSleep ^= 1 )
				PORT_GroupWrite( PORT_GROUP_1,0x1<<10,0 );
			else
				PORT_GroupWrite( PORT_GROUP_1,0x1<<10,-1 );
			break;
		case 0x03:
		case 0x1b:
			return;
		}
	}
}
void DLCFlashTest()
{
#if 0
	int		rt,k;
	char    key;
	while(1){
		uint8_t DmyData[256],Data[256];
		int	address;
		for( int i=0;i<256;i++ )
			DmyData[i] = i;
		putst("\r\nW:write R:read E:erase=>");
		key = toupper(getch());
		putst("\r\nAddress=>");address = c_get32b();
		switch( key ){
		case 'W':
			if( address == -1 ){
				for( int j=0;j<0x1000;j++ ){
					if( W25Q128JV_eraseSctor( j,true ) == W25Q128JV_ERR_NONE ){
						char line[20];
						putst("ERASE OK");putcrlf();
						sprintf(line, "%03X", (unsigned int)j);
						putst(line);putcrlf();
						APP_delay(300);
						address = (j << 4);								/* 0,0x10,0x20,0x30... */
						for( int i=0;i<16;i++ ){
							if( W25Q128JV_programPage( address++,(uint8_t)0,DmyData,(uint16_t)sizeof(DmyData),true ) == W25Q128JV_ERR_NONE ){
								putst( "PROG. OK\r\n" );
								sprintf( line, "%04X\r\n",(unsigned int)address );
								putst( line );
							}
							else
							    putst("PAGE NG\r\n");
						}
					}
					else {
						putst("ERASE NG\r\n");
					}
				}
			}
			else {
				address /= 0x100;
				for( int i=0;i<16;i++ ){
					if( W25Q128JV_programPage( address+i,0,(uint8_t*)DmyData,(uint16_t)sizeof(DmyData),true )== W25Q128JV_ERR_NONE ){
						char line[20];
						putst( "PROG. OK\r\n" );
						sprintf( line, "%04X\r\n",(unsigned int)address+i );
						putst( line );
					}
					else
						putst("PAGE NG\r\n");
				}
			}
			break;
		case 'R':
			if( address == -1 ){
			    for (int k=0; k<0x10000;k++){				/* 65万セクタ(256) */
					uint32_t addr = ((uint32_t)k << 8);
					if (W25Q128JV_readData(addr, Data, (uint16_t)sizeof(Data)) == W25Q128JV_ERR_NONE){
#if 0
						puthxw( addr );putcrlf();
						Dump( (char*)Data,sizeof( Data ) );
#else
						if( memcmp( Data,DmyData,sizeof( Data )) ){
							putst("Find NG=>");puthxw( addr );putcrlf();break;
						}
						else{
							puthxw( addr );putcrlf();
						}
#endif
					}
					else{
						putst("Read NG ");puthxw( addr );putcrlf();
					}
					APP_delay(2);
				}
			}
			else {
				rt = W25Q128JV_readDataFaster( address,(uint8_t*)DmyData, sizeof( DmyData ));
				if( !rt ){
					putcrlf();Dump( (char*)DmyData,sizeof( DmyData ) );
				}
				else {
					puthxb( rt );putcrlf();
				}
			}
			break;
		case 'E':
			if( address == -1 ){
	  			rt = W25Q128JV_eraseChip(true);
				if( !rt ){
					putst("OK\r\n");
				}
				else {
					puthxb( rt );putcrlf();
				}
			}
			else {
				rt = W25Q128JV_eraseSctor(address/0x1000, true);
				if( !rt ){
					putst("OK\r\n");
				}
				else {
					puthxb( rt );putcrlf();
				}
			}
			break;
		case 'B':
			for (k = 0; k < 4; k++) {	/* 指定アドレス～3ブロック消去 */
				char line[20];
				W25Q128JV_eraseBlock64(((address / 0x10000) + k), true);
				sprintf( line, "%X:ERASE OK\r\n",(unsigned int)((address / 0x10000) + k) );
				putst( line );
			}
			break;
		case 0x03:
		case 0x1b:
			return;
		}
	}
#endif
}
void DLCkarugamoTest()
{
	uint8_t c;
	char    key;
	char *VerPrint();
	putst( VerPrint() );
	putst( "\r\nMATcore Task Started." );
	DLCMatInit();
	PORT_GroupWrite( PORT_GROUP_1,0x1<<22,0 );
	while(1){
		putst("\r\nDLC>");
		key = getch();
		key = toupper(key);
		switch( key ){
		case '?':
			putst(help);
			break;
		case 'M':
			DLCMatTest();
			break;
		case 'I':
			putst("Read IO(1-7)=>");
			key = getch()-'1';
			putcrlf();puthxb(GPIOEXP_get(key));
			break;
		case 'L':
			putst("LED(1-3)=>");
			key = getch()-'1';
			putst("1:On 2:Off 3:Blink=>");
			c = getch();
			switch( c ){
			case '1':
				GPIOEXP_clear(key);
				break;
			case '2':
				GPIOEXP_set(key);
				break;
			case '3':
				GPIOEXP_set(key);
				break;
			}
			break;
		case 'O':
			putst("\r\nNum=>");
			PORT_GroupWrite( PORT_GROUP_1,0x1<<c_get32b(),0 );
			break;
		case 'U':
			putst("\r\nNum=>");
			PORT_GroupWrite( PORT_GROUP_1,0x1<<c_get32b(),-1 );
			break;
		case 'Y':
			putcrlf();
			puthxw( PORT_GroupRead( PORT_GROUP_1 ));
			break;
		case 'E':
			putst("Address=0x8000 Erased!\r\n");
			NVMCTRL_RowErase( 0x8000 );
			break;
		case 'F':
			DLCFlashTest();
			break;
		case 0x1b:
			Moni();
			break;
		}
	}
}
