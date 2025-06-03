#ifndef _CAN_H_
#define _CAN_H_

#include <Arduino.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct CAN_Msg_t
{    
    long unsigned int ID;
    unsigned char len;
    unsigned char arrData[8];
}CAN_Msg_t;

extern CAN_Msg_t sCAN_TxMsg;

extern CAN_Msg_t sCAN_RxMsg;
extern uint32_t CAN_FilterID;
extern uint32_t deltatime;
extern char RxDataString[];
extern boolean bCAN_RxActv;

extern void fnCAN_Init();
extern void fnCAN_apply_filterID();
extern void fnCAN_cntrl_Rx();
extern void fnCAN_Rx();
extern void fnCAN_Tx();

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif