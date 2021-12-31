#pragma once
#include "sector.h"
#include "constants.h"

namespace FAT
{
	//Occupies the first sector in FAT32 volumes
	class FsInfoSector : public Sector
	{
	public:
		FsInfoSector(size_t pSize) : Sector(pSize) {}
		void init()
		{
			//This pretty much contains default values
			set32(FS_LEAD_SIG_OFFSET, 0x41615252);

			set32(FS_STRUC_SIG_OFFSET, 0x61417272);
			

			set32(FS_TRAIL_SIG_OFFSET, 0xAA550000);

		}


		size_t getFreeClusterCount() { return get32(FS_FREE_COUNT_OFFSET); }
		size_t getNextFreeCluster() { return get32(FS_NEXT_FREE_OFFSET); }


		void setFreeClusterCount(size_t value) { set32(FS_FREE_COUNT_OFFSET, value); }
		void setNextFreeCluster(size_t value) { set32(FS_NEXT_FREE_OFFSET, value); }

	private:

	};
}