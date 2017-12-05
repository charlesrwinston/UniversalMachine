/*
 * umlab.c
 * 
 * The functions defined in this lab should be linked against umlabwrite.c
 * to produce a unit test writing program. Any additional functions and unit
 * tests written for the lab go here.
 */

#include <stdint.h>
#include <stdio.h>

#include <bitpack.h>
#include <assert.h>
#include <seq.h>


typedef uint32_t Um_instruction;
typedef enum Um_opcode {
        CMOV = 0, SLOAD, SSTORE, ADD, MUL, DIV,
        NAND, HALT, MAP, UNMAP, OUT, IN, LOADP, LV
} Um_opcode;

typedef enum Um_register { r0 = 0, r1, r2, r3, r4, r5, r6, r7 } Um_register;

/* Functions that return the two instruction types */
Um_instruction three_register(Um_opcode op, int ra, int rb, int rc);
Um_instruction loadval(unsigned ra, unsigned val);


/* Wrapper functions for each of the instructions */
static inline Um_instruction halt(void) 
{
        return three_register(HALT, 0, 0, 0);
}

static inline Um_instruction add(Um_register a, Um_register b, Um_register c) 
{
        return three_register(ADD, a, b, c);
}

static inline Um_instruction multiply(Um_register a, Um_register b, 
                                      Um_register c) 
{
        return three_register(MUL, a, b, c);
}

static inline Um_instruction divide(Um_register a, Um_register b, 
                                    Um_register c) 
{
        return three_register(DIV, a, b, c);
}

static inline Um_instruction cmov(Um_register a, Um_register b,
                                  Um_register c)
{
        return three_register(CMOV, a, b, c);
}

static inline Um_instruction map(Um_register a, Um_register b,
                                Um_register c)
{
        return three_register(MAP, a, b, c); 
}

static inline Um_instruction sload(Um_register a, Um_register b,
                                Um_register c)
{
        return three_register(SLOAD, a, b, c);
}

static inline Um_instruction sstore(Um_register a, Um_register b,
                                Um_register c)
{
        return three_register(SSTORE, a, b, c);
}

static inline Um_instruction loadp(Um_register a, Um_register b,
                                Um_register c)
{
        return three_register(LOADP, a, b, c);
}

static inline Um_instruction nand(Um_register a, Um_register b,
                                Um_register c)
{
        return three_register(NAND, a, b, c);
}

static inline Um_instruction unmap(Um_register a, Um_register b,
                                Um_register c)
{
        return three_register(UNMAP, a, b, c);
}

static inline Um_instruction input(Um_register c)
{
    return three_register(IN, c, c, c);
}

static inline Um_instruction output(Um_register c)
{
	return three_register(OUT, c, c, c);
}

/* Functions for working with streams */

static inline void emit(Seq_T stream, Um_instruction inst)
{
        assert(sizeof(inst) <= sizeof(uintptr_t));
        Seq_addhi(stream, (void *)(uintptr_t)inst);
}

extern void Um_write_sequence(FILE *output, Seq_T stream)
{
	Um_instruction instr;
	int length = Seq_length(stream);
	for (int i = 0; i < length; i++) {
		instr = (uintptr_t)Seq_remlo(stream);
		for (int j = 3; j >= 0; j--) {
			fputc((Bitpack_getu(instr, 8, 8*j)), output);
        }
	}
}


/* Unit tests for the UM */

void emit_cmov_test(Seq_T stream)
{
        emit(stream, loadval(r0, 5));
        emit(stream, loadval(r1, 8));
        emit(stream, loadval(r2, 12));
        emit(stream, cmov(r0, r1, r2));
        emit(stream, output(r0));

        emit(stream, loadval(r0, 5));
        emit(stream, loadval(r1, 8));
        emit(stream, loadval(r2, 0));
        emit(stream, cmov(r0, r1, r2));
        emit(stream, output(r0));

        emit(stream, halt());
}

void emit_halt_test(Seq_T stream)
{
        emit(stream, halt());
}

