/*
 * um.c
 * Main program for the Universal Machine
 *
 * Brendan Voelz & Charles Winston
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Instructions.h"
#include "Segments.h"
#include "Registers.h"
#include "Program.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

static FILE *check_args(int argc, char *argv[]);
static void initialize(FILE *fp, const char *filename);
static void run();

/*
 * main
 * Driver program for the UM
 */
int main(int argc, char *argv[])
{
        // Step 1: Validate arguments
        FILE *fp = check_args(argc, argv);

        // Step 2: Initialize the UM given a .um file
        initialize(fp, argv[1]);

        // Step 3: Fetch, decode, execute...
        run();

        exit(EXIT_SUCCESS);
}

/*
 * check_args
 * Validates command line arguments and returns an opened file pointer
 * on success
 */
static FILE *check_args(int argc, char *argv[])
{
        if (argc != 2) {
                fprintf(stderr, "Invalid number of arguments\n");
                exit(EXIT_FAILURE);
        }
        FILE *fp = fopen(argv[1], "r");
        if (fp == NULL) {
                fprintf(stderr, "Invalid file\n");
                exit(EXIT_FAILURE);
        }
        return fp;
}

/*
 * initialize
 * Initializes modules of the UM
 */
static void initialize(FILE *fp, const char *filename)
{
        // Get num words
        struct stat stats;
        if (stat(filename, &stats) != 0) {
                fprintf(stderr, "Invalid file\n");
        }
        unsigned num_words = stats.st_size / 4;

        initialize_segments(fp, num_words);
        initialize_registers();
        initialize_program();

        fclose(fp);
}

/*
 * run
 * Initiates the fetch, decode, execute loop for the UM
 */
static void run()
{
        bool running         = true;
        uint32_t instruction = 0;
        while (running) {
                instruction = fetch();
                execute(instruction);   /* Decode */
        }
}





















