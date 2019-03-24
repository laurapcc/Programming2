/*
 * File:   stack_elestack.c
 * Author: Paula Samper, Laura de Paz
 */


#include "stack_elestack.h"

struct Stack {
 int top;
 EleStack *item[MAXSTACK];
};



Stack * stack_ini(){
    Stack *s = NULL;
    int i;
    if (!(s = (Stack *)malloc(sizeof(Stack)))){
        fprintf(stderr,"Error initializing stack");
        return NULL;
    }

    for (i = 0; i < MAXSTACK; i++) s->item[i] = NULL;
    s->top = EMPTY_STACK;

    return s;
}


void stack_destroy(Stack *stc){
    while (stc->top != EMPTY_STACK){
        EleStack_destroy(stc->item[stc->top]);
	      stc->item[stc->top] = NULL;
        stc->top --;
    }
    free(stc);
}


Status stack_push(Stack *stc, const EleStack *el_stc){
    EleStack *el_stc_copy = NULL;
    if (!stc || !el_stc){
        fprintf(stderr,"Error in stack_push");
        return ERROR;
    }

    /*stack full*/
    if (stack_isFull(stc)){
        fprintf(stderr,"Stack full");
        return ERROR;
    }

    /*copy of el_stc*/
    el_stc_copy = EleStack_copy(el_stc);
    if (!el_stc_copy){
       	fprintf(stderr,"No copy");
    	  return ERROR;
    }

    stc->top++;
    stc->item[stc->top] = el_stc_copy;

    return OK;
}


EleStack * stack_pop(Stack *stc){
    EleStack *el_s = NULL;
    /*Error control*/
    if (!stc){
        fprintf(stderr,"Error in stack_pop");
        return NULL;
    }

    if (stack_isEmpty(stc)){
        fprintf(stderr,"Stack empty");
        return NULL;
    }

    el_s = stc->item[stc->top];
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


int stack_print(FILE* pf, const Stack* stc){
    int i, num_char, total_char = 0;
    /*Error control*/
    if (!pf || !stc) return -1;

    for (i = stc->top; i > EMPTY_STACK; i--){
        num_char = EleStack_print(pf,stc->item[i]);
	      if (num_char == -1) return -1;
	      total_char += num_char;
    }

    return total_char;
}



/**--------------------------------------------------------------------
                    PRIVATE FUNCTIONS
---------------------------------------------------------------------*/

double meanElementStack(Stack *s){
  int counter = 0, sum = 0;
  double mean = 0;

  Stack *aux_s = NULL;
  EleStack *ele = NULL;
  aux_s = stack_ini();
  ele = EleStack_ini();
  if (!s || !aux_s || !ele) return -1;
  free(ele);

  while (s->top > EMPTY_STACK){
    ele = stack_pop(s);
    if (stack_push(aux_s,ele) == ERROR || !ele) return -1;
    sum += *((int *)EleStack_getInfo(ele));
    counter ++;
    EleStack_destroy(ele);
  }

  while (aux_s->top > EMPTY_STACK){
    ele = stack_pop(aux_s);
    if (stack_push(s,ele) == ERROR || !ele) return -1;
    EleStack_destroy(ele);
  }

  stack_destroy(aux_s);
  mean = (double)sum / (double)counter;
  return mean;

}
