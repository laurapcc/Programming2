/*
 * File:   p2_e3.c
 * Author: Paula Samper and Laura de Paz
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int cleanup(int ret_value, Graph *gc, Node *out, Node *in, FILE *pf);

int main(int argc, char **argv) {
//declara variables
  FILE *pf = NULL;
  Node *out = NULL;
  Node *in = NULL;
  Graph *g = NULL;
  int IdIn, IdOut;

// check that there are 4 input elements , if not failure
  if (argc != 4) exit(EXIT_FAILURE);

  // read the input elements
  out = node_ini();
  in = node_ini();
  g = graph_ini();
  IdIn = atoi(argv[2]);
  IdOut = atoi(argv[3]);


  if (!g || !out || !in){
    cleanup(EXIT_FAILURE, g, out, in, pf);
  }

  //open file
  pf = fopen(argv[1], "r");
  if (!pf){
     cleanup(EXIT_FAILURE, g, out, in, pf);
   }

  //read graph from file
   if (graph_readFromFile(pf, g) == ERROR){
     cleanup(EXIT_FAILURE, g, out, in, pf);
   }
   in = graph_getNode(g, IdIn);
   out = graph_getNode(g, IdOut);


  //print the graph
   graph_print(stdout, g);
  // check if there is a path from in to out

  if(!graph_findDeepSearch(g,node_getId(in), node_getId(out))){
    // if not print "no...."
    fprintf(stdout,"There´s no path between the nodes.\n");
  }

  else { //if yes:
    fprintf(stdout,"It exists a path between the nodes:\n");
    node_print(stdout, in);
    node_print(stdout, out);

    //print path
    //fprintf(stdout,"Here is the path between the nodes:\n");
    //graph_printPath (stdout, g, node_getId(out));
  }

  //Success
  cleanup(EXIT_SUCCESS, g, out, in, pf);
}


int cleanup(int ret_value, Graph *gc, Node *out, Node *in, FILE *pf){
  node_destroy(out);
	node_destroy(in);
	graph_destroy(gc);
  //cierro el archivo
  fclose(pf);
  exit(ret_value);
}
