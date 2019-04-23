########################################################
CC=gcc
CFLAGS= -g -Wall -ansi -pedantic
EJS = p4_e1 p4_e2 p4_e3 p4_e4
########################################################
OBJECTSP4E1 = p4_e1.o tree.o
OBJECTSP4E2 = p4_e2.o #list.o integer.o
OBJECTSP4E3 = p4_e3.o #queuel.o list.o node.o
########################################################

all: $(EJS) clean

p4_e1: $(OBJECTSP4E1)
	$(CC) $(CFLAGS) -o p4_e1 $(OBJECTSP4E1)

p4_e2: $(OBJECTSP4E2)
	$(CC) $(CFLAGS) -o p4_e2 $(OBJECTSP4E2)

p4_e3: $(OBJECTSP4E3)
	$(CC) $(CFLAGS) -o p4_e3 $(OBJECTSP4E3)


p4_e1.o: p4_e1.c tree.h types.h
	$(CC) $(CFLAGS) -c p4_e1.c

p4_e2.o: p4_e2.c #list.h integer.h types.h
	$(CC) $(CFLAGS) -c p4_e2.c

p4_e3.o: p4_e3.c #queue.h node.h types.h
	$(CC) $(CFLAGS) -c p4_e3.c



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

tree.o: tree.c tree.h types.h
	$(CC) $(CFLAGS) -c tree.c


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
