########################################################
CC=gcc
CFLAGS= -g -Wall -ansi -pedantic
EJS = p2_e1 p2_e2 p2_e3-node p2_e3-int p2_e4
########################################################
OBJECTSP1E1 = p2_e1.o node.o elestack-node.o stack_elestack.o
OBJECTSP1E2 = p2_e2.o stack_elestack.o elestack-int.o
OBJECTSP1E3NODE = p2_e3-node.o stack_fp.o node.o
OBJECTSP1E3INT = p2_e3-int.o stack_fp.o
OBJECTSP1E4 = p2_e4.o graph.o stack_fp.o node.o
########################################################

all: $(EJS) clean

p2_e1: $(OBJECTSP1E1)
	$(CC) $(CFLAGS) -o p2_e1 $(OBJECTSP1E1)

p2_e2: $(OBJECTSP1E2)
	$(CC) $(CFLAGS) -o p2_e2 $(OBJECTSP1E2)

p2_e3-node: $(OBJECTSP1E3NODE)
	$(CC) $(CFLAGS) -o p2_e3-node $(OBJECTSP1E3NODE)

p2_e3-int: $(OBJECTSP1E3INT)
	$(CC) $(CFLAGS) -o p2_e3-int $(OBJECTSP1E3INT)

p2_e4: $(OBJECTSP1E4)
	$(CC) $(CFLAGS) -o p2_e4 $(OBJECTSP1E4)

p2_e4.o: p2_e4.c graph.h stack_fp.h node.h types.h
	$(CC) $(CFLAGS) -c p2_e4.c

p2_e3-node.o: p2_e3-node.c stack_fp.h node.h types.h
	$(CC) $(CFLAGS) -c p2_e3-node.c

p2_e3-int.o: p2_e3-int.c stack_fp.h types.h
	$(CC) $(CFLAGS) -c p2_e3-int.c

p2_e2.o: p2_e2.c stack_elestack.h elestack.h types.h
	$(CC) $(CFLAGS) -c p2_e2.c

p2_e1.o: p2_e1.c stack_elestack.h elestack.h node.h types.h
	$(CC) $(CFLAGS) -c p2_e1.c

node.o: node.c node.h types.h
	$(CC) $(CFLAGS) -c node.c

elestack-node.o: elestack-node.c elestack.h node.h types.h
	$(CC) $(CFLAGS) -c elestack-node.c

elestack-int.o: elestack-int.c elestack.h types.h
	$(CC) $(CFLAGS) -c elestack-int.c

stack_fp.o: stack_fp.c node.h types.h
	$(CC) $(CFLAGS) -c stack_fp.c

graph.o: graph.c graph.h node.h types.h
	$(CC) $(CFLAGS) -c graph.c

clear:
	rm -rf *.o

clean:
	rm -rf *.o $(EJS)

run:
	@echo ">>>>>>Running p2_e1"
	./p2_e1
	@echo ">>>>>>Running p2_e2"
	./p2_e2 8
	@echo ">>>>>>Running p2_e3-node"
	./p2_e3-node
	@echo ">>>>>>Running p2_e3-int"
	./p2_e3-int 8
	@echo ">>>>>>Running p2_e4"
	./p2_e4 g1.txt 3 1

runv:
	@echo ">>>>>>Running p2_e1 with valgrind"
	valgrind --leak-check=full ./p2_e1
	@echo ">>>>>>Running p2_e2 with valgrind"
	valgrind --leak-check=full ./p2_e2 8
	@echo ">>>>>>Running p2_e3-node with valgrind"
	valgrind --leak-check=full ./p2_e3-node
	@echo ">>>>>>Running p2_e3-int with valgrind"
	valgrind --leak-check=full ./p2_e3-int 8
	@echo ">>>>>>Running p2_e4 with valgrind"
	valgrind --leak-check=full ./p2_e4 g1.txt 3 1
