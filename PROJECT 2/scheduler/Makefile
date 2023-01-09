CC = gcc
CFLAGS = -Wall
LDFLAGS = -lm

all: scheduler

objectFiles:
	@$(CC) -c *.c

scheduler: FCFS.o structures.o scheduler.o
	@$(CC) -o scheduler *.o
	@rm -f *.o

clean:
	rm -f scheduler
