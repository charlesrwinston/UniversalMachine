/*
 * testprogram.c
 * A testing file for a Program module
 *
 * Brendan Voelz & Charles Winston
 */

#include <stdio.h>
#include <stdlib.h>
#include "Program.h"
#include "Segments.h"
#include <inttypes.h>
#include <stdbool.h>

void test_init();
void print_ip();
void test_fetch();

int main(int argc, char *argv[])
{
        (void)argc;
        FILE *program = fopen(argv[1], "r");
        initialize_segments(program, 8);
        test_init();
}

void test_init()
{
        printf("****** TEST INIT ******\n");
        initialize_program();
        print_ip();
}

void print_ip()
{
        printf("IP: %d\n", get_ip());
}

void test_fetch()
{
        printf("****** TEST FETCH ******\n");
        for (int i = 0; i < 8; i++) {
                uint32_t instr = fetch();
                printf("Instruction %d: %" PRIu32 "\n", i, instr);
        }
}