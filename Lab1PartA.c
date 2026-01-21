/****************************************************
 Name:        Yashika Bhatt
 Student ID:  N01661425
 Lab 1 - Data Sizes of x86 Architecture
 ****************************************************/

#include <stdio.h>

/* Struct definition MUST be before use */
struct Account {
    unsigned int account_number;
    char account_type;
    char *last_name;
    char *first_name;
    float balance;
    char reserved[6];
};

void displaySizes()
{
    /* Basic data types */
    char ant;
    short bear;
    int cat;
    long dog;
    float eagle;
    double fox;

    /* Pointer data types */
    int *iguana;
    long *jaguar;
    float *koala;
    double *lion;

    /* Struct and pointer */
    struct Account monkey;
    struct Account *newt;

    printf("char ant = %zu bytes\n", sizeof(ant));
    printf("short bear = %zu bytes\n", sizeof(bear));
    printf("int cat = %zu bytes\n", sizeof(cat));
    printf("long dog = %zu bytes\n", sizeof(dog));
    printf("float eagle = %zu bytes\n", sizeof(eagle));
    printf("double fox = %zu bytes\n\n", sizeof(fox));

    printf("int *iguana = %zu bytes\n", sizeof(iguana));
    printf("long *jaguar = %zu bytes\n", sizeof(jaguar));
    printf("float *koala = %zu bytes\n", sizeof(koala));
    printf("double *lion = %zu bytes\n\n", sizeof(lion));

    printf("struct Account monkey = %zu bytes\n", sizeof(monkey));
    printf("struct Account *newt = %zu bytes\n", sizeof(newt));
}

int main()
{
    displaySizes();
    return 0;
}
