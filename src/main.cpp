#include <Arduino.h>
#include "TapCAN.h"
#include <Wire.h>
#include "lvgl.h"
#include "display.h"
#include "CAN.h"
#include "I2C.h"
#include "touch.h"
#include "gpio_ext.h"
#include "anlg_out.h"
#include "anlg_in.h"
#include "pulse.h"
#include "ui.h"

void setup()
{ 
  Serial.begin(115200); 
  
  i2c_init();

  display_init(); 
  touchscreen_init(); // call after dispay init and I2C init
  
  fnGPIO_Init(); //call after i2c init   
  fnDAC_Init();
  fnAnlgIn_Init();
  fnPulse_Init();
  fnCAN_Init();
  delay(500);      
}

void loop()
{   
  fnCAN_Rx();
  lv_timer_handler();
  #ifdef CONFIG_EEZ
  ui_tick();
  #endif
}


