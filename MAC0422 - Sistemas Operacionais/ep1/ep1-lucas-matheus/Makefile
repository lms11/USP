CFLAGS = -O0 -ansi -lreadline

all: ep1sh ep1

ep1: fcfs.o srtn.o multiple_queues.o process.o input.o queue.o heap.o ep1.c

fcfs.o: fcfs.c fcfs.h

srtn.o: srtn.c srtn.h

multiple_queues.o: multiple_queues.c multiple_queues.h

ep1sh: ep1sh.c

input.o: input.c input.h

process.o: process.c process.h

heap.o: heap.c heap.h

queue.o: queue.c queue.h

zip: *.c *.h Makefile ep1sh ep1
	zip ep1.zip $^

clear:
	rm -f *.o
	rm ep1sh ep1
