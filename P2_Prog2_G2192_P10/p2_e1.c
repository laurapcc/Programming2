/*
 * File:   p2_e1.c
 * Author: Paula Samper and Laura de Paz
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "stack_elestack.h"

//int cleanup(int ret_value, Node *pn, EleStack *ele, Stack *s);

int main() {
  Stack *s = NULL;
  s = stack_ini();

  //node 1
  Node *n_1 = NULL;
  n_1 = node_ini();
  if (!n_1){
	stack_destroy(s);
	return EXIT_FAILURE;
  }
  n_1 = node_setName(n_1,"first");
  n_1 = node_setId(n_1,111);
  
  EleStack *ele_1 = NULL;
  ele_1 = EleStack_ini();
  if (!ele_1){
	stack_destroy(s);
        return EXIT_FAILURE;	
  }

  EleStack_setInfo(ele_1, (Node*)n_1);
  stack_push(s, ele_1);
 
 
  //node 2
  Node *n_2 = NULL;
  n_2 = node_ini();
  if (!n_2){
	stack_destroy(s);
	return EXIT_FAILURE;
  }
  n_2 = node_setName(n_2,"second");
  n_2 = node_setId(n_2,222);

  EleStack *ele_2 = NULL;
  ele_2 = EleStack_ini();
  if (!ele_2){
	stack_destroy(s);
        return EXIT_FAILURE;	
  }

  EleStack_setInfo(ele_2, (Node*)n_2);
  stack_push(s, ele_2);

 
  fprintf(stdout,"Print the contents of the stack:\n");

  fprintf(stdout,"printed characters: %d",stack_print(stdout, s));

  fprintf(stdout,"\nEmptying stack. Elements extracted:\n");

  while ((s->top)> EMPTY_STACK){
    EleStack_print(stdout, s->item[s->top]);
    stack_pop(s);
  }

  fprintf(stdout,"Print the contents of the stack after emptying:\n");
  fprintf(stdout,"printed characters:%i",stack_print(stdout, s));
  fprintf(stdout, "\n");

  /**
  node_destroy(n_1);
  node_destroy(n_2);
  EleStack_destroy(ele_1);
  EleStack_destroy(ele_2);
  stack_destroy(s);
  **/

  return (EXIT_SUCCESS);
}

/**
int cleanup(int ret_value, Node *pn, EleStack *ele, Stack *s){
  node_destroy(pn);
  elestack_destroy(ele);
  stack_destroy(s);

  exit(ret_value);
}
**/

