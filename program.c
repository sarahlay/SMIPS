////////////////////////////////////////////////////////////////////////
// COMP1521 --- Assignment 2: SMIPS
// Filename:            program.c
// Written by:          Sarah Lay (z5161194)
// Date of Submission:  09/08/2020
//
// This code contains functions that assist in processing and printing
// 32-bit hexadecimal instruction codes for MIPS instructions.
//

# include "program.h"

// Input: a binary MIPS instruction, PC pointer, registers array & isValid instruction pointer
// Function: if MIPS instruction is valid, updates the registers else, sets isValid to false
void mipsEmulator(uint32_t instruction, int *PC, int registers[NUM_REGISTERS], bool *isValid)
{
    if (instruction == SYSCALL) {
        return;
    }

    // Setting variables
    uint32_t s = (instruction >> S_SHIFT) & MASK;
    uint32_t t = (instruction >> T_SHIFT) & MASK;

    if ((instruction & MASK_FRONT) == 0) {

        // Functions with $d register
        uint32_t d = (instruction >> D_SHIFT) & MASK;
        if ((instruction & SLT) == SLT) {
            // slt     $d, $s, $t	d = 1 if s < t else 0	000000ssssstttttddddd00000101010
            if (registers[s] < registers[t]) {
                registers[d] = 1;
            } else {
                registers[d] = 0;
            }

        } else if ((instruction & OR) == OR) {
            // or      $d, $s, $t	d = s | t	            000000ssssstttttddddd00000100101
            registers[d] = registers[s] | registers[t];
        } else if ((instruction & SUB) == SUB) {
            // sub     $d, $s, $t	d = s - t	            000000ssssstttttddddd00000100010
            registers[d] = registers[s] - registers[t];
        } else if ((instruction & AND) == AND) {
            // and     $d, $s, $t	d = s & t	            000000ssssstttttddddd00000100100
            registers[d] = registers[s] & registers[t];
        } else if ((instruction & ADD) == ADD) {
            // add     $d, $s, $t	d = s + t	            000000ssssstttttddddd00000100000
            registers[d] = registers[s] + registers[t];
        } else {
            // Invalid instruction
            *isValid = false;
        }

    } else if ((instruction & MUL) == MUL) {
        // mul     $d, $s, $t	d = s * t	            011100ssssstttttddddd00000000010
        uint32_t d = (instruction >> D_SHIFT) & MASK;
        registers[d] = registers[s] * registers[t];
    } else if ((instruction & LUI) == LUI) {
        // lui     $t, I	t = I << 16	                00111100000tttttIIIIIIIIIIIIIIII
        uint16_t I = instruction & MASK_16BITS;
        registers[t] = I << 16;
    } else {
        int I = twosComplement(instruction & MASK_16BITS);
        if ((instruction & ORI) == ORI) {
            // ori     $t, $s, I	t = s | I	            001101ssssstttttIIIIIIIIIIIIIIII
            I = instruction & MASK_16BITS;
            registers[t] = registers[s] | I;
        } else if ((instruction & SLTI) == SLTI) {
            // slti    $t, $s, I	t = (s < I)	            001010ssssstttttIIIIIIIIIIIIIIII
            registers[t] = (registers[s] < I);
        } else if ((instruction & ANDI) == ANDI) {
            // andi    $t, $s, I	t = s & I	            001100ssssstttttIIIIIIIIIIIIIIII
            registers[t] = registers[s] & I;
        } else if ((instruction & ADDI) == ADDI) {
            // addi    $t, $s, I	t = s + I	            001000ssssstttttIIIIIIIIIIIIIIII
            registers[t] = registers[s] + I;
        } else if ((instruction & BNE) == BNE) {
            // bne     $s, $t, I	if (s != t) PC += I	    000101ssssstttttIIIIIIIIIIIIIIII
            if (registers[s] != registers[t]) {
                if (I < 0) (*PC) += I - 1;
            }
        } else if ((instruction & BEQ) == BEQ) {
            // beq     $s, $t, I	if (s == t) PC += I	    000100ssssstttttIIIIIIIIIIIIIIII
            if (registers[s] == registers[t]) {
                if (I < 0) (*PC) += I - 1;
            }

        } else {
            // Invalid Instruction
            *isValid = false;
        }
    }

    // Ensuring register 0 remains unchanged
    registers[0] = 0;
    return;
}

