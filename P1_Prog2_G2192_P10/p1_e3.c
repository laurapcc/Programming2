/*
 * File:   main.c
 * Author: Paula Samper, Laura de Paz
 */

#include "node.h"
#include "graph.h"
#include <stdio.h>

int mainCleanUp (int ret_value, Graph *gc, FILE *pf);

int main(int argc, char **argv) {
    FILE *f = NULL;
    Graph *g = NULL;

    g = graph_ini();
    if (!g) mainCleanUp(EXIT_FAILURE, g, f);

    //graph_print(g,stdout);
    f = fopen(argv[1], "r");
    if (!f){
        fprintf(stderr, "File error\n");
        mainCleanUp(EXIT_FAILURE, g, f);
    }

    if (graph_readFromFile(f, g) == ERROR){
        printf("hola\n");
        mainCleanUp(EXIT_FAILURE, g, f);
    }
    graph_print(stdout, g);

    mainCleanUp(EXIT_SUCCESS, g, f);


    return 0;
}


int mainCleanUp (int ret_value, Graph *gc, FILE *pf){
    graph_destroy(gc);
    fclose (pf);
    exit (ret_value);
}
