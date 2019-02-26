/*
 * File:   stack_elestack.h
 * Author: Paula Samper, Laura de Paz
 */


#include "stack_elestack.h"
//#define MAXSTACK 1024
//#define EMPTY_STACK -1


struct Stack {
 int top;
 EleStack *item[MAXSTACK];
};


/**------------------------------------------------------------------
Initialize the stack reserving memory. Output: NULL if there was an error or the stack if it went well
----------------------------------------------------*/
Stack * stack_ini(){
    Stack *s = NULL;
    if (!(s = (Stack *)malloc(sizeof(Stack)))){
        fprintf(errno,"Error initializing stack");
        return NULL;
    }

    for (int i = 0; i < MAXSTACK; i++) s->item[i] = NULL;

    s->top = EMPTY_STACK;

    return s;
}

/**------------------------------------------------------------------
Remove the stack Input: the stack to be removed
------------------------------------------------------------------*/
void stack_destroy(Stack *stc){
    while (stc->top != EMPTY_STACK){
        EleStack_destroy(stc->item[stc->top]);
        stc->top --;
    }
    free(stc);
}

/**------------------------------------------------------------------
Insert an EleStack in the stack. Input: an EleStack and the stack where to insert it. Output: NULL if you can
not insert it or the resulting stack if it succeeds
------------------------------------------------------------------*/
Status stack_push(Stack *stc, const EleStack *el_stc){
    if (!stc || !el_stc){
        fprintf(errno,"Error in stack_push");
        return ERROR;
    }

    //stack full
    if (stack_isFull(stc)){
        fprintf(errno,"Stack full");
        return ERROR;
    }

    //copy of el_stc
    EleStack *el_stc_copy = EleStack_copy(el_stc);
    if (!el_stc_copy) return ERROR;

    stc->top++;
    stc->item[stc->top] = el_stc_copy;

    return OK;
}

/**------------------------------------------------------------------
Extract an EleStack in the stack. Input: the stack from which to extract it. Output: NULL if you can not extract it
or the extracted EleStack if it succeeds. Note that the stack will be modified
------------------------------------------------------------------*/
EleStack * stack_pop(Stack *stc){
    //Error control
    if (!stc){
        fprintf(errno,"Error in stack_pop");
        return NULL;
    }

    EleStack *el_s;

    if (stack_isEmpty(stc)){
        fprintf(errno,"Stack empty");
        return NULL;
    }

    el_s = stc->item[stc->top];
    stc->item[stc->top] = NULL;
    stc->top--;

    return el_s;

}

/**------------------------------------------------------------------
Check if the stack is empty. Input: stack. Output: TRUE if it is empty or FALSE if it is not
------------------------------------------------------------------*/
Bool stack_isEmpty(const Stack *stc){
    //Error control
    if (!stc) return FALSE;

    if (stc->top == EMPTY_STACK) return TRUE;
    return FALSE;
}

/**------------------------------------------------------------------
Check if the stack is full. Input: stack. Exit: TRUE if it is full or FALSE if it is not
------------------------------------------------------------------*/
Bool stack_isFull(const Stack *stc){
    //Error control
    if (!stc) return FALSE;

    if (stc->top == MAXSTACK - 1) return TRUE;
    return FALSE;
}

/**------------------------------------------------------------------
Print the entire stack, placing the EleStack on top at the beginning of printing (and one EleStack per line).
Input: stack and file where to print it. Output: Returns the number of written characters.
------------------------------------------------------------------*/
int stack_print(FILE* pf, const Stack* stc){
    //Error control
    if (!pf || !stc) return -1;

    int num_char = 0;

    for (int i = stc->top; i > EMPTY_STACK; i--){
        num_char += EleStack_print(pf,stc->item[i]);
        num_char += fprintf(pf, "\n");
    }
    return num_char;
}
