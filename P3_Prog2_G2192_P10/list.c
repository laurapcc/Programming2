/*
 * File:  list.c
 * Author: Laura de Paz y Paula Samper
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "list.h"

extern int errno;


typedef struct _NodeList { /* EdD privada, necesaria para implementar lista */

  void* info;
  struct _NodeList *next;

} NodeList;  /* Tipo NodeList privado */

struct _List {

  NodeList *last; /* The LEC points to the last node and the last to the first */

  destroy_element_function_type destroy_element_function;
  copy_element_function_type copy_element_function;
  print_element_function_type print_element_function;
  cmp_element_function_type cmp_element_function;

};

/*#######################################################################
                        PRIVATE FUNCTIONS
#######################################################################*/


NodeList* nodelist_ini();
void nodelist_free(NodeList* pn, destroy_element_function_type f);


NodeList* nodelist_ini (){

  NodeList *pn = NULL;

  if ((pn = (NodeList *) malloc(sizeof (NodeList))) == NULL) {
    fprintf (stderr, "Error initializing nodelist: %s\n", strerror(errno));
    return NULL;
  }

  pn->info = NULL;
  pn->next = NULL;

  return pn;
}


void nodelist_free(NodeList* pn, destroy_element_function_type f){
  if (pn != NULL){
    if (pn->info != NULL){
      f(pn->info);
      free(pn);
    }
  }
}



/*#######################################################################
                      PRIMITIVE FUNCTIONS
#######################################################################*/

List* list_ini (destroy_element_function_type f1, copy_element_function_type f2, print_element_function_type f3, cmp_element_function_type f4){

  List *l = NULL;

  l = (List *)malloc(sizeof(List));
  if (l == NULL) {
    fprintf(stderr, "Error initializing list: %s\n", strerror(errno));
    return NULL;
  }

  l->last = NULL;

  l->destroy_element_function = f1;
  l->copy_element_function = f2;
  l->print_element_function = f3;
  l->cmp_element_function = f4;

  return l;

}


void list_destroy (List* list){

  if (list == NULL) return;

  while (list_isEmpty(list) == FALSE) {
    list->destroy_element_function(list_extractFirst(list));
  }

  free(list);
  list = NULL;

}


Status list_insertFirst (List* list, const void *pelem){

  NodeList *pn = NULL;

  if (list == NULL || pelem == NULL) return ERROR;

  pn = nodelist_ini();
  if (pn == NULL) return ERROR;

  pn->info = list->copy_element_function(pelem);

  if (pn->info == NULL) {
    nodelist_free(pn, list->destroy_element_function);
    return ERROR;
  }

  if (list_isEmpty(list) == TRUE) {

    pn->next = pn;
    list->last = pn;

  } else {

    pn->next = list->last->next;
    list->last->next = pn;

  }

  return OK;

}


Status list_insertLast (List* list, const void *pelem){

  NodeList *pn = NULL;

  if (list == NULL || pelem == NULL) return ERROR;

  pn = nodelist_ini();
  if (pn == NULL) return ERROR;

  pn->info = list->copy_element_function(pelem);

  if (pn->info == NULL) {

    nodelist_free(pn, list->destroy_element_function);
    return ERROR;

  }

  if (list_isEmpty(list) == TRUE) {

    pn->next = pn;
    list->last = pn;

  } else {

    pn->next = list->last->next;
    list->last->next = pn;
    list->last = pn;

  }

  return OK;

}


Status list_insertInOrder (List *list, const void *pelem){

  NodeList *pn = NULL, *aux = NULL;

  if (list == NULL || pelem == NULL) return ERROR;

  pn = nodelist_ini();
  if (pn == NULL) return ERROR;

  pn->info = list->copy_element_function(pelem);

  if (pn->info == NULL) {

    nodelist_free(pn, list->destroy_element_function);
    return ERROR;

  }

  if (list_isEmpty(list) == TRUE) {

    pn->next = pn;
    list->last = pn;

  } else {

    aux = list->last->next;

    if (list->cmp_element_function(aux->info, pelem) > 0) {

      nodelist_free(pn, list->destroy_element_function);
      if (list_insertLast(list, pelem) == ERROR) return ERROR;

    } else {

      while ((aux != list->last) && (list->cmp_element_function(pelem, aux->next->info) > 0)) {

        aux = aux->next;
        if(aux == list->last) {
          nodelist_free(pn, list->destroy_element_function);
          if (list_insertLast(list, pelem) == ERROR) return ERROR;
        }

        pn->next = aux->next;
        aux->next = pn;

      }
    }
  }
  return OK;
}


void * list_extractFirst (List* list){
  NodeList *aux = NULL;
  void * ele = NULL;

  if (!list || list_isEmpty(list) == TRUE){
    return NULL;
  }

  ele = list->last->next->info;
  list->last->next->info = NULL;

  if (list->last->next == list->last) {
    nodelist_free(list->last, list->destroy_element_function);
    list->last = NULL;
  }

  else {
    aux = list->last->next;
    list->last->next = aux->next;
    nodelist_free(aux, list->destroy_element_function);
  }
  return ele;
}


void * list_extractLast (List* list){
  NodeList *aux = NULL;
  void *ele = NULL;

  if (!list || list_isEmpty(list) == TRUE){
    return NULL;
  }

  ele = list->last->info;
  list->last->info = NULL;

  if (list->last->next == list->last) {
    nodelist_free(list->last, list->destroy_element_function);
    list->last = NULL;
    return ele;
  }

  aux = list->last;
  while (aux->next != list->last){
    aux = aux->next;
  }

  aux->next = list->last->next;
  nodelist_free(list->last, list->destroy_element_function);
  list->last = aux;

  return ele;
}


Bool list_isEmpty (const List* list){

  if (list == NULL){
    return TRUE;
  }

  if (list->last == NULL){
    return TRUE;
  }

  return FALSE;
}


const void* list_get (const List* list, int index){
  NodeList *nl = NULL;
  int count = 0;

  if(list == NULL || list_isEmpty(list) || index > list_size(list) || index < 1){
    return NULL;
  }

  nl = list->last;

  do {
    nl = nl->next;
    count++;
  } while(count <= index && list->last != nl);

  if (count == index){
    return nl->info;
  }

  return NULL;
}

int list_size (const List* list){
  NodeList *nl = NULL;
  int count = 0;

  if (list == NULL){
    return -1;
  }

  nl = list->last;

  do {
    count++;
    nl = nl->next;
  } while(nl != list->last);

  return count;
}

int list_print (FILE *fd, const List* list){
  NodeList *pl = NULL;
  int count = 0;

  if (!fd || !list) {
    fprintf(stderr, "Error printing list: %s\n", strerror(errno));
    return -1;
  }

  if (list_isEmpty(list) == TRUE) {
    return -1;
  }

  fprintf(fd, "List with %d elements:\n", list_size(list));

  pl = list->last;

  do {
    pl = pl->next;
    count += list->print_element_function(fd, pl->info);
  } while(pl != list->last);

  return count;
}
