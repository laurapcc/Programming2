/*
 * File:   stack_elestack.h
 * Author: Paula Samper, Laura de Paz
 */

#ifndef STACK_ELESTACK_H
#define STACK_ELESTACK_H

#define MAXSTACK 1024
#define EMPTY_STACK -1
#include "elestack.h"

typedef struct _Stack{
  int top;
  EleStack *item[MAXSTACK];
}Stack;

/**------------------------------------------------------------------
Initialize the stack reserving memory. Output: NULL if there was an error or the stack if it went well
----------------------------------------------------*/
Stack * stack_ini();

/**------------------------------------------------------------------
Remove the stack Input: the stack to be removed
------------------------------------------------------------------*/
void stack_destroy(Stack *stc);

/**------------------------------------------------------------------
Insert an EleStack in the stack. Input: an EleStack and the stack where to insert it. Output: NULL if you can
not insert it or the resulting stack if it succeeds
------------------------------------------------------------------*/
Status stack_push(Stack *stc, const EleStack *el_stc);

/**------------------------------------------------------------------
Extract an EleStack in the stack. Input: the stack from which to extract it. Output: NULL if you can not extract it
or the extracted EleStack if it succeeds. Note that the stack will be modified
------------------------------------------------------------------*/
EleStack * stack_pop(Stack *stc);

/**------------------------------------------------------------------
Check if the stack is empty. Input: stack. Output: TRUE if it is empty or FALSE if it is not
------------------------------------------------------------------*/
Bool stack_isEmpty(const Stack *);

/**------------------------------------------------------------------
Check if the stack is full. Input: stack. Exit: TRUE if it is full or FALSE if it is not
------------------------------------------------------------------*/
Bool stack_isFull(const Stack *);

/**------------------------------------------------------------------
Print the entire stack, placing the EleStack on top at the beginning of printing (and one EleStack per line).
Input: stack and file where to print it. Output: Returns the number of written characters.
------------------------------------------------------------------*/
int stack_print(FILE*, const Stack*);


#endif /* STACK_ELESTACK_H */
