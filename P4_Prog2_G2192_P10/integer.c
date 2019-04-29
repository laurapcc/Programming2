/*
 * File:   integer.c
 * Author: Paula Samper, Laura de Paz
 */

#include "integer.h"
extern int errno;



void int_destroy(void* e){
  if (e){
    free((int*)e);
  }
  e = NULL;
}


void *int_copy(const void *e){
	int *a = NULL;
	if (!e) return NULL;
	a = (int *)malloc(sizeof(int));
	*(a) = *((int *)e);
	return a;
}


int int_print(FILE *pf, const void *a){
	if (!pf || !a) return -1;
	return fprintf(pf,"%d ", *((int *)a));
}


/* e1 == e2 => 0
   e1 > e2 => pos
   e1 < e2 => neg*/
int int_cmp(const void* e1, const void* e2){
  if (!e1 || !e2) return -1;
  return (*((int *)e1)) - (*((int *)e2));
}


void * int_ini (){
  int *new = NULL;
  new = (int*)malloc(sizeof(int));
  if (!new){
    fprintf(stderr, "Error initializing integer: %s\n", strerror(errno));
    return NULL;
  }
  return new;
}


void * int_setInfo (void *e, int v){
  if (!e) return NULL;
  (*(int *)e) = v;
  return e;
}
