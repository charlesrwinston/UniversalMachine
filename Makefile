#
# Makefile for the UM Test lab
# 
CC = gcc

IFLAGS  = -I/comp/40/include -I/usr/sup/cii40/include/cii
CFLAGS  = -g -std=gnu99 -Wall -Wextra -Werror -pedantic $(IFLAGS)
LDFLAGS = -g -L/comp/40/lib64 -L/usr/sup/cii40/lib64
LDLIBS  = -l40locality -lm -lbitpack -lcii40

EXECS   = writetests

all: $(EXECS)

writetests: umlabwrite.o umlab.o
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

testsegments: testsegments.o Segments.o
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

testinstructions: Instructions.o
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

testregisters: Registers.o testregisters.o
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

testprogram: Program.o Segments.o testprogram.o
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

um: Constants.o Program.o Segments.o Registers.o Instructions.o um.o
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

# To get *any* .o file, compile its .c file with the following rule.
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(EXECS)  *.o

