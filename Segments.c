/*
 * Segments.c
 * An implementation of a Segments interface
 *
 * Brendan Voelz & Charles Winston
 */
#include "Segments.h"
#include "Constants.h"
#include "stack.h"
#include <bitpack.h>

const unsigned BYTE_WIDTH = 8;
const int MAX_SEQ_SIZE    = 100;


typedef struct Segment {
        uint32_t *words;
        unsigned num_words;
} *Segment;

/* A sequence of memory segments */
Seq_T segments;

/* A stack of available, previously unmapped segment IDs */
Stack_T stack;

static uint32_t get_instruction(FILE *program);
static void Seg_free(Segment *segment);

/* 
 * Initializes the segments sequences and maps segment 0 to contain the program.
 * Initializes the stack of segment IDs. Is initially empty.
 */
extern void initialize_segments(FILE *program, unsigned num_words)
{
        /* UM's memory segments */
        segments = Seq_new(MAX_SEQ_SIZE);

        /* Stack of instructions */
        stack    = Stack_new();

        /* Load program into segment zero */
        uint32_t *words = (uint32_t *)malloc(sizeof(uint32_t) * num_words);
        // printf("%lx\n", (unsigned long) words );
        for (unsigned i = 0; i < num_words; i++) {
                uint32_t instr = get_instruction(program);
                words[i]       = instr;
        }

        /* Create segment */
        Segment segment    = (Segment)malloc(sizeof(struct Segment));
        segment->words     = words;
        segment->num_words = num_words;

        /* Add segment zero to segments */
        Seq_addhi(segments, segment);
}

/*
 * get_instruction
 * Returns the next instruction from a UM program file
 */
static uint32_t get_instruction(FILE *program)
{
        uint64_t word = 0;

        word = Bitpack_newu(word, BYTE_WIDTH, 24, getc(program));
        word = Bitpack_newu(word, BYTE_WIDTH, 16, getc(program));
        word = Bitpack_newu(word, BYTE_WIDTH, 8, getc(program));
        word = Bitpack_newu(word, BYTE_WIDTH, 0, getc(program));

        return word;
}

/*
 * map
 * Maps a new segment of size num_words into the segments sequence. If the stack
 * is not empty, then the top element of the stack will be the segment ID. If
 * stack is empty, the ID will be the next available unused integer. The
 * returns the new ID.
 */
extern uint32_t map(unsigned num_words)
{
        uint32_t id;

        /* Initialize segment words to zero */
        uint32_t *words = (uint32_t *)malloc(sizeof(uint32_t) * num_words);
        for (unsigned i = 0; i < num_words; i++) {
                words[i] = 0;
        }

        /* Create segment */
        Segment segment = (Segment)malloc(sizeof(Segment));
        segment->words = words;
        segment->num_words = num_words;

        /* Check if stack has open ID */
        if (Stack_empty(stack) != 1) {
                id = (uintptr_t)Stack_pop(stack);
                Seq_put(segments, id, segment);
        } else {
                id = Seq_length(segments);
                Seq_addhi(segments, segment);
        }

        return id;
}

/*
 * Unmaps the previously mapped segment with the given ID. The ID is pushed onto
 * the stack to be used again for future mapping. Returns true if successfully
 * unmapped.
 */
extern void unmap(uint32_t id)
{
        Segment segment = Seq_get(segments, id);
        Seg_free(&segment);
        Seq_put(segments, id, NULL);
        Stack_push(stack, (void *)(uintptr_t)id);
}

/*
 * Returns the value at the id'th segment with the given offset.
 */
extern uint32_t load(uint32_t id, uint32_t offset)
{
        Segment segment = Seq_get(segments, id);
        return segment->words[offset];
}

/*
 * Stores the given value at the id'th segment in the given offset. Returns true
 * if successfully stored.
 */
extern void store(uint32_t id, uint32_t offset, uint32_t value)
{
        Segment segment = Seq_get(segments, id);
        segment->words[offset] = value;
}

/*
 * Duplicates segment id1 and replaces segment id2 with the duplicated segment
 */
extern void duplicate_segment(uint32_t id1, uint32_t id2)
{
        Segment segment_1 = Seq_get(segments, id1);
        Segment segment_2 = Seq_get(segments, id2);

        Seg_free(&segment_2);

        /* Duplicate array of words */
        uint32_t *words = (uint32_t *)malloc(sizeof(uint32_t) * segment_1->num_words);
        for (unsigned i = 0; i < segment_1->num_words; i++) {
                words[i] = segment_1->words[i];
        }

        /* Create new duplicate segment */
        segment_2            = (Segment)malloc(sizeof(Segment));
        segment_2->words     = words;
        segment_2->num_words = segment_1->num_words;

        Seq_put(segments, id2, segment_2);
}

/*
 * Frees all segments and the segment sequence.
 */
extern void free_memory()
{
        Segment segment = NULL;
        for (int i = 0; i < Seq_length(segments); i++) {
                segment = (Segment)Seq_get(segments, i);
                if (segment != NULL) {
                        Seg_free(&segment);
                        Seq_put(segments, i, NULL);
                }
        }
        Seq_free(&segments);
        Stack_free(&stack);
}

/*
 * Used for testing purposes. Prints the segments.
 */
extern void print_segments()
{
        for (int i = 0; i < Seq_length(segments); i++) {
                Segment segment = (Segment)Seq_get(segments, i);
                if (segment != NULL) {
                        printf("SEGMENT %d:\n", i);
                        for (unsigned j = 0; j < segment->num_words; j++) {
                                printf("word %d: %" PRIu32 "\n", j, segment->words[j]);
                        }
                }
        }
}

/*
 * Frees memory allocated for a segment struct.
 */
static void Seg_free(Segment *segment)
{
        free((*segment)->words);
        free(*segment);
}



