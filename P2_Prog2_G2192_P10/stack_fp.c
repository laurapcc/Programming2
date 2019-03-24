/*
 * File:   stack_fp.c
 * Author: Paula Samper, Laura de Paz
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "stack_fp.h"

#define MAXSTACK 100
#define EMPTY_STACK -1

extern int errno;
struct _Stack {
    int top;
    void *item[MAXSTACK];

    P_stack_ele_destroy pf_destroy;
    P_stack_ele_copy pf_copy;
    P_stack_ele_print pf_print;
};



Stack *stack_ini (P_stack_ele_destroy fd, P_stack_ele_copy fc, P_stack_ele_print fp) {
    Stack *s;
    int i;

    s = (Stack*) malloc(sizeof(Stack));
    if (!s) {
    fprintf(stderr, "%s\n", strerror(errno));
    return NULL;
    }

    s->top = -1;
    s->pf_copy = fc;
    s->pf_destroy = fd;
    s->pf_print = fp;

    /* assign the pointers of the elements*/
    for (i=0; i< MAXSTACK; i++)
    s->item[i] = NULL;

    return s;
}

void stack_destroy(Stack* stc) {
    if (stc){
		while (stc->top != EMPTY_STACK) {
    		stc->pf_destroy( stc->item[stc->top]); /* Call to the function whose pointer was stored as a stack field
    		*that is, using the pointer to the function*/
    		stc->top --;
    	}
	}
    free(stc);
}




Status stack_push(Stack *stc, const void *ele){
	void *copy;
    if (!stc || !ele){
        fprintf(stderr,"%s\n",strerror(errno));
        return ERROR;
    }

    /*stack full*/
    if (stack_isFull(stc)){
        fprintf(stderr,"Stack full");
        return ERROR;
    }

    /*copy of el_stc*/
    copy = stc->pf_copy(ele);
    if (!copy){
      fprintf(stderr,"No copy");
    return ERROR;
    }

    stc->top++;
    stc->item[stc->top] = copy;

    return OK;

}


void * stack_pop(Stack *stc){
	void *el_s;
    /*Error control*/
    if (!stc){
        fprintf(stderr,"Error in stack_pop");
        return NULL;
    }

    if (stack_isEmpty(stc)){
        fprintf(stderr,"Stack empty");
        return NULL;
    }

    el_s = (void *)stc->item[stc->top];
    stc->item[stc->top] = NULL;
    stc->top--;

    return el_s;
}



Bool stack_isEmpty(const Stack *stc){
  /*Error control*/
  if (!stc) return FALSE;

  if (stc->top == EMPTY_STACK) return TRUE;
  return FALSE;
}


Bool stack_isFull(const Stack *stc){
    /*Error control*/
    if (!stc) return TRUE;

    if (stc->top == MAXSTACK - 1) return TRUE;
    return FALSE;
}


int stack_print(FILE* pf, const Stack *stc){
	int i, num_char, total_char = 0;
    /*Error control*/
    if (!pf || !stc) return -1;

    for (i = stc->top; i > EMPTY_STACK; i--){
        num_char = stc->pf_print(pf,stc->item[i]);
        if (num_char == -1) return -1;
        total_char += num_char;
    }
    return total_char;


}


/*---------------PRIVATE FUNCTIONS FOR INT------------------*/

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


int int_print(FILE *pf, const void *a){
	if (!pf || !a) return -1;
	return fprintf(pf,"[%d]\n", *((int *)a));
}


double meanStack(Stack *s){

  int counter = 0, sum = 0, *ele;
  double mean = 0;

  Stack *aux_s;
  aux_s = stack_ini(free,int_copy, int_print);

  if (!s || !aux_s) return -1;

  while (s->top > EMPTY_STACK){
    ele = (int *)stack_pop(s);
    if (stack_push(aux_s,(void *)ele) == ERROR || !ele) return -1;
    sum += *ele;
    counter ++;
    free(ele);
  }

  while (aux_s->top > EMPTY_STACK){
    ele = (int *)stack_pop(aux_s);
    if (stack_push(s,(void *)ele) == ERROR || !ele) return -1;
    free(ele);
  }

  stack_destroy(aux_s);
  mean = (double)sum / (double)counter;
  return mean;
}
