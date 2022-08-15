/*
 * File:    wpfm.c
 * Author:  Interark Corp.
 * Summary: WPFM(code name "DLC_04") project common definition file.
 * Date:    2022/07/16 (R0)
 * Note:
 */


#include "wpfm.h"

/*
*   Global variables
*/
  // current operation mode and status
WPFM_OPERATION_MODE WPFM_operationMode = WPFM_OPERATION_MODE_MEASUREMENT;
WPFM_STATUS WPFM_status = WPFM_POWER_OFF;
bool WPFM_IsConnectedUSB = false;

  // current settings
WPFM_SETTING_PARAMERS MAIN_settingParameter =   // current setting parameters
{
    4,                      // measurement interval[sec]
    1,                      // communication interval [min]
    { SENSOR_KIND_1_3V, SENSOR_ERR_NOT_EXIST },     // sensor kinds
    false,                  // alert operation pause
    true,                   // alart operation enabled
    { { 2.298, 2.598 }, { 0.0, 0.0 } },     // alart upper limits
    { { 1.698, 1.398 }, { 0.0, 0.0 } },     // alart lower limits
    { { 1, 1 }, { 2, 2 } },         // alart chattring times
    { { 0.998, 2.998, 0.0, 0.0 }, { 0.0, 0.0, 0.0, 0.0 } },     // calibration upper values
    { { 0.998, 2.998, 0.0, 0.0 }, { 0.0, 0.0, 0.0, 0.0 } },     // calibration lower values
    { 3.0, 0.0 }, { 1.0, 0.0 },     // sensor upper/lower limit
    30,                     // communication timeout
    2                       // emergency alart timeout
};
uint16_t WPFM_measurementInterval;
uint16_t WPFM_communicationInterval;

  // for alert
time_t WPFM_lastEmergencyAlartTime;

  // for battery
time_t WPFM_startExchangingBatteryTime;
int WPFM_externalBatteryNumberInUse;
int WPFM_externalBatteryNumberToExchange;

  // last measured values and status
float WPFM_measuredValues[2];                // measured values - index 0: CH1/1: CH2 [MhPa..]
WPFM_ALERT_STATUS WPFM_alertStatuses[2];     // alert status - index 0: CH1/1: CH2
uint16_t WPFM_batteryVoltages[2];            // external battery voltage - index 0: External#1/1: External#2 [mV]
int16_t WPFM_temperatureOnBoard;             // temperature on board [x10 C]

  // last error
int WPFM_lastErrorNumber;
char *WPFM_lastErrorMessage;
