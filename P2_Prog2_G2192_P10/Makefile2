p2_e2: p2_e2.o elestack-int.o stack_elestack.o
	gcc -o p2_e2 p2_e2.o elestack-int.o stack_elestack.o

p2_e2.o: p2_e2.c types.h elestack.h stack_elestack.h
	gcc -c p2_e2.c

elestack-int.o: elestack-int.c elestack.h types.h
	gcc -c elestack-int.c

stack_elestack.o: stack_elestack.c stack_elestack.h elestack.h types.h
	gcc -c stack_elestack.c

clean:
	rm -f p2_e2 *.o
