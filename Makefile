CC=gcc
CFLAGS=-c -Wall
SOURCES=main.c utils.c
OBJ=main.o utils.o
HFILES=shell.h
EXEC=main

all: main

main: $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

%.o: %.c $(HFILES)
	$(CC) $(CFLAGS) $<

clean:
	rm -rf *.o main