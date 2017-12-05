#ifndef REG
#define REG

/*
 * Registers.h
 * An interface for a Registers module
 *
 * Brendan Voelz & Charles Winston
 */

#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>


/*
 * get_value
 * Returns the value given a register index
 */
extern uint32_t get_value(int register_index);

/*
 * set_value
 * Sets the value at a register given a register index and a value
 */
extern void set_value(int reg, uint32_t value);

/*
 * initialize_registers
 * Initializes the values in the registers
 */
extern void initialize_registers();

#endif