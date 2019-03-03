/*
 * File:   main.c
 * Author: Paula Samper, Laura de Paz
 */

#include "node.h"
#include "graph.h"
#include <stdio.h>

int mainCleanUp (int ret_value, Graph *gc, FILE *pf);


int main() {

    Graph *g;
    g = graph_ini();
    if (!g) return (EXIT_FAILURE);

    Node *n1, *n2;
    n1 = node_ini();
    if (!n1) mainCleanUp(1, g, stdout);
    n2 = node_ini();
    if (!n2) mainCleanUp(1, g, stdout);
    n1 = node_setId(n1,111);
    n2 = node_setId(n2,222);
    n1 = node_setName(n1,"first");
    n2 = node_setName(n2,"second");


    int insert_n1 = graph_insertNode(g, n1);
    fprintf(stdout, "\nInserting node 1... Result...:%d",insert_n1);
    if (!insert_n1) mainCleanUp(1, g, stdout);
    int insert_n2 = graph_insertNode(g, n2);
    fprintf(stdout, "\nInserting node 2... Result...:%d",insert_n2);
    if (!insert_n2) mainCleanUp(1, g, stdout);

    fprintf(stdout, "\nInserting edge: node 2 --> node 1");
    graph_insertEdge(g, node_getId(n2), node_getId(n1));

    fprintf(stdout,"\nConnected node 1 y node 2? %s", (graph_areConnected(g, node_getId(n1),node_getId(n2))==TRUE?"Yes":"No"));
    fprintf(stdout,"\nConnected node 2 y node 1? %s", (graph_areConnected(g, node_getId(n2), node_getId(n1))==TRUE?"Yes":"No"));

    insert_n2 = graph_insertNode(g, n2);
    fprintf(stdout, "\nInserting node 2... Result...:%d",insert_n2);

    //print graph
    fputs("\nGraph\n", stdout);
    graph_print(stdout, g);

    node_destroy(n1);
    node_destroy(n2);
    mainCleanUp(EXIT_SUCCESS, g, stdout);

    return 0;
}


int mainCleanUp (int ret_value, Graph *gc, FILE *pf){
    graph_destroy(gc);
    fclose (pf);
    exit (ret_value);
}
