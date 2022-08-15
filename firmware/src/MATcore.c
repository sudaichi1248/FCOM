//須田編集
#include <stdio.h>
#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include <ctype.h>
#include <string.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                // SYS function prototypes
#include "moni.h" 
#include "gpioexp.h" 
#include "w25q128jv.h"
void command_main(void);
void DLCMatState();
void _GO_IDLE(){	command_main();DLCMatState();SYS_Tasks();}
void Moni();
void DLCMatConfigDefault(),DLCMatStatusDefault(),DLCMatReortDefault();
void DLCMatPostConfig(),DLCMatPostStatus(),DLCMatPostReport();
extern	char s_command_version[];
int DLCMatRecvDisp();
#define MAIN_VERSION "Ver 00.10 "
char 	_Main_version[32] = {MAIN_VERSION};
char 	zLogOn=1;
char 	DLC_MatSleep;
char 	DLC_MatResBuf[2000];
int	 	DLC_MatResIdx;
uchar	DLC_MatLineBuf[4000];
int		DLC_MatLineIdx;
uchar	DLC_Matfact,DLC_MatState;
char	DLC_MatDateTime[32];
char	DLC_MatRadioDensty[64];
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
void DLCMatInit()
{
	strcat( _Main_version,__DATE__ );
	strcat( _Main_version," " );
	strcat( _Main_version,__TIME__ );
	DLCMatConfigDefault();
	DLCMatStatusDefault();
	DLCMatReortDefault();
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
#define		MATC_FACT_HTTP	10
#define		MATC_FACT_TO	11
#define		MATC_FACT_WUP	12
#define		MATC_FACT_FOTA	13
#define		MATC_FACT_FTP	14
#define		MATC_FACT_SLP	15
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
	APP_delay(3000);
	DLC_MatState = MATC_STATE_IDLE;
}
void MTVrT()
{
	DLC_MatLineIdx = 0;
	DLCMatSend( "AT$VER\r" );
	APP_delay(1000);
}
void MTVer()
{
	DLC_MatLineIdx = 0;
	DLCMatSend( "AT$IMEI\r" );
	DLC_MatState = MATC_STATE_IMEI;
}
void MTimei()
{
	DLC_MatLineIdx = 0;
	DLCMatSend( "AT$SETAPN,soracom.io,sora,sora,PAP\r" );
	DLC_MatState = MATC_STATE_APN;
}
void MTapn()
{
	DLC_MatLineIdx = 0;
//	DLCMatSend( "AT$SETSERVER,karugamosoft.ddo.jp,9999\r" );
	DLCMatSend( "AT$SETSERVER,beam.soracom.io,8888\r" );
	DLC_MatState = MATC_STATE_SVR;
}
void MTserv()
{
	DLC_MatLineIdx = 0;
	DLCMatSend( "AT$CONNECT\r" );
	DLC_MatState = MATC_STATE_CONG;
}
void MTcong()
{
	DLC_MatLineIdx = 0;
	DLCMatSend( "AT$CONNECT?\r" );
	DLC_MatState = MATC_STATE_COND;
}
void MTtime()
{
	memcpy( DLC_MatDateTime,DLC_MatLineBuf,DLC_MatLineIdx );
	DLC_MatLineIdx = 0;
	DLCMatSend( "AT$TIME\r" );
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
	DLC_MatState = MATC_STATE_OPN1;
}
void MTcnfg()
{
	DLC_MatLineIdx = 0;
	DLCMatPostConfig();
	DLC_MatState = MATC_STATE_CNFG;
}
void MTrecv()
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
	DLC_MatState = MATC_STATE_RPT;
}
void MTcls3()
{
	DLC_MatLineIdx = 0;
	DLC_MatSleep = 1;
	PORT_GroupWrite( PORT_GROUP_1,0x1<<10,0 );
	DLC_MatState = MATC_STATE_SLP;
}
void MTslp0()
{
	DLC_MatLineIdx = 0;
	putst("【Sleep】\r\n");
}
void MTwake()
{
	PORT_GroupWrite( PORT_GROUP_1,0x1<<10,-1 );
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
void	 (*MTjmp[16][19])() = {
/*					  0         1       2      3       4       5       6       7       8       9       10      11      12      13      14      15      16      17   18     */
/*				  	 INIT    IDLE    IMEI    APN     SVR     CONG    COND    OPN1    CNFG    OPN2    STAT    OPN3    REPT    SLEEP   FOAT    FCON    FTP     MNT     ERR   */
/* MATCORE RDY 0 */{ MTRdy,  MTRdy,  MTRdy,  MTRdy,  MTRdy,  MTRdy,  MTRdy,  MTRdy,  MTRdy,  MTRdy,  MTRdy,  MTRdy,  MTRdy,  MTRdy,  MTRdy,  MTRdy,  MTRdy,  MTRdy,  MTRdy  },
/* ERROR       1 */{ ______, MTVrT,  ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______ },
/* $VER		   2 */{ ______, MTVer,  ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______ },
/* $NUM		   3 */{ ______, ______, MTimei, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______ },
/* OK          4 */{ ______, ______, ______, MTapn,  MTserv, MTcong, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______ },
/* CONNECT:1   5 */{ ______, ______, ______, ______, ______, ______, MTtime, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______ },
/* $TIME       6 */{ ______, ______, ______, ______, ______, ______, MTrsrp, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______ },
/* $RSRP       7 */{ ______, ______, ______, ______, ______, ______, MTopn1, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______ },
/* $OPEN       8 */{ ______, ______, ______, ______, ______, ______, ______, MTcnfg, ______, MTstst, ______, MTrprt, ______, ______, ______, ______, ______, ______, ______ },
/* $CLOSE      9 */{ ______, ______, ______, ______, ______, ______, ______, ______, MTcls1, ______, MTcls2, ______, MTcls3, ______, ______, ______, ______, ______, ______ },
/* HTTP       10 */{ ______, ______, ______, ______, ______, ______, ______, ______, MTrecv, ______, MTrecv, ______, MTrecv, ______, ______, ______, ______, ______, ______ },
/* TimOut     11 */{ ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______ },
/* WAKEUP     12 */{ ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, MTwake, ______, ______, ______, ______, ______ },
/* FOTA       13 */{ ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______ },
/* FTP        14 */{ ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______ },
/* $SLEEP     15 */{ ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, MTslp0, ______, ______, ______, ______, ______ },
							};
void DLCMatState()
{
	char	*p;
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
		if( strstr( (char*)DLC_MatLineBuf,"$NUM:" )){
			DLC_Matfact = MATC_FACT_NUM;
		}
	}
	if( DLC_MatLineIdx >= 22 ){								/* $IMEI:356766100967880 */
		if( strstr( (char*)DLC_MatLineBuf,"$IMEI:" )){
			DLC_Matfact = MATC_FACT_NUM;
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
		if( strstr( (char*)DLC_MatLineBuf,"$CONNECT:1\r" )){
			DLC_Matfact = MATC_FACT_CON;
		}
	}
	if( DLC_MatLineIdx >= 24 ){								/* $TIME:22/08:03,18:16:32 */
		p = strstr( (char*)DLC_MatLineBuf,"$TIME:2" );
		if( p ){
			if( strchr( p,'\r' ))							/* <cr>まで受信済み */
				DLC_Matfact = MATC_FACT_TIM;
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
		if( strstr( (char*)DLC_MatLineBuf,"$WAKE\r" )){
			DLC_Matfact = MATC_FACT_OPN;
		}
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
	if( DLC_MatLineIdx >= 15 ){
		DLC_MatLineBuf[DLC_MatLineIdx] = 0;
		if( strstr( (char*)DLC_MatLineBuf,"$RECVDATA:" )){
			p = strchr( (char*)DLC_MatLineBuf,'\"' );
			if( p > 0 ){
				if( strstr( p+2,"\"\r" )){
					DLC_Matfact = MATC_FACT_HTTP;
				}
			}
		}
	}
	if( DLC_Matfact == 0xff ){
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
	if( DLC_Matfact != 0xff ){
		putst("【");puthxb( DLC_Matfact );putch(':');puthxb( DLC_MatState );putst("】\r\n");
		(*MTjmp[DLC_Matfact][DLC_MatState])();
	}
}
bool command_getch(char * character_p)
{
	bool result = false;
	if (APP_readUSB( (uint8_t*)character_p, 1)) {
		result = true;
	}
	return result;
}
bool command_putch(char character)
{
	bool result = false;
	if (APP_writeUSB( (uint8_t const*)&character, 1)) {
	    result = true;
	}
	return result;
}
#define command_COMMAND_BUFFER_SIZE 128
typedef struct {
    int write_index;
    int read_index;
    char buffer[command_COMMAND_BUFFER_SIZE];
} command_command;
static command_command s_command_command;
//-----------------------------------------------------------------------------
// 受信バッファから1Line取得
//-----------------------------------------------------------------------------
bool command_sci_get_line(void)
{
	char c;
	bool result = false;
	while (command_getch(&c) == true) {
		command_putch(c);
		if (c == '\n') {				// ラインフィード(無視)
			continue;
		}
		if (c == '\b') {				// バックスペース
			if (s_command_command.write_index) {
				s_command_command.write_index--;
			}
			continue;
		}
		s_command_command.buffer[s_command_command.write_index++] = toupper(c);
		if (c == '\r') {				// コマンド検出
			s_command_command.buffer[s_command_command.write_index] = 0x00; 
			s_command_command.write_index = 0;
			result = true;
			break;
		}
	}
	return result;
}
void command_software_reset(void)
{
#if 0
	uint32_t app_start_address;
	app_start_address = *(uint32_t *) (4);
	SYS_INT_Disable(); /* 割り込み禁止 */
	/* Rebase the Stack Pointer */
	__set_MSP(*(uint32_t *) 0);
	/* Rebase the vector table base address */
	SCB->VTOR = ((uint32_t) 0);
	/* Jump to application Reset Handler in the application */
	asm("bx %0"::"r"(app_start_address));
#else
	NVMCTRL_RowErase( 0x8000 );
	__NVIC_SystemReset();
#endif
}
void command_main(void)
{
	unsigned char *p;
	p = (unsigned char*)0x20007fff;
	while (command_sci_get_line() == true) {   // コマンドバッファから１line取得
		if (strcmp(s_command_command.buffer , "!!DOWNLOADFIRM\r") == 0) {
			*p = 1;
			APP_printlnUSB("\r\nOK\r\n");
			command_software_reset();
			break;
		}
		if (strcmp(s_command_command.buffer , "!!DOWNLOADBOOT\r") == 0) {
			*p = 2;
			APP_printlnUSB("\r\nOK\r\n");
			command_software_reset();
			break;
		}
		if (strcmp(s_command_command.buffer , "!!VERSION\r") == 0) {
			APP_printlnUSB( _Main_version );
			break;
		}
		if (strcmp(s_command_command.buffer , "!!RESET\r") == 0) {
			APP_printlnUSB("\r\nOK\r\n");
			command_software_reset();
			break;
		}
		if (memcmp(s_command_command.buffer , "AT", 2) == 0) {
			APP_printlnUSB("\r\nOK\r\n");
			break;
		}
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
	char	Time[19];
	float	Value_ch1;
	float	Value_ch2;
	char	Alert[2];
} DLC_MatReportData[100];
int	DLC_MatReportStack;
void DLCMatConfigDefault()
{
	DLC_MatConfigPara.LoggerSerialNo 		= 3423423;
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
	DLC_MatSgtatusPara.LoggerSerialNo 		= 4324232;
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
		strcpy( DLC_MatReportData[i].Time,"2022-07-05 10:16:00" );
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
//	strcat( http_tmp,"{" );
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
//	i = (int)(strchr(http_tmp,'}')-strchr(http_tmp,'{'));
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
	strcpy( http_tmp,http_Head );
//	strcat( http_tmp,"{" );
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
//	i = (int)(strchr(http_tmp,'}')-strchr(http_tmp,'{'));
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
void DLCMatPostReport()
{
	char	tmp[48],n,*p;
	int		i;
	strcpy( http_tmp,http_Head );
//	strcat( http_tmp,"{" );
	strcat( http_tmp,"{\"Report\":{" );
	sprintf( tmp,"\"Time\":%s,"			,DLC_MatReportData[0].Time );				strcat( http_tmp,tmp );
	sprintf( tmp,"\"Value_ch1\":%f,"	,DLC_MatReportData[0].Value_ch1 );			strcat( http_tmp,tmp );
	sprintf( tmp,"\"Value_ch2\":%f,"	,DLC_MatReportData[0].Value_ch2 );			strcat( http_tmp,tmp );
	sprintf( tmp,"\"Alert\":%c%c,"		,DLC_MatReportData[0].Alert[0],DLC_MatReportData[0].Alert[1] );				strcat( http_tmp,tmp );
	strcat( http_tmp,"}}" );
//	i = (int)(strchr(http_tmp,'}')-strchr(http_tmp,'{'));
	i = (int)(strchr(http_tmp,'}')-strstr(http_tmp,"{\"Report\":{"))+1;
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
	int		rt;
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
