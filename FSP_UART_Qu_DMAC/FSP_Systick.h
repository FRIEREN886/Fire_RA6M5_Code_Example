#ifndef _FSP_SYSTICK_H__
#define _FSP_SYSTICK_H__

#include "hal_data.h"

typedef enum
{
    SYS_DELAY_UNITS_SECONDS      = 200000000, ///< Requested delay amount is in seconds
    SYS_DELAY_UNITS_MILLISECONDS = 200000,    ///< Requested delay amount is in milliseconds
    SYS_DELAY_UNITS_MICROSECONDS = 200        ///< Requested delay amount is in microseconds
} sys_delay_units_t;

void FSP_Systick_Init(uint32_t FSP_Systick_Frequency);
void FSP_Delay_Systick(uint32_t FSP_Delay_time,sys_delay_units_t uint);

#endif