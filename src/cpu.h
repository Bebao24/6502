#pragma once
#include <stdint.h>

// 0 - 0xFFFF
#define MEM_SIZE 0x10000

typedef struct
{
	// Registers
	uint8_t A, X, Y;

	uint16_t PC; // Program counter
	uint8_t SP; // Stack pointer

	// Status flags
	uint8_t C : 1;
	uint8_t Z : 1;
	uint8_t I : 1;
	uint8_t D : 1;
	uint8_t B : 1;
	uint8_t V : 1;
	uint8_t N : 1;

	// Memory
	uint8_t memory[MEM_SIZE];
} cpu_t;

void CPU_Reset(cpu_t* cpu);