void emit_verbose_halt_test(Seq_T stream)
{
        emit(stream, halt());
        emit(stream, loadval(r1, 'B'));
        emit(stream, output(r1));
        emit(stream, loadval(r1, 'a'));
        emit(stream, output(r1));
        emit(stream, loadval(r1, 'd'));
        emit(stream, output(r1));
        emit(stream, loadval(r1, '!'));
        emit(stream, output(r1));
        emit(stream, loadval(r1, '\n'));
        emit(stream, output(r1));
}

void emit_add_test(Seq_T stream)
{
        emit(stream, loadval(r1, 1));
        emit(stream, loadval(r2, 5));
        emit(stream, loadval(r3, 0));
        emit(stream, add(r3, r1, r2));
        emit(stream, output(r3));
        emit(stream, halt());
}

void emit_map_test(Seq_T stream)
{
        emit(stream, loadval(r2, 10));
        emit(stream, map(r0, r1, r2));
        emit(stream, halt());
}

void emit_sload_test(Seq_T stream)
{
        emit(stream, loadval(r2, 10));
        emit(stream, loadval(r5, 3));
        emit(stream, map(r0, r1, r2));
        emit(stream, sload(r4, r1, r5));
        emit(stream, output(r4));
}

void emit_loadp_test(Seq_T stream)
{
        (void) stream;
}

void emit_nand_test(Seq_T stream)
{
        (void) stream;
}

void emit_unmap_test(Seq_T stream)
{
        (void) stream;
}

void emit_sstore_test(Seq_T stream)
{
        emit(stream, loadval(r0, 5));
        emit(stream, loadval(r1, 1));
        emit(stream, loadval(r2, 15));
        emit(stream, map(r0, r1, r2));
        emit(stream, sstore(r1, r0, r2));
}

void emit_mult_test(Seq_T stream)
{
        emit(stream, loadval(r1, 1));
        emit(stream, loadval(r2, 5));
        emit(stream, loadval(r3, 0));
        emit(stream, multiply(r3, r1, r2));
        emit(stream, output(r3));
        emit(stream, halt());

}

void emit_div_test(Seq_T stream)
{
        emit(stream, loadval(r1, 1));
        emit(stream, loadval(r2, 5));
        emit(stream, loadval(r3, 2));
        emit(stream, divide(r3, r1, r2));
        emit(stream, output(r3));
        emit(stream, halt());

}

void emit_input_test(Seq_T stream)
{
        emit(stream, input(r0));
        emit(stream, input(r1));
        emit(stream, input(r2));
        emit(stream, input(r3));
        emit(stream, input(r4));
        emit(stream, output(r0));
        emit(stream, output(r1));
        emit(stream, output(r2));
        emit(stream, output(r3));
        emit(stream, halt());
}

void emit_output_test(Seq_T stream)
{
        emit(stream, loadval(r0, 12));
        emit(stream, output(r0));
        emit(stream, halt());
}


void print6_test(Seq_T stream)
{
        emit(stream, loadval(r0, 0));
        emit(stream, loadval(r1, 48));
        emit(stream, loadval(r2, 6));
        emit(stream, loadval(r3, 7));
        emit(stream, loadval(r4, 99));
        emit(stream, loadval(r5, 255));
        emit(stream, output(r0));
        emit(stream, output(r1));
        emit(stream, output(r2));
        emit(stream, output(r3));
        emit(stream, output(r4));
        emit(stream, output(r5));        
        emit(stream, halt());
}



Um_instruction three_register(Um_opcode op, int ra, int rb, int rc)
{
	uint32_t instr = 0;
	instr = Bitpack_newu(instr, 4, 28, op);
	instr = Bitpack_newu(instr, 3, 6, ra);
	instr = Bitpack_newu(instr, 3, 3, rb);
	instr = Bitpack_newu(instr, 3, 0, rc);
	return (Um_instruction)(instr);
}

Um_instruction loadval(unsigned ra, unsigned val)
{
        uint32_t instr = 0;
	    instr = Bitpack_newu(instr, 4, 28, LV);
	    instr = Bitpack_newu(instr, 3, 25, ra);
	    instr = Bitpack_newu(instr, 25, 0, val);
        return (Um_instruction)(instr);
}
