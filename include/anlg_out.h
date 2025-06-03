#ifndef __ANLG_OUT_H
#define __ANLG_OUT_H

#include <Arduino.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void fnDAC_Init();
extern void set_DAC_val(uint8_t);

#ifdef __cplusplus
} /*extern "C"*/
#endif


#endif