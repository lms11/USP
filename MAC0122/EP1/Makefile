cc = gcc
CFLAGS = -Wall --std=c99 -g

draw: main.o graphics.o stack.o processor.o
		$(CC) $(CFLAGS) -o $@ $^ -lm

main.o: main.c graphics.h
		$(CC) $(CFLAGS) -c -o $@ $<

graphics.o: graphics.c graphics.h processor.h
		$(CC) $(CFLAGS) -c -o $@ $<

processor.o: processor.c processor.h graphics.h stack.h
		$(CC) $(CFLAGS) -c -o $@ $<

stack.o: stack.c stack.h
		$(CC) $(CFLAGS) -c -o $@ $<

clean:
		rm -f *.o *~ draw