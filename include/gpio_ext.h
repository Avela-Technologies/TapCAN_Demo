#ifndef GPIO_EXT_H
#define GPIO_EXT_H

#ifdef __cplusplus
extern "C" {
#endif

extern void fnGPIO_Init();
extern uint8_t get_gpi_1();
extern uint8_t get_gpi_2();
extern void set_gpo_3(uint8_t);
extern void set_gpo_4(uint8_t);
extern void set_gpo_5(uint8_t);
extern void set_gpo_beep(uint8_t);
extern void set_gpo_CANTerm(uint8_t);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif