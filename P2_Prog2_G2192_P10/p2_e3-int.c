/*
 * File:   p2_e3-int.c
 * Author: Paula Samper and Laura de Paz
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "stack_fp.h"


int cleanUp (int ret_value, Stack *s);

int main(int argc, char *argv[]) {
  /*Variable declaration*/
  int i, lenght_s, ele;
  double mean;
  Stack *s;


  if (argc != 2) return (EXIT_FAILURE);
  lenght_s = atoi(argv[1]);

  s = stack_ini(free,int_copy,int_print);
  if (!s) return (EXIT_FAILURE);

  for (i = 0; i <= lenght_s; i++){
      ele = i;
      if(!stack_push(s,(void *)&ele)) cleanUp(EXIT_FAILURE,s);
  }


  fprintf(stdout, "Stack before the call to the function\n");
  if (stack_print(stdout,s) == -1) cleanUp(EXIT_FAILURE,s);

  mean = meanStack(s);
  if (mean == -1) cleanUp(EXIT_FAILURE,s);
  fprintf(stdout, "The average is %f\n",mean);

  fprintf(stdout, "Stack after the call to the function\n");
  if (stack_print(stdout,s) == -1) cleanUp(EXIT_FAILURE,s);

  /* success */
  cleanUp(EXIT_SUCCESS,s);
}



int cleanUp (int ret_value, Stack *s){
    stack_destroy(s);
    exit(ret_value);
}
