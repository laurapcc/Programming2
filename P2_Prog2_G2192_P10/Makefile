p2_e1: p2_e1.o node.o elestack-node.o stack_elestack.o
	gcc -o p2_e1 p2_e1.o node.o elestack-node.o stack_elestack.o

p2_e1.o: p2_e1.c node.h types.h elestack.h stack_elestack.h
	gcc -c p2_e1.c

node.o: node.c node.h types.h
	gcc -c node.c

elestack-node.o: elestack-node.c elestack.h  node.h types.h
	gcc -c elestack-node.c

stack_elestack.o: stack_elestack.c stack_elestack.h elestack.h node.h types.h
	gcc -c stack_elestack.c

clean:
	rm -f p2_e1 *.o
