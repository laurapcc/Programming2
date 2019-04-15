/*
 * File:   elestack-node.c
 * Author: Paula Samper, Laura de Paz
 */

#include "elestack.h"

struct _EleStack {
    Node *info;
};


EleStack * EleStack_ini(){
    EleStack *ele = NULL;

    if (!(ele = (EleStack *)malloc(sizeof(EleStack)))){
      fprintf(stderr, "%s\n",strerror(errno));
      return NULL;
    }

  ele->info = NULL;
  return ele;
}


void EleStack_destroy(EleStack *ele){
  if (!ele) return;
  node_destroy((void *)ele->info);
  free(ele);
}


Status EleStack_setInfo(EleStack *ele, void *p){
  Node* p_prima;
  /*Error control*/
  if (!ele || !p) return ERROR;

  p_prima = (Node *)p;
  if (ele->info != NULL) node_destroy((void *)ele->info);

  ele->info = (Node *)node_copy((void *)p_prima);
  return OK;
}


void *EleStack_getInfo(EleStack *ele){
  if (!ele) return NULL;
  return (void *)ele->info;

}


EleStack *EleStack_copy(const EleStack *ele){
  EleStack *target = NULL;

  if (!ele) return NULL;
  target = EleStack_ini();
  if (!target) return NULL;

  EleStack_setInfo(target,(void *)ele->info);

  return target;

}


Bool EleStack_equals(const EleStack *ele, const EleStack *ele_2){
  if (!ele_2 || !ele) return FALSE;

  if (ele->info == ele_2->info) return TRUE;
  else return FALSE;


}


int EleStack_print(FILE *pf, const EleStack *ele){
  int result;
  if (!pf || !ele) return -1;

  result = node_print(pf, (void *)ele->info);
  return result;

}
