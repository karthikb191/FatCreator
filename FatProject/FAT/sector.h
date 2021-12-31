#pragma once
#ifndef _H_FAT_SECTOR
#define _H_FAT_SECTOR

#include <exception>
#include <iostream>
#include "constants.h"

namespace FAT
{
	class Sector
	{
	public:

		Sector(size_t pSize) : size(pSize) 
		{
			buffer = malloc(pSize);
			//Default initializing the buffer to 0
			memset(buffer, 0, SECTOR_SIZE);
		}
		virtual ~Sector() {
			free(buffer);
		}

		void* getBuffer() { return buffer; }

		//Get first 8 bytes
		uint8_t get8(size_t offset)
		{
			try {
				if (offset + 1 > size)
					throw(new std::exception());

				return (*(uint8_t*)((BYTE*)buffer + offset) & 0xFF);
			}
			catch (std::exception exception) {
				std::cout << exception.what() << std::endl;
			}
		}
		//Get first 16 bytes
		uint16_t get16(size_t offset)
		{
			try {
				if (offset + 2 > size)
					throw(new std::exception());

				return (*(uint16_t*)((BYTE*)buffer + offset) & 0xFFFF);
			}
			catch (std::exception exception) {
				std::cout << exception.what() << std::endl;
			}
		}
		//Get first 32 bytes after offset
		uint32_t get32(size_t offset)
		{
			try {
				if (offset + 4 > size)
					throw(new std::exception());

				return (*(uint32_t*)((BYTE*)buffer + offset) & 0xFFFFFFFF);
			}
			catch (std::exception exception) {
				std::cout << exception.what() << std::endl;
			}
		}

		
		//Get first 8 bits
		uint16_t set8(size_t offset, size_t value)
		{
			try {
				if (offset + 1 > size)
					throw(new std::exception());

				memcpy((BYTE*)buffer + offset, &value, 1);
			}
			catch (std::exception exception) {
				std::cout << exception.what() << std::endl;
			}
		}
		//Get first 16 bytes
		uint16_t set16(size_t offset, size_t value)
		{
			try {
				if (offset + 2 > size)
					throw(new std::exception());

				memcpy((BYTE*)buffer + offset, &value, 2);
			}
			catch (std::exception exception) {
				std::cout << exception.what() << std::endl;
			}
		}
		//Get first 32 bytes after offset
		uint16_t set32(size_t offset, size_t value)
		{
			try {
				if (offset + 4 > size)
					throw(new std::exception());

				memcpy((BYTE*)buffer + offset, &value, 4);
			}
			catch (std::exception exception) {
				std::cout << exception.what() << std::endl;
			}
		}

		void setBlock(const void* data, size_t offset, size_t length)
		{
			try {
				if ( offset + length > size)
					throw(new std::exception());

				memcpy((BYTE*)buffer + offset, data, length);
			}
			catch (std::exception exception) {
				std::cout << exception.what() << std::endl;
			}
		}
	protected:
		void* buffer;
		size_t size;
	};
}
#endif