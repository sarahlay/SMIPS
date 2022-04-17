////////////////////////////////////////////////////////////////////////
// COMP1521 --- Assignment 2: SMIPS
// Filename:            program.h
// Written by:          Sarah Lay (z5161194)
// Date of Submission:  09/08/2020
//
// This code is contains #defines, #includes and function prototypes.
// The program.h & program.c contents assist in processing and printing
// 32-bit hexadecimal instruction codes for MIPS instructions.
//

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Indexing
#define FILE_INDEX      1
#define ARG_INDEX       4
#define SYSCALL_INDEX   2

// Array Lengths
#define MAX_LEN         20
#define NUM_REGISTERS   32
#define MAX_OUTPUT      100000

// Valid Syscall Types
#define PRINT_INT       1
#define PRINT_CHAR      11
#define EXIT            10

// Printing
#define DISPOSE         3

// Shifting Bits
#define S_SHIFT         21
#define T_SHIFT         16
#define D_SHIFT         11

// Masks
#define MASK_FRONT      0xFC000000
#define MASK            0x0000001F
#define MASK_NEG        0x00000080
#define MASK_8BITS      0x000000FF
#define MASK_16BITS     0x0000FFFF

// MIPS Instructions
#define SYSCALL         0x0000000C
#define ADD             0x00000020
#define SUB             0x00000022
#define AND             0x00000024
#define OR              0x00000025
#define SLT             0x0000002a
#define MUL             0x70000002
#define BEQ             0x01000000
#define BNE             0x14000000
#define ADDI            0x20000000
#define SLTI            0x38000000
#define ANDI            0x28000000
#define ORI             0x34000000
#define LUI             0x3C000000

// Exiting
#define EXIT_SUCCESS    0
#define EXIT_FAILURE    1

// Function Prototypes

// Input: a binary MIPS instruction, PC pointer, registers array & isValid instruction pointer
// Function: if MIPS instruction is valid, updates the registers else, sets isValid to false
void mipsEmulator(uint32_t instruction, int *PC, int registers[NUM_REGISTERS], bool *isValid);

// Input: a binary MIPS instruction & PC pointer
// Function: prints out the MIPS instruction
void mipsPrint(uint32_t instruction, int *PC);

// Input: a 16 bit binary
// Returns: performs twos complement if the number is negative and returns an int
int twosComplement(uint16_t bytes);
