/*
 * File:   p2_e1.c
 * Author: Paula Samper and Laura de Paz
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "stack_fp.h"


int cleanUp (int ret_value, Stack *s);


int main(int argc, char *argv[]) {

  int i, lenght_s, ele;
  double mean;


  if (argc != 2) return (EXIT_FAILURE);
  lenght_s = atoi(argv[1]);

  Stack *s;
  s = stack_ini(free,(void *)int_copy, (void *)int_print);
  if (!s) return (EXIT_FAILURE);

  for (i = 0; i <= lenght_s; i++){
      ele = i;
      if(!stack_push(s,(void *)&ele)) cleanUp(EXIT_FAILURE,s);
  }

  fprintf(stdout, "Stack before the call to the function\n");
  if (stack_print(stdout,s) == -1) cleanUp(EXIT_FAILURE,s);
  mean = meanStack(s);
  if (mean == -1) cleanUp(EXIT_FAILURE,s);
  fprintf(stdout, "The average is %lf\n",mean);

  fprintf(stdout, "Stack after the call to the function\n");
  if (stack_print(stdout,s) == -1) cleanUp(EXIT_FAILURE,s);


  cleanUp(EXIT_SUCCESS,s);
}



int cleanUp (int ret_value, Stack *s){
    stack_destroy(s);
    exit(ret_value);
}
