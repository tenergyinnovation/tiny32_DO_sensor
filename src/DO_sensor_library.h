/***********************************************************************
 * File         :     DO_sensor_library.h
 * Description  :     Library for DO sensor
 * Author       :     Tenergy Innovation Co., Ltd.
 * Date         :     17 July 2022
 * Revision     :     1.0
 * Rev1.0       :     Original 
 * website      :     http://www.tenergyinnovation.co.th
 * Email        :     uten.boonliam@innovation.co.th
 * TEL          :     089-140-7205
 ***********************************************************************/
#include <Arduino.h>
#include <SPI.h>



//Single-point calibration Mode=0
//Two-point calibration Mode=1
#define TWO_POINT_CALIBRATION 0

#define READ_TEMP (25) //* Current water temperature ℃, Or temperature sensor function

//Single point calibration needs to be filled CAL1_V and CAL1_T
#define CAL1_V (1600) //* mv (change here value from STEP1)
#define CAL1_T (25)   //℃
//Two-point calibration needs to be filled CAL2_V and CAL2_T
//CAL1 High temperature point, CAL2 Low temperature point
#define CAL2_V (1300) //mv
#define CAL2_T (15)   //℃

const uint16_t DO_Table[41] = {
    14460, 14220, 13820, 13440, 13090, 12740, 12420, 12110, 11810, 11530,
    11260, 11010, 10770, 10530, 10300, 10080, 9860, 9660, 9460, 9270,
    9080, 8900, 8730, 8570, 8410, 8250, 8110, 7960, 7820, 7690,
    7560, 7430, 7300, 7180, 7070, 6950, 6840, 6730, 6630, 6530, 6410};

/**************************************/
/*        define global variable      */
/**************************************/
uint8_t Temperaturet;
uint16_t DO;


/**************************************/
/*           define function          */
/**************************************/
int16_t readDO(uint32_t voltage_mv, uint8_t temperature_c);

 /***********************************************************************
 * FUNCTION:    readDO
 * DESCRIPTION: read DO sensor
 * PARAMETERS:  voltage_mv, temperature_c
 * RETURNED:    int16_t
 ***********************************************************************/
int16_t readDO(uint32_t voltage_mv, uint8_t temperature_c)
{
#if TWO_POINT_CALIBRATION == 0
  uint16_t V_saturation = (uint32_t)CAL1_V + (uint32_t)35 * temperature_c - (uint32_t)CAL1_T * 35;
  return (voltage_mv * DO_Table[temperature_c] / V_saturation);
#else
  uint16_t V_saturation = (int16_t)((int8_t)temperature_c - CAL2_T) * ((uint16_t)CAL1_V - CAL2_V) / ((uint8_t)CAL1_T - CAL2_T) + CAL2_V;
  return (voltage_mv * DO_Table[temperature_c] / V_saturation);
#endif
}



