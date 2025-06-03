#include <Arduino.h>
#include "Adafruit_FT6206.h"
#include "touch.h"
#include "TapCAN.h"

// The FT6206 uses hardware I2C (SCL/SDA)
Adafruit_FT6206 ctp = Adafruit_FT6206();

void fnCTP_Init()
{
  ctp.begin();
}

void my_input_read(lv_indev_drv_t *drv, lv_indev_data_t *data)
{  
  TS_Point p = ctp.getPoint();
  
  #if DEBUG_TOUCH
  p.x = map(p.x, 0, LCD_WIDTH, LCD_WIDTH, 0);
  p.y = map(p.y, 0, LCD_HEIGHT, LCD_HEIGHT, 0);
  Serial.print("X: ");Serial.print(p.x);
  Serial.print(" Y: ");Serial.println(p.y);
  #endif

  if (ctp.touched())
  {    
    data->state = LV_INDEV_STATE_PRESSED;
    data->point.x = p.x;
    data->point.y = p.y; 
  }
  else
  {
    data->state = LV_INDEV_STATE_RELEASED;    
  }   
}