/*
 * File:    sensor.h
 * Author:  Interark Corp.
 * Summary: Analog Sensor control header file.
 * Date:    2022/06/26 (R0)
 * Note:
 */

#ifndef SENSOR_H
#define	SENSOR_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "definitions.h"
#include "app.h"

/*
*   Types
*/
typedef enum {
    SENSOR_KIND_1_3V = 0,       // Voltage(1-3V) output sensor
    SENSOR_KIND_1_5V,           // Voltage(1-5V) output sensor
    SENSOR_KIND_0_20MA,         // Current(0-20mA) output sensor
    SENSOR_KIND_4_20MA,         // Current(4-20mA) output sensor
    SENSOR_KIND_NOT_PRESENT     // Sensor is not present
} SENSOR_KIND;

/*
*   Error codes
*/
#define SENSOR_ERR_NONE             0           // Success (no error)
#define SENSOR_ERR_PARAM            (-1)        // Parameter error
#define SENSOR_ERR_ADC              (-2)        // ADC error
#define SENSOR_ERR_NOT_EXIST        (-10)       // Sensor is not exist

// Channel number
#define SENDOR_CHANNEL_IN1          ADC_POSINPUT_PIN3       // AIN[3]/PB09
#define SENDOR_CHANNEL_IN2          ADC_POSINPUT_PIN4       // AIN[4]/PA04
#define SENSOR_EXTERNAL_BATTERY1    ADC_POSINPUT_PIN0       // AIN[0]/PA02
#define SENSOR_EXTERNAL_BATTERY2    ADC_POSINPUT_PIN2       // AIN[2]/PB08

/*
*   Functions
*/
extern int SENSOR_readSensorOutput(int sensorNo, SENSOR_KIND kind, float lower, float upper, float *result_p);
extern int SENSOR_readExternalVoltage(int externalNo, uint16_t *voltage_p);
extern int SENSOR_updateCariblationValues(int sensorNo, float calibrationUpperValue, float calibrationLowerValue);

#ifdef	__cplusplus
}
#endif

#endif	/* SENSOR_H */
