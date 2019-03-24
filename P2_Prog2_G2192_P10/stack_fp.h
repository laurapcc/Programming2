#ifndef STACK_H
#define STACK_H
#include "types.h"
#include "node.h"

#define EMPTY_STACK -1

typedef struct _Stack Stack;

/* Types of function pointers supported by the stack */
typedef void *(*P_stack_ele_destroy)(void*);
typedef void* (*P_stack_ele_copy)(const void*);
typedef int (*P_stack_ele_print)(FILE *, const void*);


/* The stack_ini function will receive the values for the stack fields that are function pointers, that is, it will
receive the functions to, respectively, destroy, copy and print the elements of the created stack*/
Stack * stack_ini (P_stack_ele_destroy fd, P_stack_ele_copy fc, P_stack_ele_print fp);
void stack_destroy(Stack *);
Status stack_push(Stack *, const void *);
void * stack_pop(Stack *);
Bool stack_isEmpty(const Stack *);
Bool stack_isFull(const Stack *);
int stack_print(FILE*, const Stack*);

/* Privata functions for int*/
void *int_copy(const void *);
int int_print(FILE *, const void *);
double meanStack(Stack *);



#endif /* STACK_H */
