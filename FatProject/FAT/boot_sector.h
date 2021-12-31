#pragma once
#ifndef _H_FAT_BOOT_SECTOR
#define _H_FAT_BOOT_SECTOR
#include "sector.h"
#include "constants.h"

namespace FAT
{
	class BootSector : public Sector
	{
	public:
		BootSector(size_t pSize);
		virtual ~BootSector() {}

		void init();
		size_t getRootEntryCount() { return get16(BPB_ROOT_ENTRIES_COUNT_OFFSET); }
		size_t getReservedSectorCount() { return get16(BPB_RESERVED_SECTOR_COUNT_OFFSET); }
		size_t getBytesPerSector() { return get16(BPB_BYTES_PER_SECTOR_OFFSET); }
		size_t getSectorsPerCluster() { return get8(BPB_SECTORS_PER_CLUSTER_OFFSET); };
		size_t getTotalSectors32() { return get32(BPB_TOTAL_SECTORS_32_OFFSET); }
		size_t getNumFats() { return get8(BPB_NUM_FATS_OFFSET); }
		size_t getBkBootSector() { return get16(BPB_BK_BOOT_SECTOR_OFFSET); }
		size_t getSectorsPerFat() { return get32(BPB_FATSZ_32_OFFSET); }


		const char* getFileSystemType()
		{
			char fileSystemType[8];
			memcpy(fileSystemType, (BYTE*)buffer + BS_FILE_SYS_TYPE, 8);
			return fileSystemType;
		}



		void setOEMName(const char* name) { setBlock(name, BS_OEM_NAME_OFFSET, 8); }
		void setBytesPerSector(size_t sectorSize) { set16(BPB_BYTES_PER_SECTOR_OFFSET, sectorSize); }
		void setSectorsPerCluster(size_t count) { set8(BPB_SECTORS_PER_CLUSTER_OFFSET, count); };
		void setReservedSectorCount(size_t count) { set16(BPB_RESERVED_SECTOR_COUNT_OFFSET, count); }
		void setNumFats(size_t count) { set8(BPB_NUM_FATS_OFFSET, count); }
		void setRootEntryCount(size_t count) { set16(BPB_ROOT_ENTRIES_COUNT_OFFSET, count); }
		void setTotalSectors16(size_t count) { set16(BPB_TOLAL_SECTORS_16_OFFSET, count); }
		void setMedia(size_t count) { set8(BPB_MEDIA_OFFFSET, count); }
		void setFatSz16(size_t count) { set16(BPB_FATSZ_16_OFFSET, count); }
		void setSectorsPerTrack(size_t count) { set16(BPB_SECTORS_PER_TRACK_OFFSET, count); }
		void setNumHeads(size_t count) { set16(BPB_NUM_HEADS_OFFSET, count); }
		void setHiddenSectors(size_t count) { set32(BPB_HIDDEN_SECTORS_OFFSET, count); }
		void setTotalSectors32(size_t count) { set32(BPB_TOTAL_SECTORS_32_OFFSET, count); }

		void setFatSz32(size_t count) { set32(BPB_FATSZ_32_OFFSET, count); }
		void setExtFlags(size_t count) { set16(BPB_EXT_FLAGS_OFFSET, count); }
		void setFSVer(size_t version) { set16(BPB_FS_VERSION_OFFSET, version); }
		void setRootCluster(size_t index) { set32(BPB_ROOT_CLUSTER_OFFSET, index); }
		void setFSInfo(size_t info) { set16(BPB_FS_INFO_OFFSET, info); }
		void setBkBootSector(size_t index) { set16(BPB_BK_BOOT_SECTOR_OFFSET, index); }
		void setReserved() 
		{ 
			//set32(BPB_RESERVED_OFFSET, 0); 
			//set32(BPB_RESERVED_OFFSET + 4, 0);
			//set32(BPB_RESERVED_OFFSET + 8, 0);
		}
		void setDriveNum(size_t index) { set8(BS_DRIVE_NUM_OFFSET, index); }
		void setReserved1(size_t count) { set8(BS_RESERVED_1_OFFSET, count); }
		void setBootSignature(size_t signature) { set8(BS_BOOT_SIG_OFFSET, signature); }
		void setVolumeId(size_t id) { set32(BS_VOL_ID_OFFSET, id); }
		void setVolLabel(const char* label) { setBlock(label, BS_VOL_LABEL, 11); }
		void setFileSystemType(const char* type) { setBlock(type, BS_FILE_SYS_TYPE, 8); }
	};
}
#endif