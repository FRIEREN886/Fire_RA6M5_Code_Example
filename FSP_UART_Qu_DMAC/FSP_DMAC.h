#ifndef __FSP_DMAC_H_
#define __FSP_DMAC_H_
#define BUFFER_SIZE 32
#include "hal_data.h"                   // Flex Software:Generated Data

#define USE_MY_TRANSFER_INFOR_CONFIG 
#ifdef USE_MY_TRANSFER_INFOR_CONFIG
    #define DMAC_TRANSFER_NORMAL_MODE (1)
    #define TRANSFER_MODE_REPEAT (2)
    #define TRANSFER_MODE_BLOCK (3)
    #define TRANSFER_MODE_REPEAT_BLOCK (4)
#define DMAC_TRANSFER_MODE TRANSFER_MODE_REPEAT
#endif

void Set_Transfer_Dst_Src_Address(transfer_cfg_t const * const p_config,void const * volatile p_src,void const * volatile p_dest);
void FSP_Dmac_Init();


#endif