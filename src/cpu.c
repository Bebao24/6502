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
	cpu->PS = 0;

	// Initialize the memory (assumming it's all RAM)
	for (int i = 0; i < MEM_SIZE; i++)
	{
		cpu->memory[i] = 0;
	}
	
	// CPU reset takes time
	cpu->cycles = 8;
}

uint8_t CPU_FetchByte(cpu_t* cpu)
{
	uint8_t data = cpu->memory[cpu->PC];
	cpu->PC++;
	cpu->cycles++;
	return data;
}

uint16_t CPU_FetchWord(cpu_t* cpu)
{
	uint16_t data = cpu->memory[cpu->PC];
	cpu->PC++;

	data |= (cpu->memory[cpu->PC] << 8);
	cpu->PC++;

	cpu->cycles += 2;
	return data;
}

uint8_t CPU_ReadByte(cpu_t* cpu, uint16_t address)
{
	uint8_t data = cpu->memory[address];
	cpu->cycles++;
	return data;
}

uint16_t CPU_ReadWord(cpu_t* cpu, uint16_t address)
{
	uint8_t lowByte = CPU_ReadByte(cpu, address);
	uint8_t highByte = CPU_ReadByte(cpu, address + 1);
	return lowByte | (highByte << 8);
}

// Instructions opcodes
#define INS_LDA_IM   0xA9
#define INS_LDA_ZP   0xA5
#define INS_LDA_ZPX  0xB5
#define INS_LDA_ABS  0xAD
#define INS_LDA_ABSX 0xBD
#define INS_LDA_ABSY 0xB9

#define INS_JMP_ABS 0x4C
#define INS_JMP_IND 0x6C

void CPU_LoadSetFlags(cpu_t* cpu, uint8_t reg)
{
	// Set processor status for instructions like lda, ldx, ldy
	cpu->flags.Z = (reg == 0); // Zero flag
	cpu->flags.N = (reg & 0b10000000) > 0; // Negative flag
}

// Execute instructions step by step
void CPU_Execute(cpu_t* cpu)
{
	uint8_t ins = CPU_FetchByte(cpu);
	switch (ins)
	{
		case INS_LDA_IM:
		{
			uint8_t value = CPU_FetchByte(cpu);
			cpu->A = value;
			CPU_LoadSetFlags(cpu, value);
			break;
		}
		case INS_LDA_ZP:
		{
			uint8_t address = CPU_FetchByte(cpu);
			uint8_t value = CPU_ReadByte(cpu, address);
			cpu->A = value;
			CPU_LoadSetFlags(cpu, value);
			break;
		}
		case INS_LDA_ZPX:
		{
			uint8_t BaseAddr = CPU_FetchByte(cpu);
			uint8_t addr = (BaseAddr + cpu->X) & 0xFF;
			cpu->cycles++;

			uint8_t value = CPU_ReadByte(cpu, addr);
			cpu->A = value;
			CPU_LoadSetFlags(cpu, value);
			break;
		}
		case INS_LDA_ABS:
		{
			uint16_t address = CPU_FetchWord(cpu);
			uint8_t value = CPU_ReadByte(cpu, address);
			cpu->A = value;
			CPU_LoadSetFlags(cpu, value);
			break;
		}
		case INS_LDA_ABSX:
		{
			uint16_t address = CPU_FetchWord(cpu);
			address += cpu->X;
			uint8_t value = CPU_ReadByte(cpu, address);
			cpu->A = value;
			CPU_LoadSetFlags(cpu, value);
			break;
		}
		case INS_LDA_ABSY:
		{
			uint16_t address = CPU_FetchWord(cpu);
			address += cpu->Y;
			uint8_t value = CPU_ReadByte(cpu, address);
			cpu->A = value;
			CPU_LoadSetFlags(cpu, value);
			break;
		}
		case INS_JMP_ABS:
		{
			uint16_t address = CPU_FetchWord(cpu);
			cpu->PC = address;
			break;
		}
		case INS_JMP_IND:
		{
			uint16_t address = CPU_FetchByte(cpu);
			uint16_t jmpAddr = CPU_ReadWord(cpu, address);
			cpu->PC = jmpAddr;
			break;
		}
		default:
			// Unimplemented instruction or invalid opcode
			break;
	}
}

void CPU_DumpRegisters(cpu_t* cpu)
{
	printf("\n----------CPU Registers dump----------\n");
	printf("A: $%X, X: $%X, Y: $%X\n", cpu->A, cpu->X, cpu->Y);
	printf("Processor status: $%X\n", cpu->PS);
	printf("SP: $%X, PC: $%X", cpu->SP, cpu->PC);
	printf("\n-----------------END------------------\n");
}


