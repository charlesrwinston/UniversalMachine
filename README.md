********************************************************************************
* Charles Winston & Brendan Voelz 
* Design for a Universal Machine   
* COMP-0040                        
* HW6                              
********************************************************************************

* Components and their Interfaces
        Registers
                The registers are used to perform the UM instructions, and are
                stored in an array of size 8 holding uint32_t's as elements.
                
                The interface for this module consists of the following
                functions:
                        /* Returns the value at a given register */
                        uint32_t get_value(int register_index);

                        /* Sets the value at a designated register */
                        void     set_value(uint32_t value);

        Memory
                The UM's memory management will be handled by our MemoryManager
                component, which keeps track of all of the segments used by
                the UM. The UM's memory will be represented by a Hanson sequence
                of segments. We will represent a segment as an array of uint32_t
                elements, which translate to UM instructions.

                It is worthwhile to document that the UM words will be
                represented by uint32_t because of the format for a word:
                ________________________________________________________
               | op_code |                               | r1 | r2 | r3 |
                --------------------------------------------------------
                  4 bits                                   3 bits each

                The interface for the Memory module consists of the following
                functions:
                        /* Returns value at segment with offset */
                        uint32_t load(uint32_t segment_id, uint32_t offset);

                        /* Returns true if stores successfully */
                        bool     store(uint32_t segment_id, uint32_t offset,
                                       uint32_t value);

                        /* Returns ID of newly mapped segment */
                        uint32_t map(int num_words);

                        /* Returns true if segment freed successfully, false
                           if segment not yet mapped */
                        bool     unmap(uint32_t segment_id);

                Included in this module will be a stack that will hold freed
                segment IDs that are currently available for mapping. So, when
                unmap is called, the segment ID goes onto this stack. Similarly,
                when map is called, if the stack is not empty the program will
                use an ID from the stack before creating a new segment.

                Invariants
                        Our UM's Memory interface, which manages the use of
                        segments in the UM, holds one key invariant that is
                        essential to the functionality of the module. That is,
                        if a segment is created and then freed, the UM will use
                        the segment ID of the recently-freed segment when it
                        goes to map a new segment before generating a new
                        segment ID. This invariant ensures that created segments
                        are not wasted memory after being freed (unmapped).

        IO
                The UM's input/output functionality is handled by our IO
                module, which is responsible for reading input and printing
                output. Our representation will ensure that inputting or
                outputting a value < 0 or > 255 will result in a checked
                runtime error.

                The interface for this module consists of the following
                functions:
                        /* Reads input into designated register */
                        uint32_t input();

                        /* Prints value */
                        void     output(uint32_t value);

        Program
                The UM's flow of instruction calling is managed by our
                Program module, which keeps track of all of the UM program's
                instructions.

                The interface for this module consists of the following
                functions:
                        /* Returns the next word in segment 0. Returns a
                           uint32_t of all 1's if no more instructions to
                           read */
                        uint32_t fetch();

        Instructions
                The Instructions module is responsible for decoding words into
                instructions and then executing them as functions.

                The interface for this module consists of the following
                functions:
                        /* Executes an instruction */
                        void     execute(uint32_t instruction);

                This module will have internal static functions that help
                decode the instructions fetched by the Program module, but
                these will be abstracted from the client.

* Architecture
        The architecture of our UM consists of interactions between our
        modules. The UM operates on a continuous loop of fetching and executing
        instructions. Once an instruction has been fetched by the Program
        module, the UM executes the instruction using the Instructions module.
        The Instructions module is responsible for decoding a word and calling
        the appropriate instruction function. Depending on the instruction,
        Instruction may use the IO, Registers, and/or Memory module(s) to
        carry out the desired instruction. This process of fetch, decode,
        execute continues while there are remaining instructions to handle,
        and once there are no more instructions the UM will free its memory
        and stop running.

* Testing
        Since the UM is composed of several different modules, which each
        perform specialized tasks, our testing plan will first consist of unit
        tests on each of the methods in each module. Then, we will look to test
        multiple modules interacting at once to test the functionality of the
        UM at a larger scope.

        Registers
                - Ensure that get_value returns the correct value in the
                  designated register
                - Ensure that set_value correctly sets the value in the
                  designated register
                - Input of values less than 0 or greater than 255 (program
                  may fail)

        Memory
                *** See file testsegments.c ***

        IO
                - Ensure that the input function reads in from stdin and
                  not anywhere else.
                        - Ensure that input reads one byte at a time
                - Ensure that the output function properly prints to stdout
                - Value passed to output function is less than 0 or greater
                  than 255 (program may fail)

        Program
                - Fetching the next instruction
                - Fetching an invalid instruction
                - Ensure proper behavior when fetch is called and there are no
                  more instructions to read in
                - Fetching from an empty file

        Instruction
                - Decoding all 14 instructions
                - Decoding invalid instructions
                - Executing an invalid instruction
                - Executing an instruction with invalid parameters
                - Executing an 'empty' instruction
********************************************************************************