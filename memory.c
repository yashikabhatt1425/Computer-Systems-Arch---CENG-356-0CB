
/*
============================================================================
Name : Lab6.c
Author : Austin Tian
Revised by :
Version :
Copyright : Copyright 2023
Description : Lab 6 in C, ANSI-C Style
============================================================================
*/
#include "header.h"
// Menu for the testing.
char *menu = "\n" \
" ***********Please select the following options**********************\n" \
" * This is the memory operation menu (Lab 6) *\n" \
" ********************************************************************\n" \
" * 1. Write a double-word (32-bit) to the memory *\n" \
" ********************************************************************\n" \
" * 2. Read a byte (8-bit) data from the memory *\n" \
" * 3. Read a double-word (32-bit) data from the memory *\n" \
" ********************************************************************\n" \
" * 4. Generate a memory dump from any memory location *\n" \
" ********************************************************************\n" \
" * e. To Exit, Type 'e' or 'E' *\n" \
" ********************************************************************\n";
//---------------------------------------------------------------
// Generate a random number between 0x00 and 0xFF.
unsigned char rand_generator()
{
return rand()%255; // generate a random number between 0 and 255.
}
//---------------------------------------------------------------
void free_memory(char *base_address)
{
free(base_address); // free memory after use to avoid memory leakage.
return;
}
//---------------------------------------------------------------
char *init_memory()
{
 // Grab 1,048,576 bytes from the heap
 char *mem = (char *)malloc(MEM_SIZE);
if (mem == NULL) {
printf("Critical Error: Memory allocation failed.\n");
exit(1);
}
 // Fill every single byte with a random value
for (int i = 0; i < MEM_SIZE; i++) {
    mem[i] = 0;
}
return mem;
}
//---------------------------------------------------------------
// Writes a 32-bit value into 4 consecutive bytes starting at the offset
void write_dword(const char *base_address, const int offset, const unsigned int dword_data) {


 // Check if we are writing past the 1MB limit
if (offset + 3 < MEM_SIZE) {
// Cast the specific memory location to an unsigned int pointer to store 4 bytes at once
unsigned int *ptr = (unsigned int *)(base_address + offset);
*ptr = dword_data;
}
}
//---------------------------------------------------------------
// Writes a single byte (8-bit) into memory
void write_byte(const char *base_address, const int offset, const unsigned char byte_data) {

    if (offset < MEM_SIZE) {
        char *ptr = (char *)(base_address + offset);
        *ptr = byte_data;

    }
}
//---------------------------------------------------------------
// Grabs a single 8-bit value from the specified offset
unsigned char read_byte(const char *base_address, const int offset) {
if (offset < MEM_SIZE) {
unsigned char data = (unsigned char)base_address[offset];
printf("Data at 0x%X [Byte]: 0x%02X\n", offset, data);
return data;
}
return 0;
}
//---------------------------------------------------------------
// Grabs a 32-bit value (4 bytes) starting at the specified offset
unsigned int read_dword(const char *base_address, const int offset) {
if (offset + 3 < MEM_SIZE) {
unsigned int data = *(unsigned int *)(base_address + offset);
printf("Data at 0x%X [D-Word]: 0x%08X\n", offset, data);
return data;
}
return 0;
}
//---------------------------------------------------------------
// Prints a formatted grid of memory: Offset | Hex Values | ASCII conversion
void memory_dump(const char *base_address, const int offset, unsigned int dumpsize) {
 // Sanitize the dump size input
if (dumpsize < MIN_DUMP_SIZE || dumpsize > 1024) {
dumpsize = MIN_DUMP_SIZE;
}

for (unsigned int i = 0; i < dumpsize; i += 16) {
// 1. Show the current memory address offset
printf("%08X ", offset + i);
// 2. Print 16 bytes of data in Hex format
for (int j = 0; j < 16; j++) {
unsigned char val = (unsigned char)base_address[offset + i + j];
printf("%02X ", val);
}
printf(" ");
// 3. Print the same 16 bytes as ASCII characters (if printable)
for (int j = 0; j < 16; j++) {
unsigned char val = (unsigned char)base_address[offset + i + j];
if (val >= 0x20 && val <= 0x7E) {
printf("%c", val);
} else {
printf("."); // Use a dot for non-printable characters
}
}
printf("\n");
}
}

//---------------------------------------------------------------
void setup_memory()
{
 // Now we need to setup the memory controller for the computer system we
 // will build. Basic requirements:
 // 1. Memory size needs to be 1M Bytes
 // 2. Memory is readable/writable with Byte and Double-Word Operations.
 // 3. Memory can be dumped and shown on screen.
 // 4. Memory needs to be freed (released) at the end of the code.
 // 6. For lab 6, we need to have a user interface to fill in memory,
 // read memory and do memory dump.
 char *mem = init_memory(); // initialize the memory.
 char options =0;
 unsigned int offset, dumpsize;
 char tempchar;
 unsigned int dword_data; // 32-bit operation.
 do{
if (options != 0x0a) // if options has a return key input, skip it.
{
puts(menu); /* prints Memory Simulation */
printf ("\nThe base address of your memory is: %I64Xh (HEX)\n", (long long unsigned int)(mem)); // output base memory first.
puts("Please make a selection:"); // output base memory first.
}
options = getchar();
switch (options)
{
case '1': // write double word.
puts("Please input your memory's offset address (in HEX):");
scanf("%x", (unsigned int*)&offset); // input an offset address (in HEX) to write.
puts("Please input your DOUBLE WORD data to be written (in HEX):");
scanf("%x", (unsigned int*)&dword_data); // input data
write_dword (mem, offset, dword_data); // write a double word to memory.
continue;
case '2': // read byte.
puts("Please input your memory's offset address (in HEX):");
scanf("%x", &offset); // input an offset address (in HEX) to write.
read_byte(mem, offset);
continue;
case '3': // read double word.
puts("Please input your memory's offset address (in HEX):");
scanf("%x", &offset); // input an offset address (in HEX) to write.
read_dword(mem, offset);
continue;
case '4': // generate memory dump starting at offset address (in HEX).
puts("Please input your memory's offset address (in HEX, should be a multiple of 0x10h):");
scanf("%x", &offset); // input an offset address (in HEX) to start.
puts("Please input the size of the memory to be dumped (a number between 256 and 1024 ):");
scanf("%d", &dumpsize); // The size of the memory dump
memory_dump(mem, offset, dumpsize); // generate a memory dump display of dumpsize bytes.
continue;
case 'e':
case 'E':
puts("Code finished, press any key to exit");
free_memory(mem);
while ((tempchar = getchar()) != '\n' && tempchar != EOF); // wait for the enter.
tempchar = getchar();
return; // return to main program.
default:
// puts("Not a valid entry, please try again");
continue;
}
}while (1); // make sure the only exit is from 'e'.
return;
}
