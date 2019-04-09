/*
 * File:   integer.c
 * Author: Paula Samper, Laura de Paz
 */

#include "integer.h"
extern int errno;

void int_destroy(void* e){
  if (e == NULL) return;
  free(e);
  e = NULL;
}


void *int_copy(const void *e){
	int *a;
	if (!e) return NULL;
	if (!(a = (int *)malloc(sizeof(int)))){
		fprintf(stderr, "Error in int_copy");
		return NULL;
	}
	*a = *((int *)e);
	return (void *)a;
}


int int_print(FILE *pf, const void *a){
	if (!pf || !a) return -1;
	return fprintf(pf,"[%d]\n", *((int *)a));
}

/* e1 == e2 => 0
   e1 < e2 => pos
   e1 > e2 => neg*/
int int_cmp(const void* e1, const void* e2){
if (!e1 || !e2) return -2;
  if ((*(int *)e1) == (*(int *)e2)){
    return 0;
  } else if ((*(int *)e1) > (*(int *)e2)){
    return -1;
  } else{
    return 1;
  }
}


void * int_ini (){
  int *new;
  new = (int*)malloc(sizeof(int));
  if (!new){
    fprintf(stderr, "Error initializing integer: %s\n", strerror(errno));
    return NULL;
  }
  return (void *)new;
}


void * int_setInfo (void *e, int v){
  if (!e || !v) return NULL;
  (*(int *)e) = v;
  return e;
}
