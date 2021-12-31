#include "formatter.h"
#include "disk_file.h"
#include <assert.h>
namespace FAT
{
	void Formatter::format(DiskFile* df)
	{
		BootSector* bs = df->getBootSector();
		//TODO: remvoe unnecessary variables

		bs->setBytesPerSector(SECTOR_SIZE);

		size_t bps = bs->getBytesPerSector();

		//We set the sectors per cluster parameter here
		size_t secPerCluster = diskSizeToSectorsPerCluster(df->getSize() / 1024);
		bs->setSectorsPerCluster(secPerCluster);

		//Reserved sector count
		size_t reservedSectors = getReservedSectorCount();
		bs->setReservedSectorCount(reservedSectors);

		// Number of Fats: This is the count of FAT data structures on the volume
		// Any number greater than or equal to 1 is perfecctly valid. But, some sytem drivers may not function properly for any value other than 2
		bs->setNumFats(getNumFats());

		//Root entries.... Always 0 for FAT32
		bs->setRootEntryCount(getRootEntries());

		bs->setTotalSectors16(0);	//TODO: Modify this when adding FAT12/16

		//WARN: This might cause a problem
		bs->setMedia(0xF8); //0xF8 is standard for non-removeable media, 0xF0 for removable

		bs->setFatSz16(0); //TODO: Modify thos when adding FAT12/16

		//WARN: Try setting this to 1 if any issues occur
		bs->setSectorsPerTrack(0);
		bs->setNumHeads(0);		//1 is a neutral value according to wikipedia.
		bs->setHiddenSectors(0);

		//Total sectors for FAT32.
		//TODO: Modify this if implementing FAT12/16
		//WARN: This should be less than or equal to DiskSz(sectors in the disk). If it is higher, you will face issues
		// because the memory to be allocated goes past the max sectors in the disk
		size_t totalSectorsInVolume = df->getSize() / SECTOR_SIZE;
		bs->setTotalSectors32(totalSectorsInVolume);

		//Sectors per FAT
		size_t sectorsPerFat = getSectorsPerFat(df);
		bs->setFatSz32(sectorsPerFat);


		//External Flags
		//WARN: This might cause an issue
		bs->setExtFlags(0x04);	//No mirroring and FAT 0 is the active FAT

		//Fat version
		//Any value other than FAT version 0 fails!!!!!!
		bs->setFSVer(0);

		//First cluster of root directory
		bs->setRootCluster(START_CLUSTER);

		//Fat info
		//Sector number of FSINFO structure in reserved area of FAT32 volume. Usually 1
		bs->setFSInfo(1);

		//Boot Sector backup
		//No value other than 6 is recommended
		bs->setBkBootSector(6);

		bs->setReserved();

		//WARN: This might cause issues
		//0x80 for hard disks and 0x00 for floppy disks
		bs->setDriveNum(0x00);

		bs->setReserved1(0);

		bs->setBootSignature(0x29);

		//Unique volume ID
		size_t t = size_t(time(NULL));
		bs->setVolumeId(size_t(time(NULL)));
		
		bs->setVolLabel("FAT32TOOL  ");

		bs->setFileSystemType("FAT32   ");

		//Cluster computation
		size_t clusterSize = SECTOR_SIZE * bs->getSectorsPerCluster();
		size_t sectorsInDataRegion = getSectorsInDataRegion(df);
		size_t totalClusters = sectorsInDataRegion / bs->getSectorsPerCluster();
		df->setClusterSize( clusterSize );
		df->setTotalClusters(totalClusters - 1);
		
		//Populate the File System Info sector with relevant values
		df->getFileSystemInfoSector()->setFreeClusterCount(totalClusters);
		df->getFileSystemInfoSector()->setNextFreeCluster(START_CLUSTER + 1);
	}

	size_t Formatter::diskSizeToSectorsPerCluster(size_t sizeInKb)
	{
		assert(sizeInKb >= 66600, "Make sure the file size passed is greater than 35.5MB");

		if (sizeInKb <= 532480) return 1;
		if (sizeInKb <= 16777216) return 8;
		if (sizeInKb <= 33554432) return 16;
		if (sizeInKb <= 67108864) return 32;
		return 64;
	}

	size_t Formatter::getReservedSectorCount()
	{
		//TODO: modify this parameter when adding support for FAT12/FAT16
		//For FAT12 and 16, this value should never be anything other than 1. 
		//For FAT32, this value is typically 32
		return 32;
	}

	size_t Formatter::getNumFats()
	{
		return 2;
	}

	size_t Formatter::getRootEntries() 
	{
		//TODO: Modify this when FAT32 is added
		return 0; 
	}

	size_t Formatter::getRootDirectorySectors(DiskFile* df)
	{
		size_t rootEntries = df->getBootSector()->getRootEntryCount();
		size_t bytesPerSector = df->getBootSector()->getBytesPerSector();
		size_t rootDirectorySectors = ((rootEntries * 32) + (bytesPerSector - 1)) / bytesPerSector;
		return rootDirectorySectors;
	}

	size_t Formatter::getSectorsPerFat(DiskFile* df)
	{
		size_t reservedSectors = df->getBootSector()->getReservedSectorCount();
		size_t sectorsPerCluster = df->getBootSector()->getSectorsPerCluster();
		size_t numFats = df->getBootSector()->getNumFats();
		//WARN: This might need to be modified when the actual data is gathered
		size_t sectorsInDisk = df->getBootSector()->getTotalSectors32();
		size_t rootDirectorySectors = getRootDirectorySectors(df);

		size_t tmpVal1 = sectorsInDisk - (reservedSectors + rootDirectorySectors);
		size_t tmpVal2 = (256 * sectorsPerCluster) + numFats;

		//TODO: Add a condition here when other FAT types are added
		tmpVal2 /= 2;

		size_t sectorsPerFat = (tmpVal1 + (tmpVal2 - 1)) / tmpVal2;
		return sectorsPerFat;
	}

	size_t Formatter::getSectorsInDataRegion(DiskFile* df)
	{
		size_t totalSectors = df->getBootSector()->getTotalSectors32();
		size_t reservedSectors = df->getBootSector()->getReservedSectorCount();
		size_t numFats = df->getBootSector()->getNumFats();
		size_t sectorsPerFat = df->getBootSector()->getSectorsPerFat();
		size_t rootDirectorySectors = getRootDirectorySectors(df);

		size_t dataSectors = totalSectors - (reservedSectors + (numFats * sectorsPerFat) + rootDirectorySectors);

		return dataSectors;
	}

}