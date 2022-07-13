/***********************************************************************
 * Project      :     tiny32_v3_DO_sensor (STEP1 calibration)
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

/**************************************/
/*       eeprom address define        */
/**************************************/

/**************************************/
/*        define global variable      */
/**************************************/

/**************************************/
/*           define function          */
/**************************************/

/***********************************************************************
 * FUNCTION:    setup
 * DESCRIPTION: setup process
 * PARAMETERS:  nothing
 * RETURNED:    nothing
 ***********************************************************************/
void setup()
{
    Serial.begin(115200);
    Serial.printf("**** tiny32_v3_DO_sensor (STEP1 calibration) ****\r\n");

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

  Serial.printf("Voltage(v): %.2f , Voltage(mv): %d*\r\n",volts0,raw);
  Serial.println("-----------------------------------------------------------");


  delay(1000);
}


