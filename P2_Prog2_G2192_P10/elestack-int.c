/*
 * File:   elestack-int.c
 * Author: Paula Samper, Laura de Paz
 */

#include "elestack.h"

struct _EleStack {
    int *e;
};


EleStack * EleStack_ini(){
    EleStack *ele = NULL;
    if (!(ele = (EleStack *)malloc(sizeof(EleStack)))){
        fprintf(stderr,"%s\n",strerror(errno));
        return NULL;
    }

    ele->e = NULL;
    return ele;
}


void EleStack_destroy(EleStack *ele){
  if (!ele) return;
  free(ele->e);
  free(ele);
}


Status EleStack_setInfo(EleStack *ele, void *p){
  int *i = NULL;
  /*Error control*/
  if (!ele || !p) return ERROR;

	if (!(i = (int *)malloc(sizeof(int)))){
    fprintf(stderr, "%s\n",strerror(errno));
    return ERROR;
  }
	*i = *(int *)p;

	free (ele->e);
	ele->e = i;
  return OK;
}


void *EleStack_getInfo(EleStack *ele){
  if (!ele) return NULL;

  return (void *)ele->e;

}


EleStack *EleStack_copy(const EleStack *ele){
  EleStack *target = NULL;
  if (!ele) return NULL;
  target = EleStack_ini();

  EleStack_setInfo(target,(void *)ele->e);

  return target;
}


Bool EleStack_equals(const EleStack *ele, const EleStack *ele_2){
  if (!ele_2 || !ele) return FALSE;

  if (*(ele->e) == *(ele_2->e)) return TRUE;
  else return FALSE;


}


int EleStack_print(FILE *pf, const EleStack *ele){
  int result;
  if (!pf || !ele) return -1;

  result = fprintf(pf, "[%d]\n", *(ele->e));
  return result;

}
