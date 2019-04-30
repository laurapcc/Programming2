/*
 * File:   functions.c
 * Author: Paula Samper, Laura de Paz
 */

#include <string.h>
#include "functions.h"
extern int errno;

#define MAX_LENGHT 200


void string_destroy(void* e){
  if (e){
    free((char*)e);
  }
  e = NULL;
}


void * string_copy(const void* e){
	char *aux[MAX_LENGHT] = NULL;
	if (!e) return NULL;

	aux = (char *)malloc(MAX_LENGHT * sizeof(char));
  if (!new){
    fprintf(stderr, "Error copying string: %s\n", strerror(errno));
    return NULL;

	*(aux) = strcpy(*((char *)e));

	return aux;
}
/* e1 == e2 => 0
   e1 > e2 => pos
   e1 < e2 => neg*/
int string_cmp(const void* e1, const void* e2){
  if (!e1 || !e2) return -1;
  return strcmp(*((char *)e1)),(*((char *)e2));
}


void * string_ini (){
  char *aux[MAX_LENGHT] = NULL;
  new = (char*)malloc(MAX_LENGHT * sizeof(char));
  if (!aux){
    fprintf(stderr, "Error initializing string: %s\n", strerror(errno));
    return NULL;
  }
  return aux;
}
