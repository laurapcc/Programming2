/*
 * File:   queuel.c
 * Author: Paula Samper, Laura de Paz
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <errno.h>
 #include "queuel.h"
 #include "list.h"

#define MAX_QUEUE 100

extern int errno;
struct _Queue {

  List *list;

  destroy_element_function_type destroy_element_function;
  copy_element_function_type copy_element_function;
  print_element_function_type print_element_function;
};



Queue* queue_ini(destroy_element_function_type f1, copy_element_function_type f2, print_element_function_type f3){

  Queue *q = NULL;
  int i;
  q = (Queue *)malloc(sizeof(Queue));

  if (q == NULL) {
    fprintf(stderr, "%s\n", strerror(errno));
    return NULL;
  }

  q->list = list_ini(f1, f2, f3, NULL);

  if (!q->list) {
    free(q);
    return NULL;
  }

  q->destroy_element_function = f1;
  q->copy_element_function = f2;
  q->print_element_function = f3;

  return q;
}


 void queue_destroy(Queue *q){

  if (q == NULL) return;
  list_destroy(q->list);
  free(q);

}


Bool queue_isEmpty(const Queue *q){

  if (q == NULL) {
    return TRUE;
  }

  return list_isEmpty (q->list);

}


Bool queue_isFull(const Queue* q){

  if (q == NULL) {
    return TRUE;
  }

  return FALSE;
}


Queue* queue_insert(Queue *q, const void* e){

  if (!q || !e) return NULL;

  if (!list_insertLast(q->list, e)){
    return NULL;
  } else {
    return q;
  }

}


void * queue_extract(Queue *q){

  if (queue_isEmpty(q) || !q) {
    return NULL;
  } else {
    return list_extractFirst(q->list);
  }
}


int queue_size(const Queue *q){

  if (q == NULL) {
    return -1;
  } else {
    return list_size (q->list);
  }

}


int queue_print(FILE *pf, const Queue *q){
  
  if (!q || !pf) return -1;
  return list_print(pf, q->list);

}
