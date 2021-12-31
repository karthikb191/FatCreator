#include "disk_file.h"

namespace FAT
{
	DiskFile::DiskFile(size_t pTotalDiskSize) 
		: totalDiskSize(pTotalDiskSize)
	{
	}
	void DiskFile::init()
	{
		bootSector = std::make_unique<BootSector>(SECTOR_SIZE);
		fsInfoSector = std::make_unique<FsInfoSector>(SECTOR_SIZE);
		bootSector->init();
		fsInfoSector->init();
		formatter.format(this);
	}
}