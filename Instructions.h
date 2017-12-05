#ifndef INSTR
#define INSTR 

/*
 * Instuctions.h
 * An interface for the Instructions module
 *
 * Brendan Voelz & Charles Winston
 */

#include <stdio.h>
#include <stdlib.h>
#include "Constants.h"
#include <inttypes.h>
#include <stdbool.h>

/* Executes an instruction */
void execute(uint32_t instruction);

#endif