#ifndef CONST
#define CONST

#include <inttypes.h>

/*
 * Constants.h
 * An interface of constant variables used for the UM
 *
 * Brendan Voelz & Charles Winston
 */
extern const int      MAX_SEQ_SIZE;
extern const unsigned BYTE_WIDTH;
extern const int      NUM_REGISTERS;


extern const unsigned CMOV;
extern const unsigned SLOAD;
extern const unsigned SSTORE;
extern const unsigned ADD;
extern const unsigned MUL;
extern const unsigned DIV;
extern const unsigned NAND;
extern const unsigned HALT;
extern const unsigned MAP;
extern const unsigned UNMAP;
extern const unsigned OUT;
extern const unsigned IN;
extern const unsigned LOADP;
extern const unsigned LV;


extern const unsigned OPCODE_WIDTH;
extern const unsigned VAL_WIDTH;
extern const unsigned REG_WIDTH;
extern const unsigned OPCODE_LSB;
extern const unsigned VAL_LSB;
extern const unsigned A_LSB;
extern const unsigned B_LSB;
extern const unsigned C_LSB;
extern const unsigned LVREG_LSB;

extern const uint32_t SENTINEL;

#endif