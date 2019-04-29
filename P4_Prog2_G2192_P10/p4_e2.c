/*
 * File:   p4_e2.c
 * Author: Paula Samper and Laura de Paz
 *
 */

#include "tree.h"
#include "integer.h"

void mainCleanUp (Tree *pt, void *pe, FILE *pf);

int main(int argc, char **argv) {
  /*Variable declaration*/
  FILE *pf = NULL;
  Tree *t = NULL;
  void *num = NULL;
  int aux, depth, nNodes;

  /* check that there are 2 input elements , if not failure*/
  if (argc != 2) return (EXIT_FAILURE);

  t = tree_ini(int_destroy,int_copy,int_print,int_cmp);
  num = int_ini();
  if (!t || !num){
    mainCleanUp (t, num, pf);
    return EXIT_FAILURE;
  }

  /*open file*/
  pf = fopen(argv[1], "r");
  if (!pf){
    mainCleanUp (t, num, pf);
    return EXIT_FAILURE;
  }

  /*read file line by line*/
  while (fscanf(pf, "%d", &aux) == 1){
    int_setInfo(num,aux);
    if (tree_insert(t,num) == ERROR){
      mainCleanUp (t, num, pf);
      return EXIT_FAILURE;
    }
    /*hay que destroy num antes de volver a allocarlo?*/
  }

  nNodes = tree_numNodes(t);
  depth = tree_depth(t);

  fprintf(stdout, "Number of nodes: %d\n", nNodes);
  fprintf(stdout, "Depth: %d\n", depth);

  /* printing tree */
  fprintf(stdout, "Pre-order: ");
  if (tree_preOrder(stdout,t) == ERROR){
    mainCleanUp (t, num, pf);
    return EXIT_FAILURE;
  }

  fprintf(stdout, "\nIn-order: ");
  if (tree_inOrder(stdout,t) == ERROR){
    mainCleanUp (t, num, pf);
    return EXIT_FAILURE;
  }

  fprintf(stdout, "\nPost-order: ");
  if (tree_postOrder(stdout,t) == ERROR){
    mainCleanUp (t, num, pf);
    return EXIT_FAILURE;
  }


  fprintf(stdout, "\n>Introduce a number: ");
  scanf("%d", &aux);
  fprintf(stdout, "Number introduced: %d\n", aux);

  int_setInfo(num,aux);
  if (tree_find(t,num) == TRUE){
    fprintf(stdout, "%d is in the tree\n", aux);
  }
  else{
    fprintf(stdout, "%d is NOT in the tree\n", aux);
  }


  mainCleanUp (t, num, pf);
  return EXIT_SUCCESS;
}


void mainCleanUp (Tree *pt, void *pe, FILE *pf){
  fclose(pf);
  tree_free(pt);
  int_destroy(pe);
}
