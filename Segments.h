#ifndef SEG
#define SEG

/* 
 * Segments.h
 * An interface for a Segments module
 *
 * Brendan Voelz & Charles Winston
 */

#include <stdio.h>
#include <stdlib.h>
#include <seq.h>
#include <stack.h>
#include <inttypes.h>
#include <stdbool.h>

/* 
 * Initializes the segments sequences and maps segment 0 to contain the program.
 * Initializes the stack of segment IDs. Is initially empty.
 */
extern void initialize_segments(FILE *program, unsigned num_words);

/*
 * Returns the value at the id'th segment with the given offset.
 */
extern uint32_t load(uint32_t id, uint32_t offset);

/*
 * Stores the given value at the id'th segment in the given offset. Returns true
 * if successfully stored.
 */
extern void store(uint32_t id, uint32_t offset, uint32_t value);

/*
 * Maps a new segment of size num_words into the segments sequence. If the stack
 * is not empty, then the top element of the stack will be the segment ID. If
 * stack is empty, the ID will be the next available unused integer. The
 * returns the new ID.
 */
extern uint32_t map(unsigned num_words);

/*
 * Unmaps the previously mapped segment with the given ID. The ID is pushed onto
 * the stack to be used again for future mapping. Returns true if successfully
 * unmapped.
 */
extern void unmap(uint32_t id);

/*
 * Duplicates segment id1 and replaces segment id2 with the duplicated segment
 */
extern void duplicate_segment(uint32_t id1, uint32_t id2);

/*
 * Frees all segments and the segment sequence.
 */
extern void free_memory();


/*
 * Used for testing purposes. Prints the segments.
 */
extern void print_segments();

#endif