########################################################
CC=gcc
CFLAGS= -g -Wall -ansi -pedantic
EJS = p4_e1 p4_e2 p4_test-node-tree p4_e3
########################################################
OBJECTSP4E1 = p4_e1.o tree.o integer.o
OBJECTSP4E2 = p4_e2.o tree.o integer.o
OBJECTSP4_TESTN = p4_test-node-tree.o tree.o node.o
OBJECTSP4E3 = p4_e3.o tree.o functions.o node.o
########################################################

all: $(EJS) clean

p4_e1: $(OBJECTSP4E1)
	$(CC) $(CFLAGS) -o p4_e1 $(OBJECTSP4E1)

p4_e2: $(OBJECTSP4E2)
	$(CC) $(CFLAGS) -o p4_e2 $(OBJECTSP4E2)

p4_test-node-tree: $(OBJECTSP4_TESTN)
	$(CC) $(CFLAGS) -o p4_test-node-tree $(OBJECTSP4_TESTN)

p4_e3: $(OBJECTSP4E3)
	$(CC) $(CFLAGS) -o p4_e3 $(OBJECTSP4E3)


p4_e1.o: p4_e1.c tree.h types.h integer.h
	$(CC) $(CFLAGS) -c p4_e1.c

p4_e2.o: p4_e2.c tree.h types.h integer.h
	$(CC) $(CFLAGS) -c p4_e2.c

p4_test-node-tree.o: p4_test-node-tree.c tree.h types.h node.h
	$(CC) $(CFLAGS) -c p4_test-node-tree.c

p4_e3.o: p4_e3.c tree.h functions.h node.h types.h
	$(CC) $(CFLAGS) -c p4_e3.c



integer.o: integer.c integer.h types.h
	$(CC) $(CFLAGS) -c integer.c

node.o: node.c node.h types.h
	$(CC) $(CFLAGS) -c node.c

functions.o: functions.c functions.h types.h
	$(CC) $(CFLAGS) -c functions.c

#graph.o: graph.c graph.h queue.h node.h types.h
#	$(CC) $(CFLAGS) -c graph.c

#queue.o: queue.c queue.h types.h
#	$(CC) $(CFLAGS) -c queue.c

#list.o: list.c list.h integer.h types.h
#	$(CC) $(CFLAGS) -c list.c

#queuel.o: queuel.c queuel.h list.h types.h
#	$(CC) $(CFLAGS) -c queuel.c

tree.o: tree.c tree.h types.h
	$(CC) $(CFLAGS) -c tree.c


clear:
	rm -rf *.o

clean:
	rm -rf *.o $(EJS)

run:
	@echo ">>>>>>Running p4_e1"
	./p4_e1 numeros.txt
	@echo ">>>>>>Running p4_e2"
	./p4_e2 numeros.txt
	@echo ">>>>>>Running p4_test-node-tree"
	./p4_test-node-tree nodos.txt
	@echo ">>>>>>Running p4_e3 balanced"
	./p4_e3 dict10.dat B
	@echo ">>>>>>Running p4_e3 not balanced"
	./p4_e3 dict10.dat N


runv:
	@echo ">>>>>>Running p4_e1 with valgrind"
	valgrind --leak-check=full ./p4_e1 numeros.txt
	@echo ">>>>>>Running p4_e2 with valgrind"
	valgrind --leak-check=full ./p4_e2 numeros.txt
	@echo ">>>>>>Running p4_test-node-tree with valgrind"
	valgrind --leak-check=full ./p4_test-node-tree nodos.txt
	@echo ">>>>>>Running p4_e3 balanced with valgrind"
	valgrind --leak-check=full ./p4_e3 dict10.dat B
	@echo ">>>>>>Running p4_e3 non balanced with valgrind"
	valgrind --leak-check=full ./p4_e3 dict10.dat N
