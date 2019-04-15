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

/*#######################################################################
                        PRIVATE FUNCTIONS
#######################################################################*/

NodeList* nodelist_ini(){

  NodeList *pn;

  if ((pn = (NodeList*) malloc(sizeof(NodeList))) ==NULL) return NULL;

  pn->info = pn->next = NULL;

  return pn;

}


void nodelist_free(NodeList *pn, destroy_element_function_type f){

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
  void *ext;
  if (list == NULL) {
    return;
  }

  while (list_isEmpty(list) == FALSE) {
    ext = list_extractFirst(list);
    list->destroy_element_function (ext);
  }

  free(list);
}


List* list_insertFirst (List* list, const void *pelem){
  NodeList *pn = NULL;

  if (list == NULL || pelem == NULL){
    return NULL;
  }

  pn = nodelist_ini();
  if (pn == NULL) return NULL;

  pn->info = list->copy_element_function(pelem);

  if (pn->info == NULL) {
    nodelist_free(pn,list->destroy_element_function);
    return NULL;
  }

  if (list_isEmpty (list) == TRUE) {
    pn->next = pn;
    list->last = pn;

  } else {
    pn->next = list->last->next;
    list->last->next = pn;
  }


  return list;
}


List* list_insertLast (List* list, const void *pelem){
  NodeList *pn = NULL;

  if (list == NULL || pelem == NULL){
    return NULL;
  }

  pn = nodelist_ini();
  if (pn == NULL) return NULL;

  pn->info = list->copy_element_function(pelem);
  if (pn->info == NULL) {
      nodelist_free(pn, list->destroy_element_function);
      return NULL;
  }

  if (list_isEmpty(list) == TRUE) {
    pn->next = pn;
    list->last = pn;
    return list;
  }


  pn->next = list->last->next;
  list->last->next = pn;
  list->last = pn;


  return list;

}


List* list_insertInOrder (List *list, const void *pelem){
  NodeList *pn = NULL, *aux = NULL;

  if (list == NULL || pelem == NULL){
    return NULL;
  }

  pn = nodelist_ini();
  if (pn == NULL) return NULL;

  pn->info = list->copy_element_function(pelem);
  if (pn == NULL) return NULL;

  if (list_isEmpty(list) == TRUE){
    pn->next = pn;
    list->last = pn;
  }

  else{
    aux = list->last->next;

    if (list->cmp_element_function(pelem, aux->info) < 0){ /* if pelem < aux->info */
      nodelist_free(pn,list->destroy_element_function);

      return list_insertFirst (list, pelem);
    }

    while (list->last != aux && list->cmp_element_function(pelem,aux->next->info) > 0){ /* if pelem > aux->next->info */
      aux = aux->next;
    }

    if (list->last == aux){
      list->last = pn;
      /* list = list_insertLast (list, (void *)pn); */
      /*list->last = pn;*/
    }

    pn->next = aux->next;
    aux->next = pn;

  }

return list;

}


void * list_extractFirst (List* list){
  NodeList *nl = NULL, *aux = NULL;

  if (list == NULL || list_isEmpty(list) == TRUE) {
    return NULL;
  }

  nl = list->last->next;
  list->last->next->info = NULL;

  if (list->last->next == list->last) {
    nodelist_free(list->last,list->destroy_element_function);
    list->last = NULL;
  }

  else {
    aux = list->last->next;
    list->last->next = aux->next;
    nodelist_free(aux,list->destroy_element_function);
  }

  return (void *)nl->info;

}


void * list_extractLast (List* list){
  NodeList *aux = NULL;
  void *ele = NULL;

  if (list == NULL || list_isEmpty(list) == TRUE) {
    return NULL;
  }

  ele = (void *)list->last->info;
  list->last->info = NULL;

  if (list->last->next == list->last) {
    nodelist_free(list->last,list->destroy_element_function);
    list->last = NULL;
  }

  aux = list->last;
  while (aux->next != list->last) {
    aux = aux->next;
  }

  aux->next = list->last->next;
  nodelist_free(aux,list->destroy_element_function);
  list->last = aux;

  return ele;

}


Bool list_isEmpty (const List* list){

  if (list == NULL) {
    return TRUE;
  }

  if (list->last == NULL) {
    return TRUE;
  }

  return FALSE;

}


const void* list_get (const List* list, int index){
  NodeList *nl = NULL;
  int count = 0;

  if (list == NULL){
    return NULL;
  }

  nl = list->last;

  do{
    count++;
    nl = nl->next;
  } while (nl != list->last && count != index);

  if (count == index){
    return (void *)nl->info;
  }

  else{
    return NULL;
  }
}


int list_size (const List* list){
  NodeList *nl = NULL;
  int count = 0;

  if (list == NULL){
    return -1;
  }

  nl = list->last;

  do{
    count++;
    nl = nl->next;
  } while(nl != list->last);

  return count;
}


int list_print (FILE *fd, const List* list){

  NodeList *pl = NULL;
  int count = 0;

  if (!fd || !list){
    fprintf(stderr, "Error printing list: %s\n", strerror(errno));
    return -1;
  }

  if (list_isEmpty(list)){
    return -1;
  }

  count += fprintf(fd,"List with %d elements:\n",list_size(list));

  pl = list->last;

  do{
    pl = pl->next;
    count += list->print_element_function(fd, pl->info);
  } while (pl != list->last);

  return count;

}
