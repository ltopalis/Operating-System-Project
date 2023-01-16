CC = gcc
LDFLAGS = -lm
CFLAGS=-Wall -O3 -pthread

all: scheduler

objectFiles:
	@$(CC) $(CFLAGS) -c *.c

scheduler: FCFS.o structures.o SJF.o RR.o PRIO.o scheduler.o
	@$(CC) $(CFLAGS) -o scheduler *.o
	@rm -f *.o

clean:
	rm -f scheduler -rf output
