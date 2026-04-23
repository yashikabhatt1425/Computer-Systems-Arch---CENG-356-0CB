/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
// Please finish the following functions for lab 8.
// Lab 8 will perform the following functions:
//   1. Fetch the code stored in memory
//   2. Decode the code and prepare for the execution of the code.
//   3. Setup the execution function for CPU.

// Lab 9 will perform the following functions:
//   4. Execute the code stored in the memory and print the results.
#include "header.h"
#include "lab8header.h"

extern char *regNameTab[N_REG];
extern unsigned int PCRegister; // PC register

void CPU(unsigned char *mem)
{
    unsigned int machineCode = 0;
    unsigned char opcode = 0;
 unsigned int temp;
    PCRegister = CODESECTION;

     while (1)
    {
        printf("\nPC:%x\n", PCRegister);

        machineCode = CPU_fetchCode(mem, PCRegister);

        opcode = CPU_Decode(machineCode);

        if (opcode == 0 && machineCode == 0)
            break;

        printf("Decoded Opcode is: %02X\n", opcode);

        CPU_Execution(opcode, machineCode, mem);
    }

// This is an infinite while loop
                 // When you fetch a machineCode of 00000000, the loop breaks.
    printRegisterFiles();     // After the code execution, print all the register contents on screen.
    printDataMemoryDump(mem); // After the code execution, print the memory dump of the data section.
}

// Lab 8 - Step 1. Finish the CPU_fectchCode function to
//         read the code section from memory and
//         get the 32-bit machine code from the memory.
unsigned int CPU_fetchCode(char *mem, int codeOffset){
    // Read 4 bytes as one 32-bit instruction
    // safe 32-bit load
    unsigned int machineCode;

    memcpy(&machineCode, mem + codeOffset, sizeof(unsigned int));

    return machineCode;
}


// Lab 8 - Step 2. Finish the CPU_Decode function to
//         decode the instruction and return the
//         opcode/function of the instruction.
//         Hints: Need to consider how to find the opcode/function from different types of instructions:
//                i.e., I-, J- and R-type instructions.
//                The return value should be a 6-bit bianry code.
unsigned char CPU_Decode(unsigned int machineCode){

unsigned char opcode;

    // Extract first 6 bits (opcode)
    opcode = (machineCode >> 26) & 0x3F;

    // If R-type instruction
    if (opcode == 0){
        // return function field (last 6 bits)
        return machineCode & 0x3F;
    }

    // Otherwise return opcode
    return opcode;
}
// Lab 9: Finish the function CPU_Execution to run all the instructions.
void CPU_Execution(unsigned char opcode, unsigned int machineCode, char *mem)
{
    unsigned char rs = 0, rt = 0, rd = 0;
short imm = 0;
  unsigned int temp = 0;
unsigned int addr = 0;
    switch (opcode)  // execute different functions when opcode is set differently.
    {
		// This is an example how lab will be executed. Please follow this example and finish exections of the code.
		// Hint: you need to implement the following instructions here:
		//       la, add, lb, bge, lw, sw, addi, j
        case 0b101111:   //"la" instruction.
            // assign the address rt = immediate address stored in machineCode;
            // first find the rt index in the register array.
            rt = (machineCode & 0x001F0000) >> 16;
            // assign the address stored in immediate field to regFile[rt];
            regFile[rt] = machineCode & 0x0000FFFF;  // get the last 16 bit as address.
            // update PCregister ???? Pay special attention to branch instructions.
            PCRegister += 4;

            break;


        // ---------------- LW ----------------
        case 0b100011:
            rs = (machineCode >> 21) & 0x1F;
            rt = (machineCode >> 16) & 0x1F;
            imm = (short)(machineCode & 0xFFFF);


memcpy(&temp, mem + regFile[rs] + imm, sizeof(unsigned int));
regFile[rt] = temp;
            PCRegister += 4;
            break;

        // ---------------- SW ----------------
       case 0b101011:
    rs = (machineCode >> 21) & 0x1F;
    rt = (machineCode >> 16) & 0x1F;
    imm = (short)(machineCode & 0xFFFF);

    memcpy(mem + regFile[rs] + imm, &regFile[rt], sizeof(unsigned int));

    PCRegister += 4;
    break;
        // ---------------- J ----------------
        case 0b000010:
            addr = machineCode & 0x03FFFFFF;
             PCRegister = addr * 4;
            break;

        // ---------------- BGE ----------------
        case 0b000001:
            rs = (machineCode >> 21) & 0x1F;
            rt = (machineCode >> 16) & 0x1F;
            imm = (short)(machineCode & 0xFFFF);

            if (regFile[rs] >= regFile[rt])
                PCRegister += 4 + (imm * 4);
            else
                PCRegister += 4;

            break;

        // ---------------- ADDI ----------------
        case 0x08:
            rs = (machineCode >> 21) & 0x1F;
            rt = (machineCode >> 16) & 0x1F;
            imm = (short)(machineCode & 0xFFFF);

            regFile[rt] = regFile[rs] + imm;
            PCRegister += 4;
            break;

        // ---------------- ADD (R-type) ----------------
        case 0x20:
            rs = (machineCode >> 21) & 0x1F;
            rt = (machineCode >> 16) & 0x1F;
            rd = (machineCode >> 11) & 0x1F;

            regFile[rd] = regFile[rs] + regFile[rt];
            PCRegister += 4;
            break;

        // ---------------- DEFAULT ----------------
        default:
            printf("Wrong instruction! %02X %08X\n", opcode, machineCode);
            system("PAUSE");
            exit(3);
    }

    if (DEBUG_CODE)
    {
        printf("Code Executed: %08X\n", machineCode);
        printf("****** PC Register is %08X ******\n", PCRegister);
    }
}
// Lab 8 - Step 3. Print all the 32 registers in regFile and names saved in
//         regNameTab. For example, it should print
//         $zero = 0x00000000
//         $at  = ... ... etc.
void printRegisterFiles(){
  printf("\n==== Register File Dump ====\n");
    for (int i = 0; i < N_REG; i++){
        printf("%s = 0x%08X\n", regNameTab[i], regFile[i]);
    }
}
 // Lab 8 - Step 4. Call function memory_dump and pass the proper parameters to dump the first 256
//          bytes from Data section.
void printDataMemoryDump(char *mem)
{printf("\n=========== Data Memory Dump ============\n");
    memory_dump(mem, DATASECTION, 256);
    printf("=========================================\n");
    }
