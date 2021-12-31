#pragma once
#ifndef _H_FAT_CONSTANTS
#define _H_FAT_CONSTANTS
namespace FAT
{
//Global Constants
//TODO: Extend the max size once the entire system is working
constexpr size_t DEFAULT_SIZE				= 1057452032; //4 GB is the limit of uint32_t.
constexpr size_t SECTOR_SIZE				= 512;
constexpr size_t START_CLUSTER				= 2;
#define BYTE	uint8_t
#define DWORD	uint32_t

//Boot sector offsets
constexpr size_t  BS_OEM_NAME_OFFSET					= 3;
constexpr size_t  BPB_BYTES_PER_SECTOR_OFFSET			= 11;
constexpr size_t  BPB_SECTORS_PER_CLUSTER_OFFSET		= 13;
constexpr size_t  BPB_RESERVED_SECTOR_COUNT_OFFSET		= 14;
constexpr size_t  BPB_NUM_FATS_OFFSET					= 16;
constexpr size_t  BPB_ROOT_ENTRIES_COUNT_OFFSET			= 17;
constexpr size_t  BPB_TOLAL_SECTORS_16_OFFSET			= 19;
constexpr size_t  BPB_MEDIA_OFFFSET						= 21;
constexpr size_t  BPB_FATSZ_16_OFFSET					= 22;
constexpr size_t  BPB_SECTORS_PER_TRACK_OFFSET			= 24;
constexpr size_t  BPB_NUM_HEADS_OFFSET					= 26;
constexpr size_t  BPB_HIDDEN_SECTORS_OFFSET				= 28;
constexpr size_t  BPB_TOTAL_SECTORS_32_OFFSET			= 32;

// FAT12/FAT16 specific structure
	//TODO: Add support to FAT 16 later

// FAT32 specific structure
constexpr size_t  BPB_FATSZ_32_OFFSET					= 36;
constexpr size_t  BPB_EXT_FLAGS_OFFSET					= 40;
constexpr size_t  BPB_FS_VERSION_OFFSET					= 42;
constexpr size_t  BPB_ROOT_CLUSTER_OFFSET				= 44;
constexpr size_t  BPB_FS_INFO_OFFSET					= 48;
constexpr size_t  BPB_BK_BOOT_SECTOR_OFFSET				= 50;
constexpr size_t  BPB_RESERVED_OFFSET					= 52;
constexpr size_t  BS_DRIVE_NUM_OFFSET					= 64;
constexpr size_t  BS_RESERVED_1_OFFSET					= 65;
constexpr size_t  BS_BOOT_SIG_OFFSET					= 66;
constexpr size_t  BS_VOL_ID_OFFSET						= 67;
constexpr size_t  BS_VOL_LABEL							= 71;
constexpr size_t  BS_FILE_SYS_TYPE						= 82;


//FS Info Offsets
constexpr size_t  FS_LEAD_SIG_OFFSET					= 0;
constexpr size_t  FS_RESERVED_1_OFFSET					= 4;
constexpr size_t  FS_STRUC_SIG_OFFSET					= 484;
constexpr size_t  FS_FREE_COUNT_OFFSET					= 488;
constexpr size_t  FS_NEXT_FREE_OFFSET					= 492;
constexpr size_t  FS_RESERVED_2_OFFSET					= 496;
constexpr size_t  FS_TRAIL_SIG_OFFSET					= 508;

}

#endif // !_H_FAT_CONSTANTS
