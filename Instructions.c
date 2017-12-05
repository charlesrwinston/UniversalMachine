/*
 * Instuctions.c
 * Implementation for Instructions.h
 *
 * Brendan Voelz & Charles Winston
 */

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>
#include "Instructions.h"
#include <bitpack.h>
#include "Registers.h"
#include "Segments.h"
#include "Program.h"

const unsigned OPCODE_WIDTH  = 4;
const unsigned VAL_WIDTH     = 25;
const unsigned REG_WIDTH     = 3;
const unsigned OPCODE_LSB    = 28;
const unsigned VAL_LSB       = 0;
const unsigned A_LSB         = 6;
const unsigned B_LSB         = 3;
const unsigned C_LSB         = 0;
const unsigned LVREG_LSB     = 25;

const unsigned CMOV          = 0;
const unsigned SLOAD         = 1;
const unsigned SSTORE        = 2;
const unsigned ADD           = 3;
const unsigned MUL           = 4;
const unsigned DIV           = 5;
const unsigned NAND          = 6;
const unsigned HALT          = 7;
const unsigned MAP           = 8;
const unsigned UNMAP         = 9;
const unsigned OUT           = 10;
const unsigned IN            = 11;
const unsigned LOADP         = 12;
const unsigned LV            = 13;

const uint32_t SENTINEL      = 0xffffffff;

static void comv_(unsigned a, unsigned b, unsigned c);
static void sload_(unsigned a, unsigned b, unsigned c);
static void sstore_(unsigned a, unsigned b, unsigned c);
static void add_(unsigned a, unsigned b, unsigned c);
static void mul_(unsigned a, unsigned b, unsigned c);
static void div_(unsigned a, unsigned b, unsigned c);
static void nand_(unsigned a, unsigned b, unsigned c);
static void halt_(unsigned a, unsigned b, unsigned c);
static void map_(unsigned a, unsigned b, unsigned c);
static void unmap_(unsigned a, unsigned b, unsigned c);
static void out_(unsigned a, unsigned b, unsigned c);
static void in_(unsigned a, unsigned b, unsigned c);
static void loadp_(unsigned a, unsigned b, unsigned c);
static void lv_(unsigned lvreg, unsigned val);

void execute(uint32_t instruction)
{
        unsigned opcode = Bitpack_getu(instruction, OPCODE_WIDTH, OPCODE_LSB);
        unsigned a      = Bitpack_getu(instruction, REG_WIDTH, A_LSB);
        unsigned b      = Bitpack_getu(instruction, REG_WIDTH, B_LSB);
        unsigned c      = Bitpack_getu(instruction, REG_WIDTH, C_LSB);
        unsigned val    = Bitpack_getu(instruction, VAL_WIDTH, VAL_LSB);
        unsigned lvreg  = Bitpack_getu(instruction, REG_WIDTH, LVREG_LSB);

	    //printf("opcode: %u\n", opcode);
        
        switch(opcode) {

        case 0  :
                comv_(a, b, c);
		        break;        
        case 1  :
                sload_(a, b, c);
		        break;
        case 2  :
                sstore_(a, b, c);
		        break;
        case 3  :
                add_(a, b, c);
		        break;
        case 4  :
                mul_(a, b, c);
		        break;
        case 5  :
                div_(a, b, c);
		        break;
        case 6  :
                nand_(a, b, c);
		        break;
        case 7  :
                halt_(a, b, c);
		        break;
        case 8  :
                map_(a, b, c);
		        break;
        case 9  :
                unmap_(a, b, c);
		        break;
        case 10  :
                out_(a, b, c);        
		        break;
        case 11  :
                in_(a, b, c);
		        break;
        case 12  :
                loadp_(a, b, c);
		        break;
        case 13  :
                lv_(lvreg, val);
		        break;
        }
}

/*
 * r
 * Returns the contents of register(i)
 */
static uint32_t r(unsigned i)
{
        return get_value(i);
}


/* 
 * COMV
 * PURPOSE:     Implementation of Conditional Move instruction:
 *              if $r[C] != 0 then $r[A] := $r[B]
 * ARGUMENTS:   Registers a, b, and c
 * RETURNS:     None
 */
static void comv_(unsigned a, unsigned b, unsigned c)
{
        if (r(c) != 0) {
                set_value(a, r(b));
        }
}

/* 
 * SLOAD
 * PURPOSE:     Implementation of Segmented Load instruction:
 *              $r[A] := $m[$r[B]][$r[C]]
 * ARGUMENTS:   Registers a, b, and c
 * RETURNS:     None
 */
static void sload_(unsigned a, unsigned b, unsigned c)
{
        set_value(a, load(r(b), r(c)));
}

/* 
 * SSTORE
 * PURPOSE:     Implementation of Segmented Store instruction:
 *              $m[$r[A]][$r[B]] := $r[C]
 * ARGUMENTS:   Registers a, b, and c
 * RETURNS:     None
 */
static void sstore_(unsigned a, unsigned b, unsigned c)
{
        store(r(a), r(b), r(c));
}