// Input: a binary MIPS instruction & PC pointer
// Function: prints out the MIPS instruction
void mipsPrint(uint32_t instruction, int *PC)
{
    if (instruction == SYSCALL) {
        printf("%*d: syscall\n", DISPOSE, *PC);
        return;
    }

    // function array stores function name to be printed
    char function[MAX_LEN];

    // Setting Variables
    uint32_t s = (instruction >> S_SHIFT) & MASK;
    uint32_t t = (instruction >> T_SHIFT) & MASK;

    if ((instruction & MASK_FRONT) == 0) {

        // Functions with $d, $s, $t registers
        uint32_t d = (instruction >> D_SHIFT) & MASK;
        if ((instruction & SLT) == SLT) {
            // slt     $d, $s, $t	d = 1 if s < t else 0	000000ssssstttttddddd00000101010
            strcpy(function, "slt");
        } else if ((instruction & OR) == OR) {
            // or      $d, $s, $t	d = s | t	            000000ssssstttttddddd00000100101
            strcpy(function, "or");
        } else if ((instruction & SUB) == SUB) {
            // sub     $d, $s, $t	d = s - t	            000000ssssstttttddddd00000100010
            strcpy(function, "sub");
        } else if ((instruction & AND) == AND) {
            // and     $d, $s, $t	d = s & t	            000000ssssstttttddddd00000100100
            strcpy(function, "and");
        } else if ((instruction & ADD) == ADD) {
            // add     $d, $s, $t	d = s + t	            000000ssssstttttddddd00000100000
            strcpy(function, "add");
        }

        printf("%*d: %s  $%d, $%d, $%d\n", DISPOSE, *PC, function, d, s, t);
    } else if ((instruction & MUL) == MUL) {
        // mul     $d, $s, $t	d = s * t	            011100ssssstttttddddd00000000010
        uint32_t d = (instruction >> D_SHIFT) & MASK;
        strcpy(function, "mul");
        printf("%*d: %s  $%d, $%d, $%d\n", DISPOSE, *PC, function, d, s, t);
    } else if ((instruction & LUI) == LUI) {
        // lui     $t, I	t = I << 16	                00111100000tttttIIIIIIIIIIIIIIII
        uint32_t I = instruction & MASK_16BITS;
        strcpy(function, "lui");
        printf("%*d: %-4s $%d, %d\n", DISPOSE, *PC, function, t, I);
    } else {

        // Performing twos complement on I
        int I = twosComplement(instruction & MASK_16BITS);
        if ((instruction & ORI) == ORI) {
            // ori     $t, $s, I	t = s | I	            001101ssssstttttIIIIIIIIIIIIIIII
            I = instruction & MASK_16BITS;
            strcpy(function, "ori");
        } else if ((instruction & SLTI) == SLTI) {
            // slti    $t, $s, I	t = (s < I)	            001010ssssstttttIIIIIIIIIIIIIIII
            strcpy(function, "slti");
        } else if ((instruction & ANDI) == ANDI) {
            // andi    $t, $s, I	t = s & I	            001100ssssstttttIIIIIIIIIIIIIIII
            strcpy(function, "andi");
        } else if ((instruction & ADDI) == ADDI) {
            // addi    $t, $s, I	t = s + I	            001000ssssstttttIIIIIIIIIIIIIIII
            strcpy(function, "addi");
        } else if ((instruction & BNE) == BNE) {
            // bne     $s, $t, I	if (s != t) PC += I	    000101ssssstttttIIIIIIIIIIIIIIII
            strcpy(function, "bne");
            uint32_t temp = s;
            s = t;
            t = temp;
        } else if ((instruction & BEQ) == BEQ) {
            // beq     $s, $t, I	if (s == t) PC += I	    000100ssssstttttIIIIIIIIIIIIIIII
            strcpy(function, "beq");
            uint32_t temp = s;
            s = t;
            t = temp;
        }

        printf("%*d: %-4s $%d, $%d, %d\n", DISPOSE, *PC, function, t, s, I);
    }
}

// Input: a 16 bit binary
// Returns: performs twos complement if the number is negative and returns an int
int twosComplement(uint16_t bytes)
{
    if (bytes & MASK_NEG) {
        // Inverting bytes
        bytes = ~bytes;

        // Returning inverted bytes + 1
        return -(bytes + 1);
    }

    return bytes;
}
