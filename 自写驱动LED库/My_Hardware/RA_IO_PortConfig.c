#include "RA_IO_PortConfig.h"

uint32_t IOPORT_PinRead(IO_Port_t Port,IO_Pin_t Pin)
{
	return R_PFS->PORT[Port >> 8].PIN[Pin].PmnPFS_b.PIDR;
}

void IOPORT_PinWrite(IO_Port_t Port,IO_Pin_t Pin,IO_OUTPut_t OUTPut)
{
	uint32_t  pfs_bits = R_PFS->PORT[Port >> 8].PIN[Pin].PmnPFS;
	pfs_bits &= ~(uint32_t)0x1;
	R_PFS->PORT[Port >> 8].PIN[Pin].PmnPFS = (pfs_bits | OUTPut);
}

void IOPORT_PinToggle(IO_Port_t Port,IO_Pin_t Pin)
{
	uint32_t  pfs_bits = R_PFS->PORT[Port >> 8].PIN[Pin].PmnPFS;
	pfs_bits ^= (uint32_t)0x1;
	R_PFS->PORT[Port >> 8].PIN[Pin].PmnPFS = (pfs_bits);
}

void IOPORT_ProtectAccessEnable()
{
	R_PMISC->PWPR = 0;
	R_PMISC->PWPR = 1<<BSP_IO_PWPR_PFSWE_OFFSET;
}

void IOPORT_ProtectAccessDisable()
{
	R_PMISC->PWPR = 0;
	R_PMISC->PWPR = 1<<BSP_IO_PWPR_B0WI_OFFSET;
}

void IOPORT_Init(IOPORT_Init_t *IOport_Init)
{
	uint32_t pfs_bits = 0;
	if(IOport_Init->Mode == IO_Mode_GPIO)
	{
		if(IOport_Init->Dir == IO_Dir_Input)
		{
			pfs_bits |= (IOport_Init->Pull) << 4;
		}
		else if(IOport_Init->Dir == IO_Dir_Output)
		{
			pfs_bits |= (IOport_Init->Dir) << 2;
			pfs_bits |= (IOport_Init->OutPut_type) << 6;
			pfs_bits |= (IOport_Init->OutPut) << 0;
			pfs_bits |= (IOport_Init->Drive) << 10;
		}
	}
	else
	{
		
	}
	R_PFS->PORT[IOport_Init->Port >> 8].PIN[IOport_Init->Pin].PmnPFS = pfs_bits;
}