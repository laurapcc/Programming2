P1_E2: main.o nodes.o graph.o
	gcc -o P1_E2 main.o nodes.o graph.o

main.o: main.c node.h types.h graph.h
	gcc -c main.c

nodes.o: nodes.c node.h types.h
	gcc -c nodes.c

graph.o: graph.c graph.h node.h types.h

clean:
	rm -f P1_E2 *.o
