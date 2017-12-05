/* Test segments */

#include <stdio.h>
#include <stdlib.h>
#include "Segments.h"
#include <inttypes.h>
#include <stdbool.h>


static const uint32_t MAX = 0xffffffff;


void test_unmap(uint32_t mapped_ids[])
{
        for (uint32_t i = 0; i < 10; i++) {
                unmap(mapped_ids[i]);
        }
        print_segments();
}

void test_load(uint32_t mapped_ids[])
{
        for (uint32_t i = 0; i < 10; i++) {
                uint32_t num_words = mapped_ids[i];
                for (uint32_t offset = 0; offset < num_words; offset++) {
                        printf("%" PRIu32 "\n", load(mapped_ids[i], offset));
                }
        }
        print_segments();
}

void test_store(uint32_t mapped_ids[])
{
        for (uint32_t i = 0; i < 10; i++) {
                uint32_t num_words = mapped_ids[i];
                for (uint32_t offset = 0; offset < num_words; offset++) {
                        for (uint32_t val = 0; val < num_words; val++) {
                                store(mapped_ids[i], offset, val);
                        }
                }
        }
        print_segments();
}

/*
 * The segment with segment ID mapped_ids[i] will have i words.
 */
void test_map(uint32_t mapped_ids[])
{
        for (uint32_t num_words = 0; num_words < 10; num_words++) {
                mapped_ids[num_words] = map(num_words);
        }
        print_segments();
}

/*
 * Tests initilize_segments().
 */
void test_init(FILE *program)
{
        initialize_segments(program, 50);
        print_segments();
}

int main(int argc, char *argv[])
{
        (void) argc;
        /* Pass in UM program as command line argument */
        FILE *program = fopen(argv[1], "r");
        test_init(program);
        (void) program;

        uint32_t mapped_ids[MAX];

        test_map(mapped_ids);
        test_store(mapped_ids);
        test_load(mapped_ids);
        test_unmap(mapped_ids);
}

