#ifndef EEZ_LVGL_UI_EVENTS_H
#define EEZ_LVGL_UI_EVENTS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void action_swt_gpo3_toggled(lv_event_t * e);
extern void action_swt_gpo4_toggled(lv_event_t * e);
extern void action_swt_gpo5_toggled(lv_event_t * e);
extern void action_swt_beep_toggled(lv_event_t * e);
extern void action_swt_can_term_toggled(lv_event_t * e);
extern void action_btn_rx_can_msg(lv_event_t * e);
extern void action_btn_send_can_msg(lv_event_t * e);
extern void action_btn_freq_up_clk(lv_event_t * e);
extern void action_btn_freq_dwn_clk(lv_event_t * e);
extern void action_btn_dc_up_clk(lv_event_t * e);
extern void action_btn_dc_dwn_clk(lv_event_t * e);
extern void action_updt_dac_val(lv_event_t * e);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_EVENTS_H*/