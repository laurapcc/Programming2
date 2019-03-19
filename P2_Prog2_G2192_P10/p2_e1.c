/*
 * File:   p2_e1.c
 * Author: Paula Samper and Laura de Paz
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "stack_elestack.h"

int cleanup(int ret_value, Node *pn, EleStack *ele, Stack *s);

int main() {
  Stack *s = NULL;
  s = stack_ini();

  //node 1
  Node *n_1 = NULL;
  n_1 = node_ini();
  if (!n_1){
	stack_destroy(s);
	exit (EXIT_FAILURE);
  }
  n_1 = node_setName(n_1,"first");
  n_1 = node_setId(n_1,111);
  
  EleStack *ele_1 = NULL;
  ele_1 = EleStack_ini();
  if (!ele_1){
	stack_destroy(s);
	node_destroy(n_1);
  exit(EXIT_FAILURE);	
  }

  if (EleStack_setInfo(ele_1, (Node*)n_1) == ERROR) cleanup(EXIT_FAILURE, n_1, ele_1, s);

  if (stack_push(s, ele_1) == ERROR) cleanup(EXIT_FAILURE, n_1, ele_1, s);
 
 
  //node 2
  Node *n_2 = NULL;
  n_2 = node_ini();
  if (!n_2) cleanup(EXIT_FAILURE, n_1, ele_1, s);

  n_2 = node_setName(n_2,"second");
  n_2 = node_setId(n_2,222);

  EleStack *ele_2 = NULL;
  ele_2 = EleStack_ini();
  if (!ele_2){
	node_destroy(n_2);
	cleanup(EXIT_FAILURE, n_1, ele_1, s);
  }

  if (EleStack_setInfo(ele_2, (Node*)n_2) == ERROR){
	node_destroy(n_2);
	EleStack_destroy(ele_2);
	cleanup(EXIT_FAILURE, n_1, ele_1, s);
  }
  if (stack_push(s, ele_2) == ERROR){
	node_destroy(n_2);
	EleStack_destroy(ele_2);
	cleanup(EXIT_FAILURE, n_1, ele_1, s);
  }

 
  fprintf(stdout,"Print the contents of the stack:\n");

  fprintf(stdout,"printed characters: %d",stack_print(stdout, s));

  fprintf(stdout,"\nEmptying stack. Elements extracted:\n");

  while ((s->top) > EMPTY_STACK){
    EleStack* temp = NULL;

    EleStack_print(stdout, s->item[s->top]);
    temp = stack_pop(s);
    EleStack_destroy(temp);
  }

  fprintf(stdout,"Print the contents of the stack after emptying:\n");
  fprintf(stdout,"printed characters:%i",stack_print(stdout, s));
  fprintf(stdout, "\n");

  
  node_destroy(n_2);
  EleStack_destroy(ele_2);
  cleanup(EXIT_SUCCESS, n_1, ele_1, s);
}


int cleanup(int ret_value, Node *pn, EleStack *ele, Stack *s){
  	node_destroy(pn);
  	EleStack_destroy(ele);
  	stack_destroy(s);

  	exit(ret_value);
}


