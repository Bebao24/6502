#include "cpu.h"
#include <stdio.h>

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

uint8_t CPU_FetchByte(cpu_t* cpu)
{
	uint8_t data = cpu->memory[cpu->PC];
	cpu->PC++;
	return data;
}

// Execute instructions step by step
void CPU_Execute(cpu_t* cpu)
{
	// TODO: Emulate CPU cycles
	uint8_t ins = CPU_FetchByte(cpu);
	printf("Instruction: 0x%02X, PC: 0x%X\n", ins, cpu->PC);
}



