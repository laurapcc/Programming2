P1_E1: main.o nodes.o
	gcc -o P1_E1 main.o nodes.o

main.o: main.c node.h types.h
	gcc -c main.c

nodes.o: nodes.c node.h types.h
	gcc -c nodes.c

clean:
	rm -f P1_E1 *.o
