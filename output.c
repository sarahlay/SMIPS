////////////////////////////////////////////////////////////////////////
// COMP1521 --- Assignment 2: SMIPS
// Filename:            output.h
// Written by:          Sarah Lay (z5161194)
// Date of Submission:  09/08/2020
//
// This code contains function prototypes that assist in executing
// system calls, printing outputs and printing registers after execution.
//

# include "output.h"

// Input: int index, registers array, syscalls array and syscallType array
// Returns: a new index with the current number of syscalls
// Function: sets the syscall output and type in the index provided
int setSyscalls(int syscalls[MAX_OUTPUT], int syscallTypes[MAX_OUTPUT], int index, int registers[NUM_REGISTERS], bool *invalidSyscall)
{
    // Setting Argument for syscall
    syscalls[index] = registers[ARG_INDEX];

    // Setting Syscall type
    syscallTypes[index] = registers[SYSCALL_INDEX];

    // Checking for valid Syscall
    if (!isValidSyscall(registers)) {
        *invalidSyscall = true;
    }

    return (index + 1);
}

// Intput:  registers array,
// Returns: true is the syscall is valid and false if invalid.
bool isValidSyscall(int registers[NUM_REGISTERS])
{
    if (registers[SYSCALL_INDEX] == PRINT_INT || registers[SYSCALL_INDEX] == PRINT_CHAR || registers[SYSCALL_INDEX] == EXIT) {
        return true;
    }

    return false;
}

// Input: registers array, syscalls array, syscallType array
// Function: runs the syscalls given
void runSyscalls(int registers[NUM_REGISTERS], int syscalls[MAX_OUTPUT], int syscallTypes[MAX_OUTPUT], int numSyscalls)
{
    for (int i = 0; i < numSyscalls; i++) {
        if (syscallTypes[i] == PRINT_INT) {
            // Printing Integer
            printf("%d", syscalls[i]);
        } else if (syscallTypes[i] == PRINT_CHAR) {
            // Printing Char
            printf("%c", syscalls[i]);
        } else if (syscallTypes[i] == EXIT) {
            // Exiting
            registers[SYSCALL_INDEX] = syscallTypes[i];
            break;
        } else if (syscallTypes[i] != 0) {
            // Unknown System Call
            printf("Unknown system call: %d\n", syscallTypes[i]);
            registers[SYSCALL_INDEX] = syscallTypes[i];
            break;
        }
    }
}

// Input: registers array
// Function: prints the non-empty registers after execution
void printRegisters(int registers[NUM_REGISTERS]) {
    for (int i = 0; i < NUM_REGISTERS; i++) {
        if (registers[i] != 0) {
            printf("$%-2d = %d\n", i, registers[i]);
        }
    }
}