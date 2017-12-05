#ifndef PROG
#define PROG

/*
 * Program.h
 * An interface for a Program module
 *
 * Brendan Voelz & Charles Winston
 */

#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#include "Constants.h"

/*
 * fetch
 * Fetches and returns the next word in segment zero
 */
extern uint32_t fetch();

/*
 * initialize_program
 * Initializes the instruction pointer variable in the Program module
 */
extern void initialize_program();

/*
 * get_ip
 * Returns the instruction pointer value
 */
extern unsigned get_ip();

/*
 * move_prgmcount
 * Assigns the program counter to the value i
 */
extern void move_prgmcount(unsigned i);

#endif