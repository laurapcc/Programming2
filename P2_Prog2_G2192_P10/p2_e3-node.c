/*
 * File:   p2_e3-node.c
 * Author: Paula Samper and Laura de Paz
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "stack_fp.h"

int cleanup(int ex_value, Node *n1, Node *n2, Stack *s);

int main() {
  /*Variable decalaration*/
  Stack *s = NULL;
  Node *n_1 = NULL;
  Node *n_2 = NULL;
  Node *temp = NULL;

  s = stack_ini(node_destroy,node_copy, node_print);


  /*node 1*/
  n_1 = node_ini();
  if (!n_1){
	   stack_destroy(s);
	   exit (EXIT_FAILURE);
  }
  n_1 = node_setName(n_1,"first");
  n_1 = node_setId(n_1,111);

  /*node 2*/
  n_2 = node_ini();
  if (!n_2) cleanup(EXIT_FAILURE, n_1, n_2, s);
  n_2 = node_setName(n_2,"second");
  n_2 = node_setId(n_2,222);


  stack_push(s, (void *)n_1);
  stack_push(s, (void *)n_2);


  fprintf(stdout,"Print the contents of the stack:\n");

  fprintf(stdout,"printed characters: %d",stack_print(stdout, s));

  fprintf(stdout,"\nEmptying stack. Elements extracted:\n");


  while (stack_isEmpty(s) == FALSE){
     temp = (Node *)stack_pop(s);
     node_print(stdout, (void *)temp);
	   node_destroy((void *)temp);
  }


  fprintf(stdout,"Print the contents of the stack after emptying:\n");
  fprintf(stdout,"printed characters:%i",stack_print(stdout, s));
  fprintf(stdout, "\n");

  /* success */
  cleanup(EXIT_SUCCESS, n_1, n_2, s);
  return 0;
}


int cleanup(int ex_value, Node *n1, Node *n2, Stack *s){
	node_destroy((void *)n1);
	node_destroy((void *)n2);
	stack_destroy(s);
	exit(ex_value);
}
