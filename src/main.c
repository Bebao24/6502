#include <stdio.h>
#include "rom.h"
#include <stdlib.h>

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		fprintf(stderr, "Usage: ./emulator <rom path>\n");
		return -1;
	}

	// Load the ROM
	char* path = argv[1];
	size_t fileSize;
	// This is only for testing, we will actually load the program into the CPU RAM later
	uint8_t* buffer = malloc(512);
	if (!buffer)
	{
		return -1;
	}

	load_rom(path, &fileSize, buffer);

	// Display the ROM content
	for (size_t i = 0; i < fileSize; i++)
	{
		printf("%02X  ", buffer[i]);
	}

	printf("\n");

	return 0;
}
