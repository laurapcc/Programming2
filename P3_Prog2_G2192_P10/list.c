/*
 * File:   list.c
 * Author: Laura de Paz and Paula Samper
 */

 #include <string.h>
 #include <errno.h>
 #include "list.h"

typedef struct _NodeList { /* EdD privada, necesaria para implementar lista */

    void* info;
    struct _NodeList *next;

} NodeList; /* Tipo NodeList privado */


struct _List {

    NodeList *last; /*La LEC apunta al último nodo y el último al primero*/

    destroy_element_function_type destroy_element_function;
    copy_element_function_type copy_element_function;
    print_element_function_type print_element_function;
    cmp_element_function_type cmp_element_function;

};


List* list_ini (destroy_element_function_type f1, copy_element_function_type f2, print_element_function_type f3, cmp_element_function_type f4){

// adaptada

  List *l = NULL;

  l = (List *)malloc(sizeof(List));
    if (l == NULL) {
      return NULL;
    }

   l->last = NULL;

   l->destroy_element_function = f1;
   l->copy_element_function = f2;
   l->print_element_function = f3;

  return l;

}


void list_destroy (List* list){ // adaptada

  if (list == NULL) {
    return;
  }

  while (list_isEmpty(list) == FALSE) {
      l->destroy_element_function (list_extractFirst(list));
  }

  free(list);

}


List* list_insertFirst (List* list, const void *pelem){ //sin adaptar
  Node *pn = NULL;
    if (pl == NULL || e == NULL) return ERR;
    pn = node_new();
    if (pn == NULL) return ERR;
    pn->info = element_copy(e);
    if (pn->info == NULL) {
      node_free(pn);
    return ERR; }
    if (cl_isEmpty() == TRUE) {
      pn->next = pn;
      pl->last = pn;
    } else {
      pn->next = pl->last->next;
      pl->last->next = pn;
    }
    return OK;
}


List* list_insertLast (List* list, const void *pelem){ //sin adaptar
  Node *pn = NULL, *qn = NULL;
    if (pl == NULL || e == NULL) return ERR;
    pn = node_new();
    if (pn == NULL) return ERR;
    pn->info = element_copy(e);
    if (pn->info == NULL) {
      node_free(pn);
      return ERR;
    }
    if (cl_isEmpty(pl) == TRUE) {
      pn->next = pn;
      pl->last = pn
    } else {
      pn->next = pl->last->next;
      pl->last->next = pn;
      pl->last = pn;
    }
    return OK;

}


List* list_insertInOrder (List *list, const void *pelem){

}


void * list_extractFirst (List* list){ //sin adaptar
  Node *pn = NULL;
    Element *pe = NULL;
    if (pl == NULL || cl_isEmpty(pl) == TRUE) {
      return NULL;
}
    pn = pl->last->next;
    pe = pn->info;
    pn->info = NULL;

    if (pl->last->next == pl->last) {
      pl->last = NULL;
      node_free(pn);
    } else {
      pl->last->next = pn->next;
      node_free(pn);
}
return pe;

}


void * list_extractLast (List* list){ //sin adaptar
  Node *pn = NULL;
    Element *pe = NULL;
    if (pl == NULL || cl_isEmpty(pl) == TRUE) {
      return NULL;
}
    if (pl->last->next == pl->last) {
      pe = pl->last->info;
      pl->last->info = NULL;
      node_free(pl->last);
      pl->last = NULL;
      return pe;
    }
pn = pl->last;
    while (pn->next != pl->last) {
      pn = pn->next;
    }
    pe = pl->last->info;
    pl->last->info = NULL;
    pn->next = pl->last->next;
    node_free(pl->last);
    pl->last = pn;
    return pe;

}



Bool list_isEmpty (const List* list){ // adaptada

    if (list == NULL) {
      return TRUE;
    }

    if (list->last == NULL) {
      return TRUE;
    }

    return FALSE;

}



const void* list_get (const List* list, int index){

}


int list_size (const List* list){

}


int list_print (FILE *fd, const List* list){

}