/* 
 * ADD
 * PURPOSE:     Implementation of Add instruction:
 *              $r[A] := ($r[B] + $r[C]) mod 2^32
 * ARGUMENTS:   Registers a, b, and c
 * RETURNS:     None
 */
static void add_(unsigned a, unsigned b, unsigned c)
{
        set_value(a, r(b) + r(c));
}

/* 
 * MUL
 * PURPOSE:     Implementation of Multiply instruction:
 *              $r[A] := ($r[B] × $r[C]) mod 2^32
 * ARGUMENTS:   Registers a, b, and c
 * RETURNS:     None
 */
static void mul_(unsigned a, unsigned b, unsigned c)
{
        set_value(a, r(b) * r(c));
}

/* 
 * DIV
 * PURPOSE:     Implementation of Divide instruction:
 *              $r[A] := ⌊$r[B] / $r[C]⌋
 * ARGUMENTS:   Registers a, b, and c
 * RETURNS:     None
 */
static void div_(unsigned a, unsigned b, unsigned c)
{
        set_value(a, r(b) / r(c));
}

/* 
 * NAND
 * PURPOSE:     Implementation of Bitwise NAND instruction:
 *              $r[A] := ~($r[B] ∧ $r[C])
 * ARGUMENTS:   Registers a, b, and c
 * RETURNS:     None
 */
static void nand_(unsigned a, unsigned b, unsigned c)
{
        set_value(a, ~((uint32_t)r(b) & (uint32_t)r(c)));
}

/* 
 * HALT
 * PURPOSE:     Implementation for name instruction:
 *              Computation Stops
 * ARGUMENTS:   Registers a, b, and c
 * RETURNS:     None
 */
static void halt_(unsigned a, unsigned b, unsigned c)
{
        free_memory();
        exit(0);
        (void) a;
        (void) b;
        (void) c;
}

/* 
 * MAP
 * PURPOSE:     Implementation for Map Segment instruction:
 *              A new segment is created with a number of
 *              words equal to the value in $r[C]. Each word in
 *              the new segment is initialized to 0. A bit pattern
 *              that is not all zeroes and that does not identify
 *              any currently mapped segment is placed in $r[B].
 *              The new segment is mapped as $m[$r[B]].
 * ARGUMENTS:   Registers a, b, and c
 * RETURNS:     None
 */
static void map_(unsigned a, unsigned b, unsigned c)
{
        set_value(b, map(r(c)));
        (void) a;
}

/* 
 * UNMAP:
 * PURPOSE:     Implementation for Unmap Segment instruction:
 *              The segment $m[$r[C]] is unmapped. Future Map
 *              Segment instructions may reuse the
 *              identifier $r[C].
 * ARGUMENTS:   Registers a, b, and c
 * RETURNS:     None
 */
static void unmap_(unsigned a, unsigned b, unsigned c)
{
        unmap(r(c));
        (void) a;
        (void) b;

}

/* 
 * OUT
 * PURPOSE:     Implementation for Output instruction:
 *              The value in $r[C] is displayed on the I/O device
 *              immediately. Only values from 0 to 255 are
 *              allowed.
 * ARGUMENTS:   Registers a, b, and c
 * RETURNS:     None
 */
static void out_(unsigned a, unsigned b, unsigned c)
{
        printf("%" PRIu32 "", r(c));
        (void) a;
        (void) b;
}

/* 
 * IN
 * PURPOSE:     Implementation for Input instruction:
 *              The universal machine waits for input on the
 *              I/O device. When input arrives, $r[C] is loaded
 *              with the input, which must be a value from
 *              0 to 255. If the end of input has been signaled,
 *              then $r[C] is loaded with a full 32-bit word in
 *              which every bit is 1.
 * ARGUMENTS:   Registers a, b, and c
 * RETURNS:     None
 */
static void in_(unsigned a, unsigned b, unsigned c)
{
        uint32_t input = getc(stdin);
        printf("Input is %" PRIu32 "\n", input);
        if (feof(stdin)) {
                printf("End of file\n");
                set_value(c, SENTINEL);
        } else {
                set_value(c, input);
        }
        (void) a;
        (void) b;
}

/* 
 * LOADP
 * PURPOSE:     Implementation for Load Program instruction:
 *              Segment $m[$r[B]] is duplicated, and the
 *              duplicate replaces $m[0], which is abandoned.
 *              The program counter is set to point to
 *              $m[0][$r[C]]. If $r[B] = 0, the load-program
 *              operation simply moves the program counter.
 * ARGUMENTS:   Registers a, b, and c
 * RETURNS:     None
 */
static void loadp_(unsigned a, unsigned b, unsigned c)
{
        /*
         * If r[b] = 0, then we would be duplicating segment 0 and placing that
         * in segment 0. This is redundant and slow, so we simply move the
         * program counter.
         */
        if (r(b) != 0) {
                duplicate_segment(r(b), 0);
        }
        move_prgmcount(r(c));
        (void) a;
}

/* 
 * LV
 * PURPOSE:     Implementation for Load Value instruction:
 *              $r[A] := val
 * ARGUMENTS:   Specified register and value
 * RETURNS:     None
 */
static void lv_(unsigned lvreg, unsigned val)
{
        set_value(lvreg, val);
}















