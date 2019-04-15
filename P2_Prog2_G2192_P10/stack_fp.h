/*
 * File:   stack_fp.h
 * Author: Paula Samper, Laura de Paz
 */

#ifndef STACK_H
#define STACK_H
#include "types.h"
#include "node.h"

#define EMPTY_STACK -1

typedef struct _Stack Stack;

/* Types of function pointers supported by the stack */
typedef void (*P_stack_ele_destroy)(void*);
typedef void* (*P_stack_ele_copy)(const void*);
typedef int (*P_stack_ele_print)(FILE *, const void*);


/* The stack_ini function will receive the values for the stack fields that are function pointers, that is, it will
receive the functions to, respectively, destroy, copy and print the elements of the created stack*/
Stack * stack_ini (P_stack_ele_destroy fd, P_stack_ele_copy fc, P_stack_ele_print fp);

/* Remove the stack Input: the stack to be removed */
void stack_destroy(Stack *);

/*Insert an EleStack in the stack. Input: an EleStack and the stack where to insert it. Output: NULL if you can
not insert it or the resulting stack if it succeeds*/
Status stack_push(Stack *, const void *);

/* Extract an EleStack in the stack. Input: the stack from which to extract it. Output: NULL if you can not extract it
or the extracted EleStack if it succeeds. Note that the stack will be modified */
void * stack_pop(Stack *);

/* Check if the stack is empty. Input: stack. Output: TRUE if it is empty or FALSE if it is not */
Bool stack_isEmpty(const Stack *);

/* Check if the stack is full. Input: stack. Exit: TRUE if it is full or FALSE if it is not */
Bool stack_isFull(const Stack *);

/* Print the entire stack, placing the EleStack on top at the beginning of printing (and one EleStack per line).
Input: stack and file where to print it. Output: Returns the number of written characters. */
int stack_print(FILE*, const Stack*);


#endif /* STACK_H */
