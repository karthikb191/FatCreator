#pragma once
#include "boot_sector.h"
#include "fs_info.h"
#include "formatter.h"
#include <memory>

namespace FAT
{
	class DiskFile
	{
	public:
		DiskFile(size_t pTotalDiskSize);
		~DiskFile() {}

		void init();
		BootSector* getBootSector() { return bootSector.get(); }
		FsInfoSector* getFileSystemInfoSector() { return fsInfoSector.get(); }
		size_t getSize() { return totalDiskSize; }
		size_t getTotalClusters() { return totalClusters; };
		size_t getClusterSize() { return clusterSize; }

		void setTotalClusters(size_t pTotalClusters) { totalClusters = pTotalClusters; };
		void setClusterSize(size_t pClusterSize) { clusterSize = pClusterSize; }

	private:
		
		size_t totalDiskSize = 0;
		size_t totalClusters = 0;
		size_t clusterSize = 0;
		std::unique_ptr<BootSector> bootSector;
		std::unique_ptr<FsInfoSector> fsInfoSector;
		Formatter formatter;
	};
}