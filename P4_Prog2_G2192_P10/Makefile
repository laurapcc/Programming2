########################################################
CC=gcc
CFLAGS= -g -Wall -ansi -pedantic
EJS = p3_testqueue p3_e1 p3_e2 p3_testqueuel
########################################################
OBJECTSP3TEST = p3_testqueue.o node.o queue.o
OBJECTSP3E1 = p3_e1.o node.o queue.o graph.o
OBJECTSP3E2 = p3_e2.o list.o integer.o
OBJECTSP3TESTL = p3_testqueuel.o queuel.o list.o node.o
########################################################

all: $(EJS) clean

p3_testqueue: $(OBJECTSP3TEST)
	$(CC) $(CFLAGS) -o p3_testqueue $(OBJECTSP3TEST)

p3_e1: $(OBJECTSP3E1)
	$(CC) $(CFLAGS) -o p3_e1 $(OBJECTSP3E1)

p3_e2: $(OBJECTSP3E2)
	$(CC) $(CFLAGS) -o p3_e2 $(OBJECTSP3E2)

p3_testqueuel: $(OBJECTSP3TESTL)
	$(CC) $(CFLAGS) -o p3_testqueuel $(OBJECTSP3TESTL)

p3_testqueuel.o: p3_testqueuel.c queuel.h list.h node.h types.h
	$(CC) $(CFLAGS) -c p3_testqueuel.c

p3_e2.o: p3_e2.c list.h integer.h types.h
	$(CC) $(CFLAGS) -c p3_e2.c

p3_testqueue.o: p3_testqueue.c queue.h node.h types.h
	$(CC) $(CFLAGS) -c p3_testqueue.c

p3_e1.o: p3_e1.c graph.h queue.h node.h types.h
	$(CC) $(CFLAGS) -c p3_e1.c


integer.o: integer.c integer.h types.h
	$(CC) $(CFLAGS) -c integer.c

node.o: node.c node.h types.h
	$(CC) $(CFLAGS) -c node.c

graph.o: graph.c graph.h queue.h node.h types.h
	$(CC) $(CFLAGS) -c graph.c

queue.o: queue.c queue.h types.h
	$(CC) $(CFLAGS) -c queue.c

list.o: list.c list.h integer.h types.h
	$(CC) $(CFLAGS) -c list.c

queuel.o: queuel.c queuel.h list.h types.h
	$(CC) $(CFLAGS) -c queuel.c


clear:
	rm -rf *.o

clean:
	rm -rf *.o $(EJS)

run:
	@echo ">>>>>>Running p3_testqueue"
	./p3_testqueue nodes.txt
	@echo ">>>>>>Running p3_e1"
	./p3_e1 g1.txt 3 1
	@echo ">>>>>>Running p3_e2"
	./p3_e2 8
	@echo ">>>>>>Running p3_testqueuel"
	./p3_testqueuel nodes.txt

runv:
	@echo ">>>>>>Running p3_testqueue with valgrind"
	valgrind --leak-check=full ./p3_testqueue nodes.txt
	@echo ">>>>>>Running p3_e1 with valgrind"
	valgrind --leak-check=full ./p3_e1 g1.txt 3 1
	@echo ">>>>>>Running p3_e2 with valgrind"
	valgrind --leak-check=full ./p3_e2 8
	@echo ">>>>>>Running p3_testqueuel with valgrind"
	valgrind --leak-check=full ./p3_testqueuel nodes.txt
