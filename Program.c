/*
 * Program.c
 * An implementation of a Program module
 *
 * Brendan Voelz & Charles Winston
 */

#include "Program.h"
#include "Segments.h"

/*
 * The program counter / instruction pointer
 */
unsigned ip;

/*
 * initialize_program
 * Initializes the instruction pointer variable in the Program module
 */
extern void initialize_program()
{
        ip = 0;
}

/*
 * fetch
 * Fetches and returns the next word in segment zero
 */
extern uint32_t fetch()
{
        uint32_t instr = load(0, ip);
        /* if (instr == SENTINEL) {
                fprintf(stderr, "Error: invalid instruction\n");
                exit(EXIT_FAILURE);
        } */
        ip++;
        return instr;
}

/*
 * get_ip
 * Returns the instruction pointer value
 */
extern unsigned get_ip()
{
        return ip;
}

/*
 * move_prgmcount
 * Assigns the program counter to the value i
 */
extern void move_prgmcount(unsigned i)
{
        ip = i;
}