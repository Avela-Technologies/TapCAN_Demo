#include "ui_interface.h"
#include "TapCAN.h"
#include "lvgl.h"
#include "ui.h"
#include "anlg_in.h"
#include "pulse.h"
#include "gpio_ext.h"
#include "CAN.h"
#ifdef CONFIG_EEZ
#include "screens.h"
#endif

/* This file contains manually generated code to interface with the auto-generated UI code */

/*Create a custom keyboard map - this is not achievable using squareline or eez studio */

static const char * kb_map[] = {"7", "8", "9", "A", "B", "C", "\n",
                                "4", "5", "6", "D", "E", "F", "\n",
                                "1", "2", "3", LV_SYMBOL_BACKSPACE,"\n",
                                "0", LV_SYMBOL_OK, NULL
                                };

/*Set the relative width of the buttons and other controls*/
static const lv_btnmatrix_ctrl_t kb_ctrl[] = {4, 4, 4, 4, 4, 4,
                                              4, 4, 4, 4, 4, 4,
                                              4, 4, 4, 8, 
                                              8,8};

lv_obj_t* kb;
void kb_event_cb(lv_event_t*);
void ta_event_cb(lv_event_t*);
unsigned char atoh(unsigned char);

#ifdef CONFIG_EEZ
#define scrnCAN objects.scrn_can
#define scrnAnalog objects.scrn_analog
#define scrnGPIO objects.scrn_gpio
#define scrnPulse objects.scrn_pulse
#define txtFilterID objects.txt_filter_id
#define txtCANTxId objects.txt_can_tx_id
#define txtCANTxData objects.txt_can_tx_data
#define lblCANRxMsg objects.lbl_can_rx_msg
#define lblGPI1Ind objects.lbl_gpi1_ind
#define lblGPI2Ind objects.lbl_gpi2_ind
#define valVin objects.val_vin
#define val0to10V objects.val0to10_v
#define valPulseIn objects.val_pulse_in
#elif CONFIG_SQUARELINE
#define scrnCAN ui_scrnCAN
#define scrnAnalog ui_scrnAnalog
#define scrnGPIO ui_scrnGPIO
#define scrnPulse ui_scrnPulse
#define txtFilterID ui_txtFilterID
#define txtCANTxId ui_txtCANTxID
#define txtCANTxData ui_txtCANTxData
#define lblCANRxMsg ui_lblCANRxMsg
#define lblGPI1Ind ui_lblGPI1Ind
#define lblGPI2Ind ui_lblGPI2Ind
#define valVin ui_valVin
#define val0to10V ui_val0to10V
#define valPulseIn ui_valPulseIn
#endif

void ui_custom_code_init()
{        
    //CAN screen keyboard
    kb = lv_keyboard_create(scrnCAN);
    lv_obj_set_width(kb, 300);
    lv_obj_set_height(kb, 240);
    lv_obj_set_align(kb, LV_ALIGN_CENTER);   
    lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN); 

    lv_keyboard_set_map(kb, LV_KEYBOARD_MODE_USER_1, kb_map, kb_ctrl);
    lv_keyboard_set_mode(kb, LV_KEYBOARD_MODE_USER_1);
    lv_obj_add_event_cb(kb,kb_event_cb,LV_EVENT_READY,NULL);
    lv_obj_add_event_cb(txtFilterID, ta_event_cb, LV_EVENT_FOCUSED, NULL);
    lv_obj_add_event_cb(txtCANTxId, ta_event_cb, LV_EVENT_FOCUSED, NULL);
    lv_obj_add_event_cb(txtCANTxData, ta_event_cb, LV_EVENT_FOCUSED, NULL);    
}

