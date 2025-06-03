#ifndef __PULSE_H
#define __PULSE_H

#include <Arduino.h>

extern void fnPulse_Init();
extern uint32_t GetPulseFrequency();

#ifdef __cplusplus
extern "C" {
#endif

extern void SetPWMOutFreq(int8_t);
extern void SetPWMOutDC(int8_t);

#ifdef __cplusplus
} /*extern "C"*/
#endif


#endif