#include "FSP_DMAC.h"

const uint32_t SRam_Buffer[BUFFER_SIZE] = 
    {
0x01020304,0x05060708,0x090A0B0C,0x0D0E0F10,
0x11121314,0x15161718,0x191A1B1C,0x1D1E1F20,
0x21222324,0x25262728,0x292A2B2C,0x2D2E2F30,
0x31323334,0x35363738,0x393A3B3C,0x3D3E3F40,
0x41424344,0x45464748,0x494A4B4C,0x4D4E4F50,
0x51525354,0x55565758,0x595A5B5C,0x5D5E5F60,
0x61626364,0x65666768,0x696A6B6C,0x6D6E6F70,
0x71727374,0x75767778,0x797A7B7C,0x7D7E7F80
    };
    
uint32_t Rom_Buffer[BUFFER_SIZE] = {0};
volatile bool dmac0_compelete_transfmission_sign = false;
volatile uint16_t dmac0_transfer_count;

/*定义传输的源地址和目的地址*/

void Set_Transfer_Dst_Src_Address(transfer_cfg_t const * const p_config,void const * volatile p_src,void const * volatile p_dest)
{
    p_config->p_info->p_src = (void *)p_src;
    p_config->p_info->p_dest = (void *)p_dest;
}


/*配置DMAC传输*/

#if(DMAC_TRANSFER_MODE == DMAC_TRANSFER_NORMAL_MODE)
//正常模式下//
transfer_info_t FSP_Transfer_Dmac0_Info_Normal =
{
    .transfer_settings_word_b.dest_addr_mode = TRANSFER_ADDR_MODE_INCREMENTED,
    .transfer_settings_word_b.repeat_area    = TRANSFER_REPEAT_AREA_SOURCE,
    .transfer_settings_word_b.irq            = TRANSFER_IRQ_END,
    .transfer_settings_word_b.chain_mode     = TRANSFER_CHAIN_MODE_DISABLED,
    .transfer_settings_word_b.src_addr_mode  = TRANSFER_ADDR_MODE_INCREMENTED,
    .transfer_settings_word_b.size           = TRANSFER_SIZE_4_BYTE,
    .transfer_settings_word_b.mode           = TRANSFER_MODE_NORMAL,
    .p_dest                                  = (void *) Rom_Buffer,
    .p_src                                   = (void const *) SRam_Buffer,
    .num_blocks                              = 0,
    .length                                  = BUFFER_SIZE,
};
#elif(DMAC_TRANSFER_MODE == TRANSFER_MODE_REPEAT)
//重复传输模式//
transfer_info_t FSP_Transfer_Dmac0_Info_Repeat =
{
    .transfer_settings_word_b.dest_addr_mode = TRANSFER_ADDR_MODE_INCREMENTED,
    .transfer_settings_word_b.repeat_area    = TRANSFER_REPEAT_AREA_SOURCE,
    .transfer_settings_word_b.irq            = TRANSFER_IRQ_END,
    .transfer_settings_word_b.chain_mode     = TRANSFER_CHAIN_MODE_DISABLED,
    .transfer_settings_word_b.src_addr_mode  = TRANSFER_ADDR_MODE_INCREMENTED,
    .transfer_settings_word_b.size           = TRANSFER_SIZE_4_BYTE,
    .transfer_settings_word_b.mode           = TRANSFER_MODE_REPEAT,
    .p_dest                                  = (void *) Rom_Buffer,
    .p_src                                   = (void const *) SRam_Buffer,
    .num_blocks                              = 8,
    .length                                  = 4,
};
//目标区域重复传输模式//
transfer_info_t FSP_Transfer_Dmac0_Info_Repeat_Dest =
{
    .transfer_settings_word_b.dest_addr_mode = TRANSFER_ADDR_MODE_INCREMENTED,
    .transfer_settings_word_b.repeat_area    = TRANSFER_REPEAT_AREA_DESTINATION,
    .transfer_settings_word_b.irq            = TRANSFER_IRQ_END,
    .transfer_settings_word_b.chain_mode     = TRANSFER_CHAIN_MODE_DISABLED,
    .transfer_settings_word_b.src_addr_mode  = TRANSFER_ADDR_MODE_INCREMENTED,
    .transfer_settings_word_b.size           = TRANSFER_SIZE_4_BYTE,
    .transfer_settings_word_b.mode           = TRANSFER_MODE_REPEAT,
    .p_dest                                  = (void *) Rom_Buffer,
    .p_src                                   = (void const *) SRam_Buffer,
    .num_blocks                              = 8,
    .length                                  = 4,
};
#elif(DMAC_TRANSFER_MODE == TRANSFER_MODE_BLOCK)
//块传输模式//
transfer_info_t FSP_Transfer_Dmac0_Info_Block =
{
    .transfer_settings_word_b.dest_addr_mode = TRANSFER_ADDR_MODE_INCREMENTED,
    .transfer_settings_word_b.repeat_area    = TRANSFER_REPEAT_AREA_SOURCE,
    .transfer_settings_word_b.irq            = TRANSFER_IRQ_END,
    .transfer_settings_word_b.chain_mode     = TRANSFER_CHAIN_MODE_DISABLED,
    .transfer_settings_word_b.src_addr_mode  = TRANSFER_ADDR_MODE_INCREMENTED,
    .transfer_settings_word_b.size           = TRANSFER_SIZE_4_BYTE,
    .transfer_settings_word_b.mode           = TRANSFER_MODE_BLOCK,
    .p_dest                                  = (void *) Rom_Buffer,
    .p_src                                   = (void const *) SRam_Buffer,
    .num_blocks                              = 4,
    .length                                  = 8,
};
//块目标区域重复传输模式//
transfer_info_t FSP_Transfer_Dmac0_Info_Block_Dest =
{
    .transfer_settings_word_b.dest_addr_mode = TRANSFER_ADDR_MODE_INCREMENTED,
    .transfer_settings_word_b.repeat_area    = TRANSFER_REPEAT_AREA_DESTINATION,
    .transfer_settings_word_b.irq            = TRANSFER_IRQ_END,
    .transfer_settings_word_b.chain_mode     = TRANSFER_CHAIN_MODE_DISABLED,
    .transfer_settings_word_b.src_addr_mode  = TRANSFER_ADDR_MODE_INCREMENTED,
    .transfer_settings_word_b.size           = TRANSFER_SIZE_4_BYTE,
    .transfer_settings_word_b.mode           = TRANSFER_MODE_BLOCK,
    .p_dest                                  = (void *) Rom_Buffer,
    .p_src                                   = (void const *) SRam_Buffer,
    .num_blocks                              = 4,
    .length                                  = 8,
};
#elif(DMAC_TRANSFER_MODE == TRANSFER_MODE_REPEAT_BLOCK)
//重复块传输模式//
transfer_info_t FSP_Transfer_Dmac0_Info_Block_Repeat =
{
    .transfer_settings_word_b.dest_addr_mode = TRANSFER_ADDR_MODE_INCREMENTED,
    .transfer_settings_word_b.repeat_area    = TRANSFER_REPEAT_AREA_SOURCE,
    .transfer_settings_word_b.irq            = TRANSFER_IRQ_EACH,
    .transfer_settings_word_b.chain_mode     = TRANSFER_CHAIN_MODE_DISABLED,
    .transfer_settings_word_b.src_addr_mode  = TRANSFER_ADDR_MODE_INCREMENTED,
    .transfer_settings_word_b.size           = TRANSFER_SIZE_4_BYTE,
    .transfer_settings_word_b.mode           = TRANSFER_MODE_REPEAT_BLOCK,
    .p_dest                                  = (void *) Rom_Buffer,
    .p_src                                   = (void const *) SRam_Buffer,
    .num_blocks                              = 16,
    .length                                  = 1,
};

