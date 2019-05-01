/*
 * File:   functions.c
 * Author: Paula Samper, Laura de Paz
 */

#include <string.h>
#include "functions.h"
extern int errno;


void string_destroy(void* e){
  if (e){
    free((char*)e);
  }
  e = NULL;
}


void * string_copy(const void* e){
	char *aux;

	if (!e) return NULL;

	aux = (char *)malloc(strlen((char *)e) * sizeof(char));
  if (!aux){
    fprintf(stderr, "Error copying string: %s\n", strerror(errno));
    return NULL;
  }

	strcpy(aux,(char *)e);

	return aux;
}

int string_print (FILE *f, const void *e){
  if (!f || !e) return -1;
  return fprintf(f, "%s\n", (char *)e);
}

/* e1 == e2 => 0
   e1 > e2 => pos
   e1 < e2 => neg*/
int string_cmp(const void* e1, const void* e2){
  if (!e1 || !e2) return -1;
  return strcmp((char *)e1,(char *)e2);
}
