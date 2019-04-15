/*
 * File:   p2_e3-int.c
 * Author: Paula Samper and Laura de Paz
 *
 */

#include "stack_fp.h"


int cleanUp (int ret_value, Stack *s);
void *int_copy(const void *);
int int_print(FILE *, const void *);
double meanStack(Stack *);


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
  return 0;
}



int cleanUp (int ret_value, Stack *s){
    stack_destroy(s);
    exit(ret_value);
}


/* Reserves memory for an int where it copies the data from the int src.
 * Returns the address of the copied node if everything went well, or NULL otherwise */
void *int_copy(const void *src){
	int *a;
	if (!src) return NULL;
	if (!(a = (int *)malloc(sizeof(int)))){
		fprintf(stderr, "Error in int_copy");
		return NULL;
	}
	*a = *((int *)src);
	return (void *)a;
}

/* Print the integer int the file stated in the argument
 * Returns number of characters printed or -1 if there is any error*/
int int_print(FILE *pf, const void *a){
	if (!pf || !a) return -1;
	return fprintf(pf,"[%d]\n", *((int *)a));
}

/* Returns the mean of all the elements in the stack or -1 if there is any error */
double meanStack(Stack *s){
  int counter = 0, sum = 0, *ele;
  double mean = 0;

  Stack *aux_s;
  aux_s = stack_ini(free,int_copy, int_print);

  if (!s || !aux_s) return -1;

  while (stack_isEmpty(s) == FALSE){
    ele = (int *)stack_pop(s);
    if (stack_push(aux_s,(void *)ele) == ERROR || !ele) return -1;
    sum += *ele;
    counter ++;
    free(ele);
  }

  while (stack_isEmpty(s) == FALSE){
    ele = (int *)stack_pop(aux_s);
    if (stack_push(s,(void *)ele) == ERROR || !ele) return -1;
    free(ele);
  }

  stack_destroy(aux_s);
  mean = (double)sum / (double)counter;
  return mean;
}
