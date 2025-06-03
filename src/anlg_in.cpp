#include "anlg_in.h"
#include "TapCAN.h"
#include "esp_adc_cal.h"

esp_adc_cal_characteristics_t adc_chars;
#define Vref_Dflt_mv 1100

float f_VIn;
float f_V0to10;

void fnAnlgIn_Init()
{  
  pinMode(V0_10_ADC, INPUT);  
  adcAttachPin(V0_10_ADC);

  pinMode(VIN_ADC, INPUT);  
  adcAttachPin(VIN_ADC);

  analogSetWidth(12);

  esp_adc_cal_value_t eTempResp = esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, Vref_Dflt_mv, &adc_chars);
  #if DEBUG_ANLG
  Serial.printf("ADC Characterize Resp: %d\n",eTempResp);
  #endif
}


void fnAnlgIn_Read()
{
    uint32_t lADC_mV_temp=0;
       
    esp_adc_cal_get_voltage(VIN_ADC_CHANNEL,&adc_chars,&lADC_mV_temp);
    //Conversion Ratio: Vin = Vadc_mV / (0.1875 * 1000)
    f_VIn=lADC_mV_temp/187.5;
    
    #if DEBUG_ANLG
    Serial.printf("Vin ADC mV: %d, Vin: %.2f\n",lADC_mV_temp, f_VIn);  
    #endif  

    esp_adc_cal_get_voltage(V0_10_ADC_CHANNEL,&adc_chars,&lADC_mV_temp);
    //Conversion Ration: V0_to_10 = Vadc_mV / (0.32 * 1000)
    f_V0to10 = lADC_mV_temp/320.0;       
    
    #if DEBUG_ANLG
    Serial.printf("V0_to_10 ADC mV: %d, V0_to_10: %.2f\n",lADC_mV_temp, f_V0to10);  
    #endif  
}