#endif
void FSP_Dmac_Init()
{
    fsp_err_t err;
    
#ifndef USE_MY_TRANSFER_INFOR_CONFIG
    Set_Transfer_Dst_Src_Address(&g_transfer_dmac0_cfg,SRam_Buffer,Rom_Buffer);
#endif
    err = R_DMAC_Open(&g_transfer_dmac0_ctrl, &g_transfer_dmac0_cfg);
    assert(FSP_SUCCESS == err);
    
#ifdef USE_MY_TRANSFER_INFOR_CONFIG 
    
#if(DMAC_TRANSFER_MODE == DMAC_TRANSFER_NORMAL_MODE)
    err = R_DMAC_Reconfigure(&g_transfer_dmac0_ctrl, &FSP_Transfer_Dmac0_Info_Normal);
    assert(FSP_SUCCESS == err);
#elif(DMAC_TRANSFER_MODE == TRANSFER_MODE_REPEAT)
    err = R_DMAC_Reconfigure(&g_transfer_dmac0_ctrl, &FSP_Transfer_Dmac0_Info_Repeat);
    assert(FSP_SUCCESS == err);
#elif(DMAC_TRANSFER_MODE == TRANSFER_MODE_BLOCK)
    err = R_DMAC_Reconfigure(&g_transfer_dmac0_ctrl, &FSP_Transfer_Dmac0_Info_Block);
    assert(FSP_SUCCESS == err);
#elif(DMAC_TRANSFER_MODE == TRANSFER_MODE_REPEAT_BLOCK)
    err = R_DMAC_Reconfigure(&g_transfer_dmac0_ctrl, &FSP_Transfer_Dmac0_Info_Block_Repeat);
    assert(FSP_SUCCESS == err);
#endif
#endif
}

void FSP_Dmac0_Callback(dmac_callback_args_t * p_args)
{ 
    FSP_PARAMETER_NOT_USED(p_args);  
    dmac0_compelete_transfmission_sign =true;
    dmac0_transfer_count ++;
}
