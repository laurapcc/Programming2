/*
 * File:   main.c
 * Author: Paula Samper, Laura de Paz
 */

#include "node.h"
#include <stdio.h>

int main() {
    
    Node *a;
    Node *b;
    
    a = node_ini();
    b = node_ini();
    a = node_setId(a,111);
    b = node_setId(b,222);
    a = node_setName(a,"first");
    b = node_setName(b,"second");
    
    node_print(stdout,a);
    node_print(stdout,b);

    fprintf(stdout,"\nAre they equal?");
    
    if (node_cmp (a, b) == 0) fprintf(stdout,"Yes");
    else fprintf(stdout,"No");
    
    fprintf(stdout,"\nId of the first node: %i",node_getId(a));
    fprintf(stdout,"\nId of the second node: %i",node_getId(b));
    
    
    fprintf(stdout,"\n");
    b = node_copy (a);
    node_print(stdout,a);
    node_print(stdout,b);
    
    fprintf(stdout,"\nAre they equal?");
    
    if (node_cmp (a, b) == 0) fprintf(stdout,"Yes");
    else fprintf(stdout,"No");
    
    fprintf(stdout,"\n");
    node_destroy(a);
    node_destroy(b);
    
    return 0;
}
