########################################################
CC=gcc
CFLAGS= -g -Wall -ansi -pedantic
EJS = p3_e1
########################################################
OBJECTSP3E1 = p3_e1.o node.o queue.o
########################################################

all: $(EJS) clean

p3_e1: $(OBJECTSP3E1)
	$(CC) $(CFLAGS) -o p3_e1 $(OBJECTSP3E1)

p3_e1.o: p3_e1.c queue.h node.h types.h
	$(CC) $(CFLAGS) -c p3_e1.c

node.o: node.c node.h types.h
	$(CC) $(CFLAGS) -c node.c

queue.o: queue.c queue.h node.h types.h
	$(CC) $(CFLAGS) -c queue.c

clear:
	rm -rf *.o

clean:
	rm -rf *.o $(EJS)

run:
	@echo ">>>>>>Running p3_e1"
	./p3_e1 nodes.txt


runv:
	@echo ">>>>>>Running p3_e1 with valgrind"
	valgrind --leak-check=full ./p3_e1 nodes.txt
