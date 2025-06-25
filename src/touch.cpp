#include <Arduino.h>
#include "Adafruit_FT6206.h"
#include "lvgl.h"
#include "touch.h"
#include "TapCAN.h"

// The FT6206 uses hardware I2C (SCL/SDA)
Adafruit_FT6206 ctp = Adafruit_FT6206();

lv_indev_drv_t indev_drv;

void my_touchpad_read(lv_indev_drv_t*, lv_indev_data_t*);

void touchscreen_init()
{
  ctp.begin();

  /*Initialize the input device driver*/
  lv_indev_drv_init(&indev_drv);          /*Descriptor of a input device driver*/
  indev_drv.type = LV_INDEV_TYPE_POINTER; /*Touch pad is a pointer-like device*/
  indev_drv.read_cb = my_touchpad_read;      /*Set your driver function*/
  lv_indev_drv_register(&indev_drv);      /*Finally register the driver*/
}

void my_touchpad_read( lv_indev_drv_t * indev, lv_indev_data_t * data )
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

