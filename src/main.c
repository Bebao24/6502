#include <stdio.h>
#include "rom.h"
#include "cpu.h"
#include <stdlib.h>

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		fprintf(stderr, "Usage: ./emulator <rom path>\n");
		return -1;
	}

	// Initialize the CPU
	cpu_t cpu;
	// Setup reset vector
	cpu.memory[0xFFFC] = 0x00;
	cpu.memory[0xFFFD] = 0x80;

	CPU_Reset(&cpu);

	// Load the ROM into memory 
	char* path = argv[1];
	size_t fileSize;
	load_rom(path, &fileSize, &cpu.memory[0x8000]);

	for (int i = 0; i < 1000; i++)
	{
		CPU_Execute(&cpu);
	}

	CPU_DumpRegisters(&cpu);

	return 0;
}
