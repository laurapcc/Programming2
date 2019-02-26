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
  Node *n_1 = NULL;
  Node *n_2 = NULL;

  Stack *s = NULL;

  EleStack *ele_1 = NULL;
  EleStack *ele_2 = NULL;

  s = stack_ini();

  n_1 = node_ini();
  ele_1 = EleStack_ini();
  n_1 = node_setName(n_1,"first");
  n_1 = node_setId(n_1,111);
  EleStack_setInfo(ele_1, (Node*)n_1);
  stack_push(s, ele_1);

  n_2 = node_ini();
  ele_2 = EleStack_ini();
  n_2 = node_setName(n_2,"second");
  n_2 = node_setId(n_2,222);
  EleStack_setInfo(ele_2, (Node*)n_2);
  stack_push(s, ele_2);

  fprintf(stdout,"Print the contents of the stack:\n");

  fprintf(stdout,"printed characters: %d",stack_print(stdout, s));

  fprintf(stdout,"\nEmptying stack. Elements extracted:\n");

  while ((s->top)>EMPTY_STACK){
    s->item[s->top] = stack_pop(s);
    EleStack_print(stdout, s->item[s->top]);
    s->top--;
    fprintf(stdout, "\n");
  }

  fprintf(stdout,"Print the contents of the stack after emptying:\n");
  fprintf(stdout,"printed characters:%i",stack_print(stdout, s));
  fprintf(stdout, "\n");

  //node_destroy(n_1);
  //node_destroy(n_2);
  EleStack_destroy(ele_1);
  EleStack_destroy(ele_2);
  stack_destroy(s);

  return (EXIT_SUCCESS);
}

/*
int cleanup(int ret_value, Node *pn, EleStack *ele, Stack *s){
  node_destroy(pn);
  elestack_destroy(ele);
  stack_destroy(s);

  exit(ret_value);
}
*/
