/*
 * File:  list.c
 * Author: Pedro Urbina and César Ramírez (Couliste 11)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "list.h"

extern int errno;

typedef struct _NodeList { /* Private EdD, necessary to imlistement list */
  void* info;
  struct _NodeList *next;
} NodeList; /* Private NodeList type */

struct _List {
  NodeList *last; /* The LEC points to the last node and the last to the first */
  destroy_element_function_type destroy_element_function;
  copy_element_function_type copy_element_function;
  print_element_function_type print_element_function;
  cmp_element_function_type cmp_element_function;
};

NodeList* nodelist_ini ();
void nodelist_free(NodeList* pn, destroy_element_function_type f);

NodeList* nodelist_ini (){

  NodeList *nl = NULL;

  nl = (NodeList *)malloc(sizeof (NodeList));
  if (nl == NULL) {
    fprintf (stderr, "%s\n", strerror(errno));
    return NULL;
  }
  nl->info = NULL;
  nl->next = NULL;
  return nl;
}

void nodelist_free(NodeList* pn, destroy_element_function_type f){
  if (pn != NULL) {
    if (pn->info != NULL) free (pn->info);
    free(pn);
  }
}

List* list_ini (destroy_element_function_type f1, copy_element_function_type f2, print_element_function_type f3, cmp_element_function_type f4){
  List *list = NULL;

  list = (List *)malloc(sizeof(List));
  if (list == NULL) {
    return NULL;
  }

  list->last = NULL;

  list->destroy_element_function = f1;
  list->copy_element_function = f2;
  list->print_element_function = f3;
  list->cmp_element_function = f4;

  return list;
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

  if (list == NULL || pelem == NULL){
    return ERROR;
  }

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
  }
  else {
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
  }

  else {
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
  }

  else {
    aux = list->last->next;
    if(list->cmp_element_function(aux->info, pelem) > 0) {
      nodelist_free(pn, list->destroy_element_function);

      if (list_insertLast(list, pelem) == ERROR) return ERROR;
    }

    else {
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

  if (!list || list_isEmpty(list) == TRUE) return NULL;

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
  NodeList *pn = NULL;
  void *ele = NULL;

  if (!list || list_isEmpty(list) == TRUE) return NULL;

  ele = list->last->info;
  list->last->info = NULL;

  if (list->last->next == list->last) {
    nodelist_free(list->last, list->destroy_element_function);
    list->last = NULL;
    return ele;
  }

  pn = list->last;
  while (pn->next != list->last) pn = pn->next;

  pn->next = list->last->next;
  nodelist_free(list->last, list->destroy_element_function);
  list->last = pn;
  return ele;
}

Bool list_isEmpty (const List* list){

  if (list == NULL) return TRUE;

  if (list->last == NULL) return TRUE;

  return FALSE;
}

const void* list_get (const List* list, int index){
  NodeList *p = NULL;
  int count = 0;

  if((list == NULL)||(index < 1)||(index > list_size(list))) return NULL;

  p = list->last;
  do {
      p = p->next;
      count++;
  } while((count  <= index)&&(list->last != p));

  if (count == index) return p->info;
  return NULL;
}

int list_size (const List* list){
  int size = 0;
  NodeList *p = NULL;

  if (list == NULL) return -1;

  p = list->last;

  do {
    size++;
    p = p->next;
  } while(p != list->last);

  return size;
}

int list_print (FILE *fd, const List* list){
  int count = 0;
  NodeList *p = NULL;

  if (!fd || !list){
    return -1;
  }

  if (list_isEmpty(list) == TRUE) {
    fprintf(fd, "List is empty.\n");
    return 0;
  }

  fprintf(fd, "\nList with %d elements:\n", list_size(list));
  p = list->last;
  do {
    p = p->next;
    count += list->print_element_function(fd, p->info);
    count += fprintf(fd, "\n");
  } while(p != list->last);

  return count;
}
