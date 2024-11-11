#ifndef _TOUCH_H
#define _TOUCH_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

extern void fnCTP_Init();
extern void my_input_read(lv_indev_drv_t*, lv_indev_data_t*);

#ifdef __cplusplus
}
#endif

#endif
