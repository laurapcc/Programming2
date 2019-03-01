/*
 * File:   elestack-node.c
 * Author: Paula Samper, Laura de Paz
 */

#include "elestack.h"

struct _EleStack {
    int *e;
};

/**------------------------------------------------------------------
Initialize a stack EleStack. Output: Pointer to the initialized EleStack or NULL in case of error
------------------------------------------------------------------*/
EleStack * EleStack_ini(){
    EleStack *ele = NULL;
    if (!(ele = (EleStack *)malloc(sizeof(EleStack)))){
        fprintf(stderr,"Error initializing Element of stack");
        return NULL;
    }

    ele->e = NULL;
    return ele;
}

/**------------------------------------------------------------------
Remove an EleStack. Entry: EleStack to destroy.
------------------------------------------------------------------*/
void EleStack_destroy(EleStack *ele){
    free(ele->e);
    free(ele);
}

/**------------------------------------------------------------------
Modify the data of an EleStack. Entry: The EleStack to be modified and the content to be saved in that
EleStack. Output: OK or ERROR
------------------------------------------------------------------*/
Status EleStack_set_int(EleStack *ele, void *p){
    //Error control
    if (!ele || !p) return ERROR;

    if (ele->e != NULL) free(ele->e);

    //void *copy_p;
    //copy_p = p;
    ele->e = (int *)p;
    if (!ele->e) return ERROR;

    return OK;
}

/**------------------------------------------------------------------
Returns the EleStack content. Entry: The EleStack. Output: The content of EleStack or NULL if there has been
an error.
------------------------------------------------------------------*/

void *EleStack_get_int(EleStack *ele){
    if (!ele) return NULL;

    return (void *)ele->e;

}

/**------------------------------------------------------------------
Copy one EleStack in another, reserving memory. Input: the EleStack to copy. Output: Returns a pointer to the
copied EleStack or NULL in case of error.
------------------------------------------------------------------*/
EleStack *EleStack_copy(const EleStack *ele){
  if (!ele) return NULL;
  EleStack *target = NULL;
  if (!(target = (EleStack *)malloc(sizeof(EleStack)))) return NULL;
  *(target->e) = *(ele->e);
  return target;

}

/**------------------------------------------------------------------
Compares two EleStack. Entry: two EleStack to compare. Output: Returns TRUE if they are the same and if
not FALSE
------------------------------------------------------------------*/
Bool EleStack_equals(const EleStack *ele, const EleStack *ele_2){
  if (!ele_2 || !ele) return FALSE;

  if (*(ele->e) == *(ele_2->e)) return TRUE;
  else return FALSE;


}

/**------------------------------------------------------------------
Print the EleStack in a file that is already open. Input: File in which it is printed and the EleStack to print.
Output: Returns the number of written characters.
------------------------------------------------------------------*/
int EleStack_print(FILE *pf, const EleStack *ele){
  if (!pf || !ele) return -1;

  int result = fprintf(pf, "[%d]\n", *(ele->e));
  return result;

}