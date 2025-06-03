#include <Arduino.h>
#include "TapCAN.h"
#include <Wire.h>
#include "display.h"
#include "CAN.h"
#include "touch.h"
#include "gpio_ext.h"
#include "anlg_out.h"
#include "anlg_in.h"
#include "pulse.h"

static void i2c_init();

void setup()
{ 
  Serial.begin(115200); 
  // Put LCD in Reset
  pinMode(LCD_RESET,OUTPUT);  
  digitalWrite(LCD_RESET,LOW);
  delay(10); 
  
  i2c_init();
  fnGPIO_Init(); //call after i2c init   
  fnDAC_Init();
  
  lv_init();
  // Release LCD Reset, before display init
  digitalWrite(LCD_RESET,HIGH);
  delay(10);
  
  display_init();  //call after LCD reset release 
  
  fnCTP_Init(); // call after dispay init and I2C init
  pinMode(LCD_BACKLIGHT,OUTPUT);  
  digitalWrite(LCD_BACKLIGHT,HIGH); //turn on LCD backlight
 
  fnAnlgIn_Init();
  fnPulse_Init();
  fnCAN_Init();
  delay(500);      
}

void loop()
{   
  fnCAN_Rx();
  lv_task_handler();
}

void i2c_init()
{
  Wire.setPins(I2C_SDA,I2C_SCL); 
  Wire.begin();
  Wire.setClock(400000);  
}
