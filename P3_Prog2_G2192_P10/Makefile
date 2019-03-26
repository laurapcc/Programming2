########################################################
CC=gcc
CFLAGS= -g -Wall -ansi -pedantic
EJS = p3_testqueue p3_e1
########################################################
OBJECTSP3TEST = p3_testqueue.o node.o queue.o
OBJECTSP3E1 = p3_e1.o node.o queue.o graph.o
########################################################

all: $(EJS) clean

p3_testqueue: $(OBJECTSP3TEST)
	$(CC) $(CFLAGS) -o p3_testqueue $(OBJECTSP3TEST)

p3_e1: $(OBJECTSP3E1)
	$(CC) $(CFLAGS) -o p3_e1 $(OBJECTSP3E1)


p3_testqueue.o: p3_testqueue.c queue.h node.h types.h
	$(CC) $(CFLAGS) -c p3_testqueue.c

p3_e1.o: p3_e1.c graph.h queue.h node.h types.h
	$(CC) $(CFLAGS) -c p3_e1.c


node.o: node.c node.h types.h
	$(CC) $(CFLAGS) -c node.c

graph.o: graph.c graph.h queue.h node.h types.h
	$(CC) $(CFLAGS) -c graph.c

queue.o: queue.c queue.h node.h types.h
	$(CC) $(CFLAGS) -c queue.c


clear:
	rm -rf *.o

clean:
	rm -rf *.o $(EJS)


run:
	@echo ">>>>>>Running p3_testqueue"
	./p3_testqueue nodes.txt
	@echo ">>>>>>Running p3_e1"
	./p3_e1 g1.txt 3 1

runv:
	@echo ">>>>>>Running p3_testqueue with valgrind"
	valgrind --leak-check=full ./p3_testqueue nodes.txt
	@echo ">>>>>>Running p3_e1 with valgrind"
	valgrind --leak-check=full ./p3_e1 g1.txt 3 1
