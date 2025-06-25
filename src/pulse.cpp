#include "pulse.h"
#include "TapCAN.h"
#include "ui.h"
#ifdef CONFIG_EEZ
#include "actions.h"
#include "screens.h"
#endif

uint32_t pulseCount;
uint32_t PrevReadTime;

uint32_t pwm_out_dc;
uint32_t pwm_out_dc_pct;
uint32_t pwm_out_freq;
#define PWM_OUT_CHANNEL 0
#define PWM_OUT_DC_RES 8 // 8-bit Duty Cycle resolution
#define MAX_PWM_OUT_DC 100
#define MIN_PWM_OUT_FREQ 100
#define MAX_PWM_OUT_FREQ 9000

#ifdef CONFIG_EEZ
    #define PWMOutDC objects.val_pwm_out_dc
    #define PWMOutFreq objects.val_pwm_out_freq
#elif CONFIG_SQUARELINE
    #define PWMOutDC ui_valPWMOutDC
    #define PWMOutFreq ui_valPWMOutFreq
#endif


void IRAM_ATTR Pulse_ISR(); 

void fnPulse_Init()
{
    pulseCount=0;
    PrevReadTime=0;
    pinMode(PULSE_IN, INPUT);  
    // Attach an interrupt when input falls
    attachInterrupt(digitalPinToInterrupt(PULSE_IN), Pulse_ISR, FALLING);

    //use ESP32 ledc functions for PWM output
    pwm_out_dc_pct=50; //initialize DC to 50%
    pwm_out_dc=(pwm_out_dc_pct/100.0)*256;
    lv_label_set_text_fmt(PWMOutDC,"%d",pwm_out_dc_pct);
    pwm_out_freq=1000; //initialize Frequency to 1000 Hz
    lv_label_set_text_fmt(PWMOutFreq,"%d",pwm_out_freq);
    
    ledcSetup(PWM_OUT_CHANNEL, pwm_out_freq, 8);  // channel 0, 8-bit duty cycle resolution 
    ledcAttachPin(PWM_OUT_PIN, PWM_OUT_CHANNEL);    
} 

void IRAM_ATTR Pulse_ISR() 
{
  // Interrupt routine triggers when when input falls  
  // Just add one to the number of pulses counted
  pulseCount++;  
}

uint32_t GetPulseFrequency()
{    
    // Calculate the time that has past since last frequency calculation
    uint32_t DeltaTime = millis() - PrevReadTime;  

    // Calculate frequency
    uint32_t freq = (pulseCount * 1000) / DeltaTime;
    
    #if DEBUG_PULSE
    Serial.printf("Pulse Freq: %d Hz\n",freq);
    #endif
    // Reset variables
    pulseCount = 0;                 // Reset the pulse counter
    PrevReadTime = millis();      // Set the previous read time to now
    return freq;
}

void SetPWMOutFreq(int8_t mDrtcn)
{
    if(mDrtcn==0 && pwm_out_freq > MIN_PWM_OUT_FREQ)
    {
        pwm_out_freq -= 100;        
    }
    else if(mDrtcn==1 && pwm_out_freq < MAX_PWM_OUT_FREQ)
    {
        pwm_out_freq += 100;
    }
    lv_label_set_text_fmt(PWMOutFreq,"%d",pwm_out_freq);
    if(ledcChangeFrequency(PWM_OUT_CHANNEL,pwm_out_freq,PWM_OUT_DC_RES) != pwm_out_freq)
    {
        #if DEBUG_PULSE
        Serial.println("PWM Output Frequency Change Error");
        #endif
    }
}

void SetPWMOutDC(int8_t mDrtcn)
{
    if(mDrtcn==0 && pwm_out_dc_pct > 0)
    {
        pwm_out_dc_pct -= 10;        
    }
    else if(mDrtcn==1 && pwm_out_dc_pct < MAX_PWM_OUT_DC)
    {
        pwm_out_dc_pct += 10;
    }
    lv_label_set_text_fmt(PWMOutDC,"%d",pwm_out_dc_pct);
    pwm_out_dc=(pwm_out_dc_pct/100.0)*256;
    ledcWrite(PWM_OUT_CHANNEL, pwm_out_dc); 
}

#ifdef CONFIG_EEZ
void action_btn_dc_up_clk(lv_event_t * e)
{
	SetPWMOutDC(1);
}

void action_btn_dc_dwn_clk(lv_event_t * e)
{
	SetPWMOutDC(0);
}

void action_btn_freq_up_clk(lv_event_t * e)
{
	SetPWMOutFreq(1);
}

void action_btn_freq_dwn_clk(lv_event_t * e)
{
	SetPWMOutFreq(0);
}
#endif