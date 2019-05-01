/*
 * File:   p4_test-node-tree.c
 * Author: Paula Samper and Laura de Paz
 *
 */

#include "tree.h"
#include "node.h"

void mainCleanUp (Tree *pt, Node *pe, FILE *pf);

int main (int argc, char **argv){
  FILE *pf = NULL;
  Tree *t = NULL;
  Node *n = NULL, *n2 = NULL;
  int id, depth, nNodes, nId;
  char name[NAMEL], nName[NAMEL];

  if (argc != 2) return (EXIT_FAILURE);

  t = tree_ini(node_destroy,node_copy,node_print,node_cmp);
  if(!t) return (EXIT_FAILURE);

  /*open file*/
  pf = fopen(argv[1], "r");
  if (!pf){
    mainCleanUp (t, n, pf);
    return EXIT_FAILURE;
  }

  /*read file line by line*/
  while (fscanf (pf,"%d %s", &id, name) == 2){
    n = node_ini();
    n = node_setId (n, id);
    n = node_setName (n, name);
    if (!n){
      mainCleanUp (t, n, pf);
      return (EXIT_FAILURE);
    }

    tree_insert(t, (void*)n);
    node_destroy(n);
  }


  nNodes = tree_numNodes(t);
  depth = tree_depth(t);

  fprintf(stdout, "Number of nodes: %d\n", nNodes);
  fprintf(stdout, "Depth: %d\n", depth);


  /* printing tree */
  fprintf(stdout, "Pre-order: \n");
  if (tree_preOrder(stdout,t) == ERROR){
    mainCleanUp (t, n, pf);
    return EXIT_FAILURE;
  }

  fprintf(stdout, "\nIn-order: \n");
  if (tree_inOrder(stdout,t) == ERROR){
    mainCleanUp (t, n, pf);
    return EXIT_FAILURE;
  }

  fprintf(stdout, "\nPost-order: \n");
  if (tree_postOrder(stdout,t) == ERROR){
    mainCleanUp (t, n, pf);
    return EXIT_FAILURE;
  }



  fprintf(stdout, "\n>Create a node: ");
  fprintf(stdout, "\n--Introduce id of the node: ");
  scanf("%d", &nId);
  fprintf(stdout, "--Introduce name of the node: ");
  scanf("%s", nName);

  n2 = node_ini();
  n2 = node_setId(n2,nId);
  n2 = node_setName(n2,nName);
  if (!n2){
    mainCleanUp(t,n,pf);
    node_destroy(n2);
    return EXIT_FAILURE;
  }
  node_print(stdout, n2);

  if (tree_find(t,n2) == TRUE){
    fprintf(stdout, "Your node is in the tree\n");
  }
  else{
    fprintf(stdout, "Your node is NOT in the tree\n");
  }


  /*mainCleanUp (t, n, pf);*/
  fclose(pf);
  tree_free(t);
  node_destroy(n2);
  return EXIT_SUCCESS;

}


void mainCleanUp (Tree *pt, Node *pe, FILE *pf){
  fclose(pf);
  tree_free(pt);
  node_destroy(pe);
}
