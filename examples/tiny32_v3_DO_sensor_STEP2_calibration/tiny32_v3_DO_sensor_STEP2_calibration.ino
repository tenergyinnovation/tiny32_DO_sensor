/***********************************************************************
 * Project      :     tiny32_v3_DO_sensor (STEP2 calibration)
 * Description  :     Calibration Dissolved Oxygen Probe
 *                    https://wiki.dfrobot.com/Gravity__Analog_Dissolved_Oxygen_Sensor_SKU_SEN0237#target_3
 * Hardware     :     tiny32_v3         
 * Author       :     Tenergy Innovation Co., Ltd.
 * Date         :     04/07/2022
 * Revision     :     1.0
 * Rev1.0       :     Origital
 * website      :     http://www.tenergyinnovation.co.th
 * Email        :     admin@innovation.co.th
 * TEL          :     +66 82-380-3299
 ***********************************************************************/
#include <Arduino.h>
#include <tiny32_v3.h>
#include <SPI.h>
#include <Adafruit_ADS1X15.h>


/**************************************/
/*          Firmware Version          */
/**************************************/
String version = "0.1";

/**************************************/
/*        define object variable      */
/**************************************/
tiny32_v3 mcu;
Adafruit_ADS1115 ads;  /* Use this for the 16-bit version */
                       /* ADDR pin short to GND default address = 0x48*/ 

/**************************************/
/*            GPIO define             */
/**************************************/


/**************************************/
/*       Constand define value        */
/**************************************/
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
/*       eeprom address define        */
/**************************************/

/**************************************/
/*        define global variable      */
/**************************************/
uint8_t Temperaturet;
uint16_t DO;

/**************************************/
/*           define function          */
/**************************************/
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



/***********************************************************************
 * FUNCTION:    setup
 * DESCRIPTION: setup process
 * PARAMETERS:  nothing
 * RETURNED:    nothing
 ***********************************************************************/
void setup()
{
    Serial.begin(115200);
    Serial.printf("**** tiny32_v3_DO_sensor (STEP2 calibration) ****\r\n");

    if (!ads.begin()) {
        Serial.println("Failed to initialize ADS1115 can't interface.");
        mcu.buzzer_beep(4);
        while (1);
    }

    mcu.buzzer_beep(2);
    mcu.TickBlueLED(0.5);

}

 /***********************************************************************
 * FUNCTION:    loop
 * DESCRIPTION: loop process
 * PARAMETERS:  nothing
 * RETURNED:    nothing
 ***********************************************************************/
void loop()
{
  int16_t adc0;
  float volts0;
  uint32_t raw;

  adc0 = ads.readADC_SingleEnded(0);
  volts0 = ads.computeVolts(adc0);
  raw = volts0*1000;
  Temperaturet = (uint8_t)READ_TEMP;

  // Serial.printf("Voltage(v): %.2f , Voltage(mv): %d*\r\n",volts0,raw);

  Serial.print("Temperaturet:\t" + String(Temperaturet) + "\t");
  Serial.print("ADC Voltage:\t" + String(raw) + "\t");
  Serial.println("DO:\t" + String(readDO(raw, Temperaturet)) + "\t");

  Serial.println("-----------------------------------------------------------");


  delay(1000);
}


