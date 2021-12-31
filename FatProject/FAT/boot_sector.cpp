#include "boot_sector.h"

namespace FAT
{
	BootSector::BootSector(size_t pSize) : Sector(pSize)
	{
		uint8_t one = 0xEB;
		set8(0, 0xEB);	//JmpBoot[0]
		set8(1, 0x59);	//JmpBoot[1]
		set8(2, 0x90);	//JmpBoot[2]
	}
	void BootSector::init()
	{
		//There should be a bloody space at the end. It fails otherwise
		setOEMName("MSWIN4.1");
	}
}