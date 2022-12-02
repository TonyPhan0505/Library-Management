CC = gcc
CFLAGS = -Wall -std=c99 -ggdb

all: processing sorting

processing: ex13q1.o ex13q11.o ex13q12.o ex13q13.o ex13q14.o ex13q15.o ex13q2.o helpers.o
	$(CC) $(CFLAGS) $^ -o $@

sorting: ex13q1.o ex13q11.o ex13q12.o ex13q13.o ex13q14.o ex13q15.o ex13q2.o helpers.o
	$(CC) $(CFLAGS) $^ -o $@

ex13q1.o: ex13q1.c lab13.h
ex13q11.o: ex13q11.c lab13.h
ex13q12.o: ex13q12.c lab13.h
ex13q13.o: ex13q13.c lab13.h
ex13q14.o: ex13q14.c lab13.h
ex13q15.o: ex13q15.c lab13.h
ex13q2.o: ex13q2.c lab13.h
helpers.o: helpers.c lab13.h

clean:
	rm -f ex13q1.o ex13q11.o ex13q12.o ex13q13.o ex13q14.o ex13q15.o helpers.o ex13q2.o processing processing.csv sorting gamesales_name.csv gamesales_NA_sales.csv gamesales_EU_sales.csv gamesales_JP_sales.csv gamesales_global_sales.csv gamesales_year.csv gamesales_platform.csv gamesales_genre.csv gamesales_publisher.csv core CORE a.out