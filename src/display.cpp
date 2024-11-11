#include "display.h"
#include "TapCAN.h"
#include <Wire.h>
#include "lvgl.h"
#include "ui.h"
#include "ui_user_code.h"
#define LGFX_USE_V1
#include <LovyanGFX.hpp>
#include "lgfx_spi.h"
#include "touch.h"


//display parameters
static const uint32_t screenWidth = LCD_WIDTH;
static const uint32_t screenHeight = LCD_HEIGHT;

static lv_disp_draw_buf_t disp_buf;
static lv_color_t buf[screenWidth * 10];
static lv_color_t buf2[screenWidth * 10];

lv_disp_drv_t disp_drv;
lv_indev_drv_t indev_drv;

LGFX lcd;

void my_disp_flush(lv_disp_drv_t*, const lv_area_t*, lv_color_t*);


void display_init()
{   
  lcd.init();  
  lcd.setRotation(0); 
  
  lv_disp_draw_buf_init(&disp_buf, buf, buf2, screenWidth * 10);
  
  /*Initialize the display*/
  lv_disp_drv_init(&disp_drv);
  disp_drv.hor_res = screenWidth;
  disp_drv.ver_res = screenHeight;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &disp_buf;
  lv_disp_drv_register(&disp_drv);
  
  /*Initialize the input device driver*/
  lv_indev_drv_init(&indev_drv);          /*Descriptor of a input device driver*/
  indev_drv.type = LV_INDEV_TYPE_POINTER; /*Touch pad is a pointer-like device*/
  indev_drv.read_cb = my_input_read;      /*Set your driver function*/
  lv_indev_drv_register(&indev_drv);      /*Finally register the driver*/

  ui_init();  
  ui_user_code_init();

  //start a 100 ms periodic timer for display label updates
  lv_timer_t* label_updt_tmr = lv_timer_create(label_updt, 100,NULL);

  lv_scr_load(ui_scrnHome);
}

void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{    
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);
  uint32_t len = w * h;
 
  lcd.startWrite();
  lcd.setAddrWindow(area->x1, area->y1, w, h); 
  lcd.writePixelsDMA(static_cast<uint16_t *>(&color_p->full), len, true); // Lovyan
  lcd.endWrite();  
  lv_disp_flush_ready(disp); /* Indicate you are ready with the flushing*/
}

