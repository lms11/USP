CC = cc
CFLAGS = -std=c99 -pedantic -Wall

all: matrix lists

graph.o: graph.c graph.h
	$(CC) $(CFLAGS) -c graph.c

graph_builder.o: graph_builder.c graph_builder.h
	$(CC) $(CFLAGS) -c graph_builder.c

graph_matrix.o: test.c graph_matrix.c graph.h
	$(CC) $(CFLAGS) -c test.c graph_matrix.c

matrix: graph.o graph_matrix.o test.o
	$(CC) test.o graph.o graph_matrix.o -o test_matrix

graph_lists.o: test.c graph_lists.c graph.h
	$(CC) $(CFLAGS) -c test.c graph_lists.c

lists: graph.o graph_lists.o test.o
	$(CC) test.o graph.o graph_lists.o -o test_lists

test_rand1.o: test_rand1.c graph_builder.h graph.h
	$(CC) $(CFLAGS) -c test_rand1.c graph.c

test_rand1: graph.o graph_builder.o test_rand1.o graph_matrix.o
	$(CC) graph.o test_rand1.o graph_builder.o graph_matrix.o -o test_rand1

test_rand2.o: test_rand2.c graph_builder.h graph.h
	$(CC) $(CFLAGS) -c test_rand2.c graph.c

test_rand2: graph.o graph_builder.o test_rand2.o graph_matrix.o
	$(CC) graph.o test_rand2.o graph_builder.o graph_matrix.o -o test_rand2

clean:
	rm -f *.o matrix lists test_matrix test_lists test_rand1 test_rand2
