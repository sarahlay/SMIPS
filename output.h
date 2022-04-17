////////////////////////////////////////////////////////////////////////
// COMP1521 --- Assignment 2: SMIPS
// Filename:            output.h
// Written by:          Sarah Lay (z5161194)
// Date of Submission:  09/08/2020
//
// This code contains function prototypes that assist in executing
// system calls, printing outputs and printing registers after execution.
//

# include "program.h"

// Function Prototypes

// Input: int index, registers array, syscalls array and syscallType array
// Returns: a new index with the current number of syscalls
// Function: sets the syscall output and type in the index provided
int setSyscalls(int syscalls[MAX_OUTPUT], int syscallTypes[MAX_OUTPUT], int index, int registers[NUM_REGISTERS], bool *invalidSyscall);

// Intput:  registers array,
// Returns: true is the syscall is valid and false if invalid.
bool isValidSyscall(int registers[NUM_REGISTERS]);

// Input: registers array, syscalls array, syscallType array
// Function: runs the syscalls given
void runSyscalls(int registers[NUM_REGISTERS], int syscalls[MAX_OUTPUT], int syscallTypes[MAX_OUTPUT], int outputCounter);

// Input: registers array
// Function: prints the non-empty registers after execution
void printRegisters(int registers[NUM_REGISTERS]);