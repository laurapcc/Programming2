/*
 * File:   p3_e2.c
 * Author: Laura de Paz and Paula Samper
 */

#include "list.h"
#include "integer.h"


int mainCleanUp (int ret_value, List *pl1, List *pl2, int *pe);


int main(int argc, char **argv){
  List *l1 = NULL, *l2 = NULL;
  int num, *pe = NULL, i;

  if (argc != 2) return (EXIT_FAILURE);

  num = atoi(argv[1]);
  pe = int_ini();

  l1 = list_ini(int_destroy,int_copy,int_print,int_cmp);
  l2 = list_ini(int_destroy,int_copy,int_print,int_cmp);

  if (!l1 || !l2 || !num) {
    mainCleanUp (EXIT_FAILURE, l1, l2, pe);
  }


  for(i = num; i >= 1; i--){
    pe = (int *)int_setInfo(pe,i);
    printf("%d\n", i);
    if (i % 2 == 0){
      if (list_insertFirst(l1,(void *)pe) == NULL){
        fprintf(stdout, "Error inserting first in list 1\n");
        mainCleanUp (EXIT_FAILURE, l1, l2, pe);
      };
    }
    else{
      if (list_insertLast(l1,(void *)pe) == NULL){
        fprintf(stdout, "Error inserting last in list 1\n");
        mainCleanUp (EXIT_FAILURE, l1, l2, pe);
      }
    }
    if (list_insertInOrder(l2,(void *)pe) == NULL){
      fprintf(stdout, "Error inserting in order in list 2\n");
      mainCleanUp (EXIT_FAILURE, l1, l2, pe);
    }

  }

  list_print (stdout, l1);
  list_print (stdout, l2);

  mainCleanUp (EXIT_SUCCESS, l1, l2, pe);
  return 0;

}


int mainCleanUp (int ret_value, List *pl1, List *pl2, int *pe){
  list_destroy(pl1);
  list_destroy(pl2);
  free(pe);
  exit(ret_value);
}
