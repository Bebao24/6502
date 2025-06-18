#include "cpu.h"

void CPU_Reset(cpu_t* cpu)
{
	// The 6502 is little endian
	cpu->PC = (cpu->memory[0xFFFD] << 8) | cpu->memory[0xFFFC]; 
	cpu->SP = 0xFD;
	// Reset registers
	cpu->A = 0;
	cpu->X = 0;
	cpu->Y = 0;

	// Reset CPU status flags
	cpu->C = 0;
	cpu->Z = 0;
	cpu->I = 0;
	cpu->D = 0;
	cpu->B = 0;
	cpu->V = 0;
	cpu->N = 0;

	// Initialize the memory (assumming it's all RAM)
	for (int i = 0; i < MEM_SIZE; i++)
	{
		cpu->memory[i] = 0;
	}
}





