#include "CAN.h"

#include "SPI.h"
#include "gpio_ext.h"
#include <mcp_can.h>

SPIClass SPI_CAN(HSPI);
static MCP_CAN CAN0(&SPI_CAN,15);

#define CAN0_INT 4

uint32_t CAN_FilterID;

CAN_Msg_t sCAN_TxMsg;
CAN_Msg_t sCAN_RxMsg;
uint32_t prevtime;
uint32_t deltatime;
char RxDataString[24];//holds characters for up to 8 data bytes and spaces between
boolean bCAN_RxActv;

void fnCAN_Init()
{
    bCAN_RxActv=false;
    pinMode(CAN0_INT, INPUT);
    
    // Initialize MCP2515 running at 8MHz with a baudrate of 500kb/s and the masks and filters disabled.
    CAN0.begin(MCP_STDEXT, CAN_500KBPS, MCP_8MHZ);
    
    // set receive filters
    CAN0.init_Mask(0,0,0x07ff0000); // Init both masks to check every ID bit against the filter, mask 0 for standard IDs
    CAN0.init_Mask(1,1,0x1fffffff); // Init both masks to check every ID bit against the filter, mask 1 fir extebded IDs

    CAN0.setMode(MCP_NORMAL); // Change to normal mode to allow messages to be transmitted  
}

void fnCAN_cntrl_Rx()
{
    uint32_t lCANFiltID=(CAN_FilterID&0x1fffffff);
    boolean extID=((CAN_FilterID & 0x80000000)==0x80000000);

    if(bCAN_RxActv)
    {
        if(extID)
        {//Ext ID
            CAN0.init_Filt(2,1,lCANFiltID);// Mask 1, Filter 2 for extended IDs
            CAN0.init_Filt(0,0,0);// Mask 0, Filter 0 for standard IDs, close the filter
        }
        else
        {//Std ID
            CAN0.init_Filt(0,0,lCANFiltID);// Mask 0, Filter 0 for standard IDs
            CAN0.init_Filt(2,1,0);// Mask 1, Filter 2 for extended IDs, close the filter
        }        
        prevtime=millis();        
    }
    else
    {// close both filters
        CAN0.init_Filt(0,0,0);
        CAN0.init_Filt(2,1,0);      
    }    
}

void fnCAN_Tx()
{   
    CAN0.sendMsgBuf(sCAN_TxMsg.ID,sCAN_TxMsg.len, sCAN_TxMsg.arrData);
}

void fnCAN_Rx()
{
    if (!digitalRead(CAN0_INT))
    {       
        if (CAN0.readMsgBuf(&sCAN_RxMsg.ID, &sCAN_RxMsg.len, sCAN_RxMsg.arrData) == CAN_OK)
        {   
            deltatime=millis()-prevtime;                      
            prevtime=millis();
        }
    }
}