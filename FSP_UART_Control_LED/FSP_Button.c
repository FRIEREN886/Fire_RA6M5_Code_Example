#include "FSP_Button.h"


void FSP_Button_Init()
{
	R_IOPORT_Open(&g_ioport_ctrl, g_ioport.p_cfg);
}



//Key1 = SW2
//Key2 = SW3
uint32_t FSP_Scan_Key(bsp_io_port_pin_t Key)
{
	bsp_io_level_t State;
	R_IOPORT_PinRead(&g_ioport_ctrl,Key, &State);
	if(State == BSP_IO_LEVEL_HIGH)
		return Button_OFF;
	else
	{
		do
		{
			
			R_IOPORT_PinRead(&g_ioport_ctrl,Key, &State);
		}while(State == BSP_IO_LEVEL_LOW);
	}
	return Button_ON;
}