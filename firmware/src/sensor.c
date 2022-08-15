/*
 * File:    sensor.c
 * Author:  Interark Corp.
 * Summary: Analog Sensor control implementation file.
 * Date:    2022/07/17 (R0)
 * Note:    Points to be adjusted where ""@tune" is listed
 */


#include "debug.h"
#include "wpfm.h"
#include "util.h"
#include "gpioexp.h"
#include "sensor.h"

/*
*   Symbols and Constants
*/
#define NUM_COUNTS          3               // The number of times the value is actually read in one measurement (@tune)
#define SHUNT_REGISTANCE    150             // for current output sensor [ohm]

const float _SENSOR_conversionFactor = 0.24743982;      // Conversion to voltage factor [mV/LSB]
const float _SENSOR_dividedRatioOfVoltageSensor = 1.6666667;
const float _SENSOR_dividedRatioOfExternalBattery = 1.5;
/**
const float _SENSOR_conversionFactor = ((3280.0 / 1480.0) / 4095.0) * 2.0;      // Conversion to voltage factor [mV/LSB]
const float _SENSOR_dividedRatioOfVoltageSensor = 1.0;
const float _SENSOR_dividedRatioOfExternalBattery = 1.0;
**/

/*
*   Local(static) variables
*/
static float _SENSOR_calibrationCoefficients[2][2];        // calibration coefficient values [0:CH1/1:CH2] [0:upper/1:lower]

/*
*   local(static) functions
*/
static float SENSOR_readVoltage(void);

int SENSOR_readSensorOutput(int sensorNo, SENSOR_KIND kind, float lower, float upper, float *result_p)
{
    uint32_t powerPin = 0;
    switch (sensorNo)
    {
        case 1:
            ADC_ChannelSelect(SENDOR_CHANNEL_IN1, ADC_NEGINPUT_GND);
            powerPin = WPFM_GPIO_CH1_PWR;
            break;
        case 2:
            ADC_ChannelSelect(SENDOR_CHANNEL_IN2, ADC_NEGINPUT_GND);
            powerPin = WPFM_GPIO_CH2_PWR;
            break;
        default:
            return (SENSOR_ERR_PARAM);
    }

    float result = 0.0, volt = 0.0, mA = 0.0;
    switch (kind)
    {
        case SENSOR_KIND_1_3V:
            // power on sensor
            UTIL_GPIO_set(powerPin);
            APP_delay(20);      // wait a little(@tune)
            // read voltage using ADC
            volt = SENSOR_readVoltage() * _SENSOR_dividedRatioOfVoltageSensor;
            // power off sensor
            GPIOEXP_clear(powerPin);
            // convert to physical quantity
            //result = UTIL_map(volt, 0.0, 3.27, lower, upper);  // for testing
            result = UTIL_map(volt, _SENSOR_calibrationCoefficients[sensorNo-1][1], _SENSOR_calibrationCoefficients[sensorNo-1][0], lower, upper);
            break;
        case SENSOR_KIND_1_5V:
            // read voltage using ADC
            volt = SENSOR_readVoltage() * _SENSOR_dividedRatioOfVoltageSensor;
            // convert to physical quantity
            result = UTIL_map(volt, _SENSOR_calibrationCoefficients[sensorNo-1][1], _SENSOR_calibrationCoefficients[sensorNo-1][0], lower, upper);
            break;
        case SENSOR_KIND_0_20MA:
            // read voltage using ADC
            volt = SENSOR_readVoltage();
            // convert to result[mV -> mA]
            mA = (volt / (float)SHUNT_REGISTANCE) * 1000.0;
            // convert to physical quantity
            result = UTIL_map(mA,  _SENSOR_calibrationCoefficients[sensorNo-1][1],  _SENSOR_calibrationCoefficients[sensorNo-1][0], lower, upper);
            break;
        case SENSOR_KIND_4_20MA:
            // read voltage using ADC
            volt = SENSOR_readVoltage();
            // convert to result[mV -> mA]
            mA = (volt / (float)SHUNT_REGISTANCE) * 1000.0;
            // convert to physical quantity
            result = UTIL_map(mA,  _SENSOR_calibrationCoefficients[sensorNo-1][1],  _SENSOR_calibrationCoefficients[sensorNo-1][0], lower, upper);
            break;
        case SENSOR_KIND_NOT_PRESENT:
            // specified sensor is not exist.
            return (SENSOR_ERR_NOT_EXIST);
        default:
            return (SENSOR_ERR_PARAM);
    }

    *result_p = result;

    return (SENSOR_ERR_NONE);
}

int SENSOR_readExternalVoltage(int externalNo, uint16_t *voltage_p)
{
    switch (externalNo)
    {
        case 1:
            ADC_ChannelSelect(SENSOR_EXTERNAL_BATTERY1, ADC_NEGINPUT_GND);
            break;
        case 2:
            ADC_ChannelSelect(SENSOR_EXTERNAL_BATTERY2, ADC_NEGINPUT_GND);
            break;
        default:
            return (SENSOR_ERR_PARAM);
    }

    float result = SENSOR_readVoltage() * _SENSOR_dividedRatioOfExternalBattery;

    *voltage_p = (uint16_t)(result * 1000.0);     // convert result from volt to millivolt

    return (SENSOR_ERR_NONE);
}

int SENSOR_updateCariblationValues(int sensorNo, float calibrationUpperValue, float calibrationLowerValue)
{
    int index = 0;
    switch (sensorNo)
    {
        case 1:
            index = 0;
            break;
        case 2:
            index = 1;
            break;
        default:
            return (SENSOR_ERR_PARAM);
    }

    _SENSOR_calibrationCoefficients[index][0] = calibrationUpperValue / _SENSOR_dividedRatioOfVoltageSensor;
    _SENSOR_calibrationCoefficients[index][1] = calibrationLowerValue / _SENSOR_dividedRatioOfVoltageSensor;

    return (SENSOR_ERR_NONE);
}

static float SENSOR_readVoltage(void)
{
    ADC_Enable();

    uint32_t sum = 0;
    for (int i = 0; i < NUM_COUNTS; i++)
    {
        ADC_ConversionStart();
        while (! ADC_ConversionStatusGet())
            ;
        sum += ADC_ConversionResultGet();

        APP_delay(10);  // wait a little (@tune)
    }

    ADC_Disable();

    float volt = ((float)sum / (float)NUM_COUNTS) * _SENSOR_conversionFactor;
    return (volt);
}
