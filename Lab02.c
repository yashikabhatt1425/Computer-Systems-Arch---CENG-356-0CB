/*
 ============================================================================
 Name        : Lab2.c
 Author      : Yashika Bhatt
 Version     :
 Copyright   : Copyright 2020
 Description : Signed number and unsigned numbers, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define SIZE 32   // maximum size of the binary number is 32 bit.
#define number1 "11000001010010000000000000000000"
#define number2 "01000001010101000000000000000000"
void convert_binary_to_signed(const char *binary);
void convert_binary_to_float(const char *binary);
char *menu =    "\n" \
                "\n" \
                "===================================================================\n" \
                "************Please select the following options********************\n"
                " *    1. Binary number to signed decimal number conversion.(Lab 2) *\n" \
                " *    2. Binary number to Floating number conversion (Lab 2)       *\n" \
                " *******************************************************************\n" \
                " *    e. To Exit, Type 'e'                                         *\n" \
                " *******************************************************************\n";

int main(void) {
	    char options;  // the option should only be a byte
        char inputs[33] = {0};  // 32-bit string plus a ending indicator.
        do{
            puts(menu); /* prints Memory Simulation */
            fflush(stdin);  // clear the input buffer before getchar.
            options = getchar();
            switch (options)
            {
                case '1': /* lab 2. Convert binary number into a SIGNED decimal
                           number and display */
                    puts("Please input your BINARY number, "\
                            "I will convert it to signed decimal:");
                    scanf("%s", &inputs[0]);  // Input must be a string with 0/1
                    // Finish function convert_binary_to_signed to convert the 8-bit binary inputs to signed decimal number.
                    convert_binary_to_signed(inputs);
                    continue;
                case '2':/* lab 2. Convert 32-bit binary number into a floating
                          *  point number number and display */
                    puts("Please input your 32-bit floating point number " \
                            "in binary, I will convert it to decimal");
                    scanf("%s", &inputs[0]);  // Input must be a string with 0/1
                    // Finish function convert_binary_to_float to convert the 32-bit binary inputs to floating point number.
                    convert_binary_to_float(inputs);
                    continue;
                case 'e':
                    puts("Code finished, exit now");
                    return EXIT_SUCCESS;
                default:
                    puts("Not a valid entry, exit now");
                    continue;
            }
        }while (1);
}

void convert_binary_to_signed(const char *binary) {
    int num = 0; // store decimal value
    int i;
 // check length must be 8 bit
    if (strlen(binary) != 8) {
        printf("Wrong Input\n");
        return;
    }
  // convert binary to decimal
    for (i = 0; i < 8; i++) {
             // check char is 0 or 1
        if (binary[i] != '0' && binary[i] != '1') {
            printf("Wrong Input\n");
            return;
        }
     // convert bit to number
        num = num * 2 + (binary[i] - '0');
    }
 // if first bit is 1 then it is negative (two's complement)
    if (binary[0] == '1') {
        num = num - 256;
    }
  // print result
    printf("%d\n", num);
}

void convert_binary_to_float(const char *binary) {
    int i;
    int sign = 0;// sign bit
    int expo = 0;  // exponent value
    int frg = 0; //fraction part of floating point number(googled it becuse output was not coming correct)
    float value;
    float fracPart = 0.0f;
    int expoVal;
 // check length must be 32 bit
    if (strlen(binary) != 32) {
        printf("Wrong Input\n");
        return;
    }
 // check all chars are 0 or 1
    for (i = 0; i < 32; i++) {
        if (binary[i] != '0' && binary[i] != '1') {
            printf("Wrong Input\n");
            return;
        }
    }
 // get sign bit
    sign = (binary[0] == '1');
 // convert exponent bits (next 8 bits)
    for (i = 1; i <= 8; i++) {
        expo = expo * 2 + (binary[i] - '0');
    }
    // convert mantissa bits (last 23 bits)
    for (i = 9; i < 32; i++) {
        frg = frg * 2 + (binary[i] - '0');
    }

 // if exponent is 0 then no implicit 1
    if (expo == 0) {
        fracPart = 0.0f;
    } else {
        fracPart = 1.0f;
    }
 // add fractional part from mantissa
 for (i = 0; i < 23; i++) {
    int bit = (frg >> (22 - i)) & 1;
    if (bit == 1) {
        fracPart = fracPart + (bit * pow(2, -(i + 1)));

    }
}

  // applied exponent
    value = fracPart;
    expoVal = expo - 127;
 // exponent positive should multiply
    if (expoVal > 0) {
        for (i = 0; i < expoVal; i++) {
            value = value * 2.0f;
        }
        // exponent negative should divide
    } else if (expoVal < 0) {
        for (i = 0; i < (-expoVal); i++) {
            value = value / 2.0f;
        }
    }
// sign is 1 then negative
    if (sign == 1) {
        value = -value;
    }
 // print final float value
    printf("Float: %f\n", value);
}
