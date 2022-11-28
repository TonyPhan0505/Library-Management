CC = gcc
CFLAGS = -Wall -std=c99 -ggdb

processing: ex13q1.o ex13q11.o ex13q12.o ex13q13.o ex13q1Helpers.o
	$(CC) $(CFLAGS) $^ -o $@

ex13q1.o: ex13q1.c lab13.h
ex13q11.o: ex13q11.c lab13.h
ex13q12.o: ex13q12.c lab13.h
ex13q13.o: ex13q13.c lab13.h
ex13q1Helpers.o: ex13q1Helpers.c lab13.h

clean:
	rm -f ex13q1.o ex13q11.o ex13q1Helpers.o ex13q2.o core CORE a.out