void kb_event_cb(lv_event_t * e)
{    
    size_t idx=0;
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * ta = lv_keyboard_get_textarea(kb);

    const char* txt = lv_textarea_get_text(ta);
    
    size_t txt_len = strlen(txt);

    if (txt_len % 2 == 0)
    {
      if (ta == txtFilterID)
      {
        CAN_FilterID=0;
        if(txt_len==4)
        {//11-bit ID
          CAN_FilterID = (unsigned long)((uint8_t)(atoh(txt[0])<<4|atoh(txt[1]))<<24 | (uint8_t)(atoh(txt[2])<<4|atoh(txt[3]))<<16);    
          #if DEBUG_CAN
          Serial.printf("ID: 0x%.8lX\n",CAN_FilterID);       
          #endif
        }
        else if(txt_len==8)
        {//29-bit ID
          CAN_FilterID = (unsigned long)((uint8_t)(atoh(txt[0])<<4|atoh(txt[1]))<<24 | (uint8_t)(atoh(txt[2])<<4|atoh(txt[3]))<<16 | (uint8_t)(atoh(txt[4])<<4|atoh(txt[5]))<<8 | (uint8_t)(atoh(txt[6])<<4|atoh(txt[7])));
          CAN_FilterID |= 0x80000000;
          #if DEBUG_CAN
          Serial.printf("ID: 0x%.8lX\n",CAN_FilterID);
          #endif
        }             
      }
      else if (ta == txtCANTxId)
      {        
        sCAN_TxMsg.ID=0;
        if(txt_len==4)
        {//11-bit ID
          sCAN_TxMsg.ID = (unsigned long)((uint8_t)(atoh(txt[0])<<4|atoh(txt[1]))<<8 | (uint8_t)(atoh(txt[2])<<4|atoh(txt[3])));          
        }
        else if(txt_len==8)
        {//29-bit ID
          sCAN_TxMsg.ID = (unsigned long)((uint8_t)(atoh(txt[0])<<4|atoh(txt[1]))<<24 | (uint8_t)(atoh(txt[2])<<4|atoh(txt[3]))<<16 | (uint8_t)(atoh(txt[4])<<4|atoh(txt[5]))<<8 | (uint8_t)(atoh(txt[6])<<4|atoh(txt[7])));
          sCAN_TxMsg.ID |= 0x80000000;
        } 
      }
      else
      { // must be CAN Tx data bytes
        sCAN_TxMsg.len=txt_len/2;
        for(idx=0;idx<txt_len;idx+=2)
        {//form each hex byte by combing two ASCII characters          
          sCAN_TxMsg.arrData[idx/2] = (uint8_t)(atoh(txt[idx])<<4 | atoh(txt[idx+1]));
        }
      }
    }
    else
    { // all hex entries must be even number of characters
    }
    
    lv_obj_clear_state(ta,LV_STATE_FOCUSED);
    lv_indev_reset(NULL, ta);
    lv_keyboard_set_textarea(kb, NULL);
    lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);    
}

void ta_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
        
    if(code == LV_EVENT_FOCUSED) 
    {        
        if(ta==txtFilterID)
        {//position keyboard at the bottom for upper text areas
          lv_obj_set_align(kb, LV_ALIGN_BOTTOM_MID);
        }
        else
        {//position keyboard at the top for lower text areas
          lv_obj_set_align(kb, LV_ALIGN_TOP_MID);
        }
        lv_keyboard_set_textarea(kb, ta);
        lv_obj_clear_flag(kb, LV_OBJ_FLAG_HIDDEN);
    }
}

unsigned char atoh(unsigned char hex)
{
  if (hex > 0x39)
  {
    hex -= 7; // adjust for hex letters upper or lower case
  }
  return (hex & 0xf);
}

void label_updt(lv_timer_t* timer)
{
  char msgString[64];  

  if(lv_scr_act()==scrnAnalog)
  {
    fnAnlgIn_Read();

    lv_label_set_text_fmt(valVin,"%.2f",f_VIn); 
    lv_label_set_text_fmt(val0to10V,"%.2f",f_V0to10); 
  }
  else if(lv_scr_act()==scrnCAN)
  {
    if (bCAN_RxActv)
    {
      sprintf(msgString, "%d ms: %.8lX ",deltatime,sCAN_RxMsg.ID);
    
      for(byte i = 0; i<sCAN_RxMsg.len; i++)
      {
        sprintf(msgString+strlen(msgString), " %.2X", sCAN_RxMsg.arrData[i]);    
      }

      lv_label_set_text(lblCANRxMsg, msgString);
    }
    else
    {
      lv_label_set_text(lblCANRxMsg, "");
    }
  }
  else if(lv_scr_act()==scrnGPIO)
  {
    if(get_gpi_1()==0)
    {
      lv_obj_set_style_bg_opa(lblGPI1Ind, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    else
    {
      lv_obj_set_style_bg_opa(lblGPI1Ind, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    }

    if(get_gpi_2()==0)
    {
      lv_obj_set_style_bg_opa(lblGPI2Ind, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    else
    {
      lv_obj_set_style_bg_opa(lblGPI2Ind, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    }
  }
  else if(lv_scr_act()==scrnPulse)
  {
    lv_label_set_text_fmt(valPulseIn,"%d",GetPulseFrequency());     
  }
}