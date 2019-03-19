/*
 * File:   p2_e1.c
 * Author: Paula Samper and Laura de Paz
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "stack_elestack.h"

int cleanUp (int ret_value, EleStack *ele, Stack *s){
    EleStack_destroy(ele);
    stack_destroy(s);
    exit(ret_value);
}

int main(int argc, char *argv[]) {

  int i, lenght_s;
  double mean;


  if (argc != 2) return (EXIT_FAILURE);
  lenght_s = atoi(argv[1]);

  Stack *s;
  s = stack_ini();
  if (!s) return (EXIT_FAILURE);

  EleStack *ele;
  ele = EleStack_ini();
  if (!ele) cleanUp(EXIT_FAILURE,ele,s);

  for (i = 0; i <= lenght_s; i++){
      if (!EleStack_setInfo(ele,(void *)(&i))) cleanUp(EXIT_FAILURE,ele,s);
      if(!stack_push(s,ele)) cleanUp(EXIT_FAILURE,ele,s);
  }

  fprintf(stdout, "Stack before the call to the function\n");
  if (stack_print(stdout,s) == -1) cleanUp(EXIT_FAILURE,ele,s);
  mean = meanElementStack(s);
  if (mean == -1) cleanUp(EXIT_FAILURE,ele,s);
  fprintf(stdout, "The average is %lf\n",mean);

  fprintf(stdout, "Stack after the call to the function\n");
  if (stack_print(stdout,s) == -1) cleanUp(EXIT_FAILURE,ele,s);


  cleanUp(EXIT_SUCCESS,ele,s);
}
