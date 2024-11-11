#include <Arduino.h>
#include "TapCAN.h"
#include <Wire.h>
#include "SparkFun_TCA9534.h"
#include "gpio_ext.h"

TCA9534 gpio_i2c = TCA9534();

void fnGPIO_Init()
{
    #if DEBUG_GPIO
    Serial.println("gpio init");
    #endif
    gpio_i2c.begin(Wire, I2C_GPIO_ADDR_A); //TCA9534A address
    //gpio_i2c.begin(Wire, I2C_GPIO_ADDR); //TCA9534 address
    gpio_i2c.pinMode(GPI1_TCA9534_PIN,GPIO_IN);
    gpio_i2c.pinMode(GPI2_TCA9534_PIN,GPIO_IN);
    gpio_i2c.pinMode(GPO3_TCA9534_PIN,GPIO_OUT);
    gpio_i2c.pinMode(GPO4_TCA9534_PIN,GPIO_OUT);
    gpio_i2c.pinMode(GPO5_TCA9534_PIN,GPIO_OUT);
    gpio_i2c.pinMode(CANTERM_TCA9534_PIN,GPIO_OUT);
    gpio_i2c.pinMode(BEEPER_TCA9534_PIN,GPIO_OUT);

    set_gpo_beep(0);
    set_gpo_CANTerm(0);
    set_gpo_3(0);
    set_gpo_4(0);
    set_gpo_5(0);
}

uint8_t get_gpi_1()
{
    return(gpio_i2c.digitalRead(GPI1_TCA9534_PIN));
}

uint8_t get_gpi_2()
{
    return(gpio_i2c.digitalRead(GPI2_TCA9534_PIN));
}

void set_gpo_3(uint8_t x)
{       
    gpio_i2c.digitalWrite(GPO3_TCA9534_PIN,x);    
}

void set_gpo_4(uint8_t x)
{       
    gpio_i2c.digitalWrite(GPO4_TCA9534_PIN,x);    
}

void set_gpo_5(uint8_t x)
{       
    gpio_i2c.digitalWrite(GPO5_TCA9534_PIN,x);    
}

void set_gpo_beep(uint8_t beep)
{
    #if DEBUG_GPIO
    Serial.printf("BEEP: %d\n",beep);   
    #endif
    gpio_i2c.digitalWrite(BEEPER_TCA9534_PIN,beep);    
}

void set_gpo_CANTerm(uint8_t x)
{       
    //0 value turns on CAN termination
    //invert input so the caller uses 1 or true to enable
    gpio_i2c.digitalWrite(CANTERM_TCA9534_PIN,!x);    
}