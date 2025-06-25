#include <Arduino.h>
#include "TapCAN.h"
#include <Wire.h>

void i2c_init()
{
  Wire.setPins(I2C_SDA,I2C_SCL); 
  Wire.begin();
  Wire.setClock(400000);  
}