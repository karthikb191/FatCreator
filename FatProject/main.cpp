#include <iostream>
#include "FAT/constants.h"
#include "FAT/disk_file.h"
#include "FAT/boot_sector.h"
#include <sys/stat.h>

int main()
{
    uint32_t size = FAT::DEFAULT_SIZE;

    //Initialize a device with size and all the default values
    FAT::DiskFile diskFile(size);
    diskFile.init();

    const char* fileName = "fatFile";

    FILE* fatFile = fopen(fileName, "wb");
    fseek(fatFile, 0, SEEK_SET);
    
    char* buf = (char*)malloc(FAT::DEFAULT_SIZE);
    memset(buf, 0x0, FAT::DEFAULT_SIZE);
    fwrite(buf, FAT::DEFAULT_SIZE, 1, fatFile);
    //unsigned char buf = 0;
    //for (unsigned int i = 0; i < FAT::DEFAULT_SIZE; i++)
    //    fwrite(&buf, sizeof(buf), 1, fatFile);

    fseek(fatFile, 0, SEEK_SET);

    fwrite(diskFile.getBootSector()->getBuffer(), FAT::SECTOR_SIZE, 1, fatFile);

    size_t freeClusters = diskFile.getFileSystemInfoSector()->getFreeClusterCount();
    size_t nextFreeCluster = diskFile.getFileSystemInfoSector()->getNextFreeCluster();

    fwrite(diskFile.getFileSystemInfoSector()->getBuffer(), FAT::SECTOR_SIZE, 1, fatFile);
    

    //Last two bytes of the Boot sector must have these values. Backup boot sector should not have these values
    unsigned char c = 0x55;
    fseek(fatFile, 510, SEEK_SET);
    fwrite(&c, 1, 1, fatFile);
    c = 0xAA;
    fwrite(&c, 1, 1, fatFile);
    

    //Write to the backup boot sector
    size_t bkBootSector = diskFile.getBootSector()->getBkBootSector();
    fseek(fatFile, bkBootSector * FAT::SECTOR_SIZE, SEEK_SET);
    fwrite(diskFile.getBootSector()->getBuffer(), FAT::SECTOR_SIZE, 1, fatFile);

    ////Filling the end of the reserved Sectors. Not sure if this code really works
    size_t resSecCount = diskFile.getBootSector()->getReservedSectorCount();
    fseek(fatFile, resSecCount * FAT::SECTOR_SIZE, SEEK_SET);
    unsigned int buf2 = 0x0FFFFFF8;
    fwrite(&buf2, sizeof(buf2), 1, fatFile);
    buf2 = 0xFFFFFFFF;
    fwrite(&buf2, sizeof(buf2), 1, fatFile);
    fwrite(&buf2, sizeof(buf2), 1, fatFile);

    /*close the file*/
    fclose(fatFile);

    //TODO: Remove the code below. Its only for testing
    //char fsType[9];
    //memset(fsType, '\0', 9);
    //memcpy(fsType, diskFile.getBootSector()->getFileSystemType(), 8);
    //printf("%s\n", fsType);
    
    //std::cout << "File System Type: " << fsType << std::endl;
    //std::cout << "Finished!" << fsType << std::endl;
    
}
