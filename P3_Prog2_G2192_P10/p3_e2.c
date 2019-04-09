/*
 * File:   p3_e2.c
 * Author: Laura de Paz and Paula Samper
 */

#include "list.h"
#include "integer.h"

/*

create clean function: int mainCleanUp (int ret_value, List *pl1, List *pl2, int *pe)

main (check errors when needed and return failure when needed):

//declare variables

// check that there are 2 input elements , if not failure

// read the input element

//initialize 2 lists

//initialize an integer

// for all numbers from input to 1

   //Set in the interger the number


  //check odd or even:

       //   In the first list, if the number is even it will insert it at the beginning and if it is odd at the end.

       //  In the second list, inserts the number in order (always keep the list sorted).

// Prints both lists.

//Free resources used

*/

int mainCleanUp (int ret_value, List *pl1, List *pl2, int *pe);


int main(int argc, char **argv){
  List *l1 = NULL, *l2 = NULL;
  int *num;

  if (argc != 2) return (EXIT_FAILURE);

  num = (int *)int_ini();
  *num = atoi(argv[1]);

  l1 = list_ini(int_destroy,int_copy,int_print,int_cmp);
  l2 = list_ini(int_destroy,int_copy,int_print,int_cmp);

  if (!l1 || !l2 || num) {
    mainCleanUp (EXIT_FAILURE, l1, l2, num);
  }

  while (*num >= 1){
    if (*num % 2 == 0){
      list_insertFirst(l1,(void *)num);
      list_insertInOrder(l2,(void *)num);
    }
    else{
      list_insertLast(l1,(void *)num);
      list_insertInOrder(l2,(void *)num);
    }
    (*num) --;
  }

  list_print (stdout, l1);
  list_print (stdout, l2);

  mainCleanUp (EXIT_SUCCESS, l1, l2, num);
  return 0;

}


int mainCleanUp (int ret_value, List *pl1, List *pl2, int *pe){
  list_destroy(pl1);
  list_destroy(pl2);
  free(pe);
  exit(ret_value);
}
