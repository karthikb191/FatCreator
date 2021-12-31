#pragma once
#ifndef _H_FAT_FORMATTER
#define _H_FAT_FORMATTER
namespace FAT
{
	class DiskFile;
	class Formatter
	{
	public:
		void format(DiskFile* df);
		
		size_t getSectorsPerFat(DiskFile* df);
		size_t getSectorsInDataRegion(DiskFile* df);
		size_t getRootDirectorySectors(DiskFile* df);

		static size_t diskSizeToSectorsPerCluster(size_t size);
		static size_t getReservedSectorCount();
		static size_t getNumFats();
		static size_t getRootEntries();
	private:
	};
}

#endif // !_H_FAT_FORMATTER
