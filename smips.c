////////////////////////////////////////////////////////////////////////
// COMP1521 --- Assignment 2: SMIPS
// Filename:            smips.c
// Written by:          Sarah Lay (z5161194)
// Date of Submission:  09/08/2020
//
// This code processes a file given via standard input consisting of
// 32-bit instruction codes for MIPS instructions as hexadecimal numbers.
//
// The output from smips.c would be:
//      - The instruction (assembler) corresponding to each instruction code.
//      - The output produced by syscalls when executing the MIPS instructions.
//      - The register values when the program terminates.
//

# include "output.h"
# include "program.h"

int main(int argc, char *argv[]) {
    // Initialising Variables
    // File Processing
    FILE        *in;
    uint32_t    bytes;
    char        string[MAX_LEN];
    uint32_t    instructions[MAX_OUTPUT]        = {0};
    int         line                            = 0;

    // Registers
    int         registers[NUM_REGISTERS]        = {0};

    // Syscall Processing
    int         PC                              = 0;
    int         syscallCounter                  = 0;
    int         syscalls[MAX_OUTPUT]            = {0};
    int         syscallTypes[MAX_OUTPUT]        = {0};

    // Booleans
    bool        isValid                         = true;
    bool        badSyscall                      = false;

    // Processing File
    if (argc != 2) {
        // No file name given
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    in = fopen(argv[FILE_INDEX], "r");
    if (in == NULL) {
        // File does not exist (unable to open)
        fprintf(stderr, "%s: ", argv[0]);
        perror(argv[1]);
        return 1;
    }

    while (fgets(string, MAX_LEN, in) != NULL) {
        // Storing file contents into instructions array
        string[strlen(string) - 1] = '\0';
        bytes = (uint32_t)strtol(string, NULL, 16);
        instructions[line] = bytes;
        line++;
    }

    // Program
    for (PC = 0; PC < line; PC++) {
        // Setting registers array
        mipsEmulator(instructions[PC], &PC, registers, &isValid);

        // Checking for a bad syscall
        if (instructions[PC] == SYSCALL && badSyscall == false) {
            syscallCounter = setSyscalls(
                syscalls, syscallTypes, syscallCounter, registers, &badSyscall);
            if (badSyscall == true) {
                // Bad syscall found
                break;
            }
        }
        // Checking for Invalid Instruction Code
        if (!isValid) {
            // Printing error message
            printf("%s:%d: invalid instruction code: %08x \n",
                argv[1], PC + 1, instructions[PC]);
            return EXIT_FAILURE;
        }
    }

    // Printing Program
    printf("Program\n");
    for (PC = 0; PC < line; PC++) {
        mipsPrint(instructions[PC], &PC);
    }

    // Output
    printf("Output\n");

    // Running Syscalls
    runSyscalls(registers, syscalls, syscallTypes, syscallCounter);

    // Registers After Execution
    printf("Registers After Execution\n");

    // Printing Registers
    printRegisters(registers);

    return EXIT_SUCCESS;
}