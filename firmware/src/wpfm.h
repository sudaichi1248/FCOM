/*
 * File:    wpfm.h
 * Author:  Interark Corp.
 * Summary: WPFM(code name "DLC_04") project common header file.
 * Date:    2022/07/17 (R0)
 * Note:
 */

#ifndef WPFM_H
#define	WPFM_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "app.h"
#include "sensor.h"


/*
*   Macros
*/

/*
*   Symbols
*/
  // EIC pin
#define WPFM_RTC_INTERRUPT_PINA         EIC_PIN_13      // INTRA: Alarm_Mo interrupt pin
#define WPFM_RTC_INTERRUPT_PINB         EIC_PIN_14      // INTRB: Time update and Alarm_Wk interrupt pin
#define WPFM_TACTSW_INTERRUPT_PIN       EIC_PIN_4       // Tact switch interrupt pin
  // GPIO expander pins
#define WPFM_GPIO_LED1                  0               // LED1 (Low:on/High:Off)
#define WPFM_GPIO_EXT1_LED              1               // External battery LED1 (Low:on/High:off)
#define WPFM_GPIO_EXT2_LED              2               // External battery LED2 (Low:on/High:off)
#define WPFM_GPIO_RESERVED              3               // Reserved
#define WPFM_GPIO_CH1_EXT_PWR           4               // Disconnect external #1 power (Low:disconnect/High:connect)
#define WPFM_GPIO_CH2_EXT_PWR           5               // Disconnect external #2 power (Low:disconnect/High:connect)
#define WPFM_GPIO_CH1_PWR               6               // Control sensor #1 power (low:off/High:on)
#define WPFM_GPIO_CH2_PWR               7               // Control sensor #2 power (low:off/High:on)

/*
*   Types
*/

typedef struct {
    uint16_t        measurementInterval;                // 平時の測定間隔 [Sec]
    uint16_t        communicationInterval;              // 平時の通信間隔 [Sec]
    SENSOR_KIND     sensorKinds[2];                     // センサ種別[0:ch1/1:ch2]
    bool            alertOperationPause;                // アラート動作一時停止(true:一時停止/false:なし)
    bool            alertOperationEnabled;              // アラート動作有無(true:有効/false:無効)
    float           alertUpperLimits[2][2];             // アラート上限値[0:上限値1/1:上限値12][0:ch1/1:ch2] [V/mA]
    float           alertLowerLimits[2][2];             // アラート下限値[0:下限値1/1:下限値2][0:ch1/1:ch2] [V/mA]
    uint16_t        alertChatteringTimes[2][2];         // アラートチャタリング時間 [0:upper/1:lower][0:ch1/1:ch2] [Min]
    float           calibrationUpperValues[2][4];       // 上限の校正値[0:ch1/1:ch2][0-3:センサ種別] [V/mA]
    float           calibrationLowerValues[2][4];       // 下限の校正値[0:ch1/1:ch2][0-3:センサ種別] [V/mA]
    float           upperLimits[2];                     // 仕様上のセンサ出力の上限値[0:ch1/1:ch2] [-]
    float           lowerLimits[2];                     // 仕様上のセンサ出力の下限値[0:ch1/1:ch2] [-]
    uint16_t        communicationTimeout;               // 通信時のタイムアウト時間 [Sec]
    uint16_t        emergencyAlartTimeout;              // 警報タイムアウト時間 [Min]
} WPFM_SETTING_PARAMERS;
    // value of sensorKinds[] is used for index of calibrationUpperValues[] and calibrationLowerValues[]

typedef enum
{
    WPFM_OPERATION_MODE_MEASUREMENT = 0,    // 計測モード（通常モード）
    WPFM_OPERATION_MODE_NO_MEASUREMENT      // 非計測モード（設置モード）
} WPFM_OPERATION_MODE;      // 動作モード

typedef enum
{
    WPFM_POWER_OFF = 0,
    WPFM_STATUS_INITIALIZING,
    WPFM_STATUS_MEASUREMENT,
    WPFM_STATUS_EMERGENCY_ALART,
    WPFM_STATUS_SLEEP,
    WPFM_STATUS_EXCHANGING_BATTERY,
    WPFM_STATUS_INITIALIZING_SETTING,
    WPFM_STATUS_WAIT_COMMAND,
    WPFM_STATUS_PROCESSING_COMMAND
} WPFM_STATUS;              // 動作状態

typedef enum
{
    WPFM_ALERT_STATUS_NORMAL = 0,           // 通常
    WPFM_ALERT_STATUS_WARNING_ALERT,        // 注意
    WPFM_ALERT_STATUS_EMERGENCY_ALERT       // 警報
} WPFM_ALERT_STATUS;        // アラート状態


/*
*   Global variables (define on wpfm.c)
*/
  // current operation
extern WPFM_OPERATION_MODE WPFM_operationMode;
extern WPFM_STATUS WPFM_status;
extern bool WPFM_IsConnectedUSB;
  // current settings
extern WPFM_SETTING_PARAMERS MAIN_settingParameter; // current setting parameters
extern uint16_t WPFM_measurementInterval;
extern uint16_t WPFM_communicationInterval;
  // for alert
extern time_t WPFM_lastEmergencyAlartTime;
  // for battery
extern time_t WPFM_startExchangingBatteryTime;
extern int WPFM_externalBatteryNumberInUse;
extern int WPFM_externalBatteryNumberToExchange;
  // last measured values and status
extern float WPFM_measuredValues[2];                // measured values - index 0: CH1/1: CH2 [MhPa..]
extern WPFM_ALERT_STATUS WPFM_alertStatuses[2];     // alert status - index 0: CH1/1: CH2
extern uint16_t WPFM_batteryVoltages[2];            // external battery voltage - index 0: External#1/1: External#2 [mV]
extern int16_t WPFM_temperatureOnBoard;             // temperature on board [x10 C]
// last error
extern int WPFM_lastErrorNumber;
extern char *WPFM_lastErrorMessage;

#ifdef	__cplusplus
}
#endif

#endif	/* WPFM_H */
