/***********************************************************************
 * Project      :     tiny32_v3_DO_sensor
 * Description  :     Calibration Dissolved Oxygen Probe
 *                    https://wiki.dfrobot.com/Gravity__Analog_Dissolved_Oxygen_Sensor_SKU_SEN0237#target_3
 * Hardware     :     tiny32_v3         
 * Author       :     Tenergy Innovation Co., Ltd.
 * Date         :     04/07/2022
 * Revision     :     1.0
 * Rev1.0       :     Origital
 * website      :     http://www.tenergyinnovation.co.th
 * Email        :     admin@innovation.co.th
 * TEL          :     +66 82-308-3299
 ***********************************************************************/
#include <Arduino.h>
#include <tiny32_v3.h>
#include <SPI.h>
#include <Adafruit_ADS1X15.h>
#include <DO_sensor_library.h>


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
float DO_read_sensor(uint16_t channel);


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

  float _DO_value = DO_read_sensor(0);
  Serial.printf("DO : %.3f mg/L\r\n",_DO_value);
  Serial.println("-----------------------------------------------------------");


  delay(1000);
}


 /***********************************************************************
 * FUNCTION:    DO_read_sensor
 * DESCRIPTION: Read DO (Dissolved_Oxygen_Sensor)
 * PARAMETERS:  channel of ADC [0-3]
 * RETURNED:    DO float
 ***********************************************************************/
float DO_read_sensor(uint16_t channel)
{
    
    int16_t _adc; //ค่า raw data ที่ได้จากโมดูล
    float _volts; //ค่า actual voltage
    uint32_t _raw; //ค่า voltage * 1000 สำหรับเอาไปใส่ให้ค่าฟังก์ชั่นแปรง DO
    float _read_DO_value;
    uint8_t _temperature_c = (uint8_t)READ_TEMP;

    if((channel < 0) || (channel > 3))
    {
        Serial.printf("Error: Out of range of channel [0-3]!!\r\n");
        return -1;
    }
    else
    {
        _adc = ads.readADC_SingleEnded(channel);
        _volts = ads.computeVolts(_adc);
        _raw = _volts*1000;
        // Serial.printf("raw = %d\r\n",_raw);
        _read_DO_value = (float)readDO(_raw, _temperature_c)*0.001;
        // Serial.printf("DO : %.3fmg/L\r\n",_read_DO_value);
        return _read_DO_value;
    }
}