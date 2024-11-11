
//Display
#define LCD_WIDTH 320
#define LCD_HEIGHT 480
#define LCD_DC 22
#define LCD_CS 21
#define LCD_CLK 5
#define LCD_MOSI 18
#define LCD_MISO 19
#define LCD_RESET 23
#define LCD_BACKLIGHT 33

//CAN
#define MCP2515_MISO 12
#define MCP2515_MOSI 13
#define MCP2515_CLK 14
#define MCP2515_CS 15
#define MCP2515_INT 4

//I2C
#define I2C_SDA 25
#define I2C_SCL 26
#define I2C_EEPROM_ADDR 0x56
#define I2C_GPIO_ADDR 0x21
#define I2C_GPIO_ADDR_A 0x39
#define I2C_DAC_ADDR 0x61


// GPIO
#define GPI1_TCA9534_PIN 4
#define GPI2_TCA9534_PIN 3
#define GPO3_TCA9534_PIN 0
#define GPO4_TCA9534_PIN 1
#define GPO5_TCA9534_PIN 2
#define CANTERM_TCA9534_PIN 6
#define BEEPER_TCA9534_PIN 7

// Analog to Digital ADC
#define VIN_ADC 36
#define VIN_ADC_CHANNEL ADC_CHANNEL_0
#define V0_10_ADC 39
#define V0_10_ADC_CHANNEL ADC_CHANNEL_3

//PWM Out 0 to 5V
#define PWM_OUT_PIN 2

//Pulse In 12V
#define PULSE_IN 32

