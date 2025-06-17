#include "rom.h"
#include <stdlib.h>

bool load_rom(const char* path, size_t* sizeOut, void* addr)
{
	FILE* filePtr = fopen(path, "rb");
	if (!filePtr)
	{
		fprintf(stderr, "Failed to open file %s\n", path);
		return false;
	}

	// Get the file's size
	fseek(filePtr, 0, SEEK_END);
	long fileSize = ftell(filePtr);
	rewind(filePtr);

	size_t readSize = fread(addr, 1, fileSize, filePtr);
	fclose(filePtr);

	// Compare read size
	if (readSize != (size_t)fileSize)
	{
		fprintf(stderr, "Failed to read file %s completely!\n", path);
		return false;
	}
	
	// Set size out
	if (sizeOut)
	{
		*sizeOut = readSize;
	}
	return true;
}



