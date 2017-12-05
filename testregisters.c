/*
 * testregisters.c
 * A testing file for a Registers module
 *
 * Brendan Voelz & Charles Winston
 */

#include <stdio.h>
#include <stdlib.h>
#include "Registers.h"
#include <inttypes.h>
#include <stdbool.h>

void test_init();
void test_set_value();
void print_registers();


int main(int argc, char *argv[])
{
        (void)argc;
        FILE *program = fopen(argv[1], "r");
        test_init(program);
        test_set_value();
        return 0;

}

/* Expected output: 0, 2, 4, 8 ... */
void test_set_value()
{
        printf("****** TEST SET VALUE ******\n");
        for (int i = 0; i < 8; i++) {
                set_value(i, i * 2);
        }
        print_registers();
}

void test_init()
{
        printf("****** TEST INIT ******\n");
        initialize_registers();
        print_registers();

}

/* Functions as a test for get_value */
void print_registers()
{
        for (int i = 0; i < 8; i++) {
                printf("Register %d: %" PRIu32 "\n", i, get_value(i));
        }
        printf("\n");
}
















