/*
 * File:   queue.c
 * Author: Paula Samper, Laura de Paz
 */

 #include <string.h>
 #include <errno.h>
 #include "queue.h"

#define MAX_QUEUE 100

extern int errno;
struct _Queue {
  void* items [MAX_QUEUE];
  int front;
  int rear;


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

  for (i=0; i<MAX_QUEUE; i++) {
    q->items[i] = NULL;
  }

  q->destroy_element_function = f1;
  q->copy_element_function = f2;
  q->print_element_function = f3;

  q->front = 0;
  q->rear = 0;

  return q;
}


 void queue_destroy(Queue *q){
  int i;

  if (q != NULL) {
    i = q->front;
    while (i != q->rear) {
      q->destroy_element_function(q->items[i]);
      q->items[i] = NULL;
      i = (i+1)% MAX_QUEUE;
    }
  free(q);
  }
}


Bool queue_isEmpty(const Queue *q){

  if (q == NULL) {
    return TRUE;
  }

  if (q->front == q->rear) {
    return TRUE;
  }

  return FALSE;
}


 Bool queue_isFull(const Queue* q){

  if (q == NULL) {
    return TRUE;
  }

  if (q->front == (q->rear+1)% MAX_QUEUE) {
    return TRUE;
  }

  return FALSE;
}


Queue* queue_insert(Queue *q, const void* e){

  void *aux = NULL;

  if (q == NULL || e == NULL || queue_isFull(q) == TRUE) {
    return NULL;
  }

  aux = q->copy_element_function(e);

  if (aux == NULL) {
    return NULL;
  }

  q->items[q->rear] = aux;
  q->rear = (q->rear+1)% MAX_QUEUE;

  return q;

}


 void * queue_extract(Queue *q){

  void *e = NULL;

  if (q == NULL || queue_isEmpty(q) == TRUE) {
    return NULL;
  }

  e = (void *)q->items[q->front];
  q->items[q->front] = NULL;
  q->front = (q->front+1)% MAX_QUEUE;

  return e;

}


 int queue_size(const Queue *q){

  if (q == NULL) {
    return -1;
  }

  return (q->rear - q->front + MAX_QUEUE) % MAX_QUEUE;

}


int queue_print(FILE *pf, const Queue *q){

  int i, num_char, total_char = 0;
  /*Error control*/
  if (!pf || !q) return -1;
  if (queue_isEmpty(q) == TRUE){
    fprintf(pf, "Queue empty\n");
    return -1;
  }

  fprintf(pf, "Queue with %d elements:\n", queue_size(q));
  for (i = 0; i < queue_size(q); i++){
    num_char = q->print_element_function(pf, (q->items[(q->front + i) % MAX_QUEUE]));
    if (num_char == -1) return -1;
    total_char += num_char;
  }

  return total_char;
}
