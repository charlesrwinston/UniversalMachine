/*
 * Registers.c
 * An implementation of a Registers interface
 *
 * Brendan Voelz & Charles Winston
 */

#include "Registers.h"
#include "Constants.h"

const int NUM_REGISTERS   = 8;

uint32_t registers[8];

/*
 * initialize_registers
 * Initializes the values in the registers
 */
extern void initialize_registers()
{
        for (int i = 0; i < 8; i++) {
                registers[i] = 0;
        }
}

/*
 * get_value
 * Returns the value given a register index
 */
extern uint32_t get_value(int reg)
{
        if (reg < 0 || reg >= 8) {
                fprintf(stderr, "Invalid register indexing\n");
                exit(EXIT_FAILURE);
        } else {
                return registers[reg];
        }
}

/*
 * set_value
 * Sets the value at a register given a register index and a value
 */
extern void set_value(int reg, uint32_t value)
{
        if (reg < 0 || reg >= 8) {
                fprintf(stderr, "Invalid register indexing\n");
                exit(EXIT_FAILURE);
        } else {
                registers[reg] = value;
        }
}