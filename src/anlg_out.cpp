#include "anlg_out.h"
#include <Wire.h>
#ifdef CONFIG_EEZ
#include "actions.h"
#include "screens.h"
#endif

#define MCP47CVB_ADDR             0x61 ///< Default i2c address
#define MCP47CVB_WRITE_DAC0       0x00    ///< Writes data to DAC 0
#define MCP47CVB_WAKEUP_CMD       0x0A    ///< Writes data to DAC 0


/**************************************************************************/
/*!
    @brief  Class for communicating with an MCP47CVB DAC
*/
/**************************************************************************/
class MCP47CVB {
public:
  MCP47CVB();
  bool begin(TwoWire &wirePort = Wire, uint8_t address = MCP47CVB_ADDR);
  bool _set_DAC_val(uint8_t output);
  bool writeRegister(uint8_t addr, uint8_t val);
  bool WakeUp();

private:
    uint8_t _deviceAddress;
	TwoWire *_i2cPort;  
};

MCP47CVB DAC_i2c = MCP47CVB();


void fnDAC_Init()
{    
    if(DAC_i2c.begin())
    {
        DAC_i2c._set_DAC_val(0);
        DAC_i2c.WakeUp();
    }
}

void set_DAC_val(byte x)
{    
    if(!DAC_i2c._set_DAC_val(x))
    {
        #if DEBUG_ANLG
        Serial.println("DAC Write Error");
        #endif
    }
}

/**************************************************************************/
/*!
    @brief  Instantiates a new MCP47CVB class
*/
/**************************************************************************/
MCP47CVB::MCP47CVB() {}

/**************************************************************************/
/*!
    @brief  Setups the hardware and checks the DAC was found
    @param address The I2C address of the DAC, defaults to 0x61
    @param wirePort The I2C TwoWire object to use, defaults to &Wire
    @returns True if DAC was found on the I2C address.
*/
/**************************************************************************/
bool MCP47CVB::begin(TwoWire &wirePort, uint8_t address)
{
	#if DEBUG_ANLG
    Serial.println("DAC begin");
    Serial.printf("addr: %d\n",address);
    #endif
    _deviceAddress = address;
	_i2cPort = &wirePort;    

	_i2cPort->beginTransmission(_deviceAddress);
	
    if (_i2cPort->endTransmission() != 0)
	{
      return (false); //Error: Sensor did not ack
	  #if DEBUG_ANLG
      Serial.println("DAC Init Error");
      #endif
	}    
	return(true);
}

/**************************************************************************/
/*!    
*/
/**************************************************************************/
bool MCP47CVB::_set_DAC_val(uint8_t output)
{
    return writeRegister(MCP47CVB_WRITE_DAC0, output);
}

bool MCP47CVB::writeRegister(uint8_t addr, uint8_t val)
{	
    _i2cPort->beginTransmission(_deviceAddress);
	_i2cPort->write(addr);
	_i2cPort->write(0);//upper byte is always 0 because device is 8-bit
    _i2cPort->write(val);
    if (_i2cPort->endTransmission() != 0)
      return (false); //Error: Sensor did not ack
	return(true);
}

bool MCP47CVB::WakeUp()
{
    _i2cPort->beginTransmission(0);
	_i2cPort->write(MCP47CVB_WAKEUP_CMD); //MCP47CV specific general call command to wakeup   
    if (_i2cPort->endTransmission() != 0)
      return (false); //Error: Sensor did not ack
	return(true);
}

#ifdef CONFIG_EEZ
void action_updt_dac_val(lv_event_t * e)
{
	lv_obj_t * slider = lv_event_get_target(e);
    uint8_t slider_val = (uint8_t)lv_slider_get_value(slider);    
	float fVOut = slider_val/25.5;
	lv_label_set_text_fmt(objects.val_vout,"%.1f",fVOut);    
	set_DAC_val(slider_val);
}
#endif