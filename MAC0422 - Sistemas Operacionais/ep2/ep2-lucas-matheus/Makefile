CFLAGS = -O0 -ansi -pthread -lm -std=gnu99 -g

all: ep2

ep2: cyclist.o speedway.o team.o main.c
	$(CC) $^ -o $@ $(CFLAGS)

cyclist.o: cyclist.h cyclist.c

speedway.o: speedway.h speedway.c

team.o: team.h team.c

zip: *.c *.h *.pdf Makefile
	tar cvfz ep2-lucas-matheus.tar.gz $^

clear:
	rm -f *.zip
	rm -f *.tar.gz
	rm -f *.o
	rm ep2
