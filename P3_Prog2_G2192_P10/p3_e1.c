/*
 * File:   p2_e4.c
 * Author: Paula Samper and Laura de Paz
 *
 */

#include "graph.h"

void cleanup(Graph *gc, Node *out, Node *in, FILE *pf);

int main(int argc, char **argv) {
  /*Variable declaration*/
  FILE *pf = NULL;
  Node *out = NULL;
  Node *in = NULL;
  Node *result = NULL;
  Graph *g = NULL;
  int IdIn, IdOut;

  /* check that there are 4 input elements , if not failure*/
  if (argc != 4) return (EXIT_FAILURE);

  /* read the input elements*/
  g = graph_ini();
  IdIn = atoi(argv[2]);
  IdOut = atoi(argv[3]);


  if (!g){
    cleanup(g, out, in, pf);
    return EXIT_FAILURE;
  }

  /*open file*/
  pf = fopen(argv[1], "r");
  if (!pf){
    cleanup(g, out, in, pf);
    return EXIT_FAILURE;
  }


  /*read graph from file*/
  if (graph_readFromFile(pf, g) == ERROR){
    cleanup(g, out, in, pf);
    return EXIT_FAILURE;
  }

  in = graph_getNode(g, IdIn);
  out = graph_getNode(g, IdOut);
  if (!in  || !out){
    cleanup(g, out, in, pf);
    return EXIT_FAILURE;
  }

  /* check if there is a path from in to out*/
  result = graph_findDeepSearch(g,node_getId(in), node_getId(out));
  if(!result){ /*If there's no path*/
    fprintf(stdout,"There´s no path between the nodes.\n");
  }

  else { /*if yes:*/
    fprintf(stdout,"It exists a path between the nodes:\n");
    node_print(stdout, in);
    node_print(stdout, out);

    /*print path*/
    fprintf(stdout,"Here is the path between the nodes:\n");
    graph_printPath (stdout, g, node_getId(out));
  }

  /*Success*/
  node_destroy(result);
  cleanup(g, out, in, pf);
  return EXIT_SUCCESS;
}


void cleanup(Graph *gc, Node *out, Node *in, FILE *pf){
  node_destroy(out);
  node_destroy(in);
  graph_destroy(gc);
  fclose(pf);
}
