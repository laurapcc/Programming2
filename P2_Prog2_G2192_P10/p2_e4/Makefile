p2_e4: p2_e4.o node.o graph.o stack_fp.o
	gcc -o p2_e4 p2_e4.o node.o graph.o stack_fp.o

p2_e4.o: p2_e4.c node.h graph.h types.h stack_fp.h
	gcc -g -c p2_e4.c

node.o: node.c node.h types.h
	gcc -g -c node.c

graph.o: graph.c graph.h stack_fp.h node.h types.h
	gcc -g -c graph.c

stack_fp.o: stack_fp.c stack_fp.h node.h types.h
	gcc -g -c stack_fp.c

clean:
	rm -f p2_e4 *.o
