CC = gcc
CFLAGS = -Wall --std=c99 -g

tree: main.o tree.o graphics.o builder.o
		$(CC) $(CFLAGS) -o $@ $^ -lm

main.o: main.c tree.h graphics.h builder.h
		$(CC) $(CFLAGS) -c -o $@ $<

tree.o: tree.c tree.h
		$(CC) $(CFLAGS) -c -o $@ $<

graphics.o: graphics.c graphics.h
		$(CC) $(CFLAGS) -c -o $@ $<

builder.o: builder.c builder.h graphics.h tree.h
		$(CC) $(CFLAGS) -c -o $@ $<

clean:
		rm -f *.o *~ draw