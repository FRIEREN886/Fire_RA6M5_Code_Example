#include "FSP_LED.h"

void FSP_LED_Init(void)
{
	R_IOPORT_Open(&g_ioport_ctrl, g_ioport.p_cfg);
}