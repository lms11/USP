CC = cc
CFLAGS = -std=c99 -pedantic -Wall

all: matrix lists

graph.o: graph.c graph.h
	$(CC) $(CFLAGS) -c graph.c

graph_matrix.o: test.c graph_matrix.c graph.h
	$(CC) $(CFLAGS) -c test.c graph_matrix.c

matrix: graph.o graph_matrix.o test.o
	$(CC) test.o graph.o graph_matrix.o -o test_matrix

graph_lists.o: test.c graph_lists.c graph.h
	$(CC) $(CFLAGS) -c test.c graph_lists.c

lists: graph.o graph_lists.o test.o
	$(CC) test.o graph.o graph_lists.o -o test_lists

clean:
	rm -f *.o matrix lists
