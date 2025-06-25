#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *scrn_home;
    lv_obj_t *scrn_can;
    lv_obj_t *scrn_gpio;
    lv_obj_t *scrn_analog;
    lv_obj_t *scrn_pulse;
    lv_obj_t *obj0;
    lv_obj_t *btn_gpio;
    lv_obj_t *btn_analog;
    lv_obj_t *btn_pulse;
    lv_obj_t *btn_home;
    lv_obj_t *btn_rx_can;
    lv_obj_t *btn_rx_can_1;
    lv_obj_t *btn_home_1;
    lv_obj_t *swt_gpo3;
    lv_obj_t *swt_gpo4;
    lv_obj_t *swt_gpo5;
    lv_obj_t *swt_beep;
    lv_obj_t *swt_can_term;
    lv_obj_t *btn_home_3;
    lv_obj_t *slider_dac_vout;
    lv_obj_t *btn_home_2;
    lv_obj_t *btn_freq_up;
    lv_obj_t *btn_dc_up;
    lv_obj_t *btn_freq_dwn;
    lv_obj_t *btn_dc_dwn;
    lv_obj_t *txt_filter_id;
    lv_obj_t *lbl_rx_btn_txt;
    lv_obj_t *txt_can_tx_id;
    lv_obj_t *txt_can_tx_data;
    lv_obj_t *obj1;
    lv_obj_t *lbl_can_rx_msg;
    lv_obj_t *obj2;
    lv_obj_t *lbl_gpi1_ind;
    lv_obj_t *lbl_gpi2_ind;
    lv_obj_t *val_vout;
    lv_obj_t *val_vin;
    lv_obj_t *val0to10_v;
    lv_obj_t *val_pwm_out_freq;
    lv_obj_t *val_pwm_out_dc;
    lv_obj_t *val_pulse_in;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_SCRN_HOME = 1,
    SCREEN_ID_SCRN_CAN = 2,
    SCREEN_ID_SCRN_GPIO = 3,
    SCREEN_ID_SCRN_ANALOG = 4,
    SCREEN_ID_SCRN_PULSE = 5,
};

void create_screen_scrn_home();
void tick_screen_scrn_home();

void create_screen_scrn_can();
void tick_screen_scrn_can();

void create_screen_scrn_gpio();
void tick_screen_scrn_gpio();

void create_screen_scrn_analog();
void tick_screen_scrn_analog();

void create_screen_scrn_pulse();
void tick_screen_scrn_pulse();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/