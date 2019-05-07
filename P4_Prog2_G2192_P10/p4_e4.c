/*
 * File:   p4_e4.c
 * Author: Paula Samper and Laura de Paz
 *
 */
#include <string.h>
#include <stdlib.h>

#include "tree.h"
#include "functions.h"

void mainCleanUp (Tree *pt, void *pe, FILE *pf);

int main(int argc, char **argv) {

 /*Variable declaration*/
 FILE *pf = NULL;
 Tree *t = NULL;
 void *string = NULL;
 char aux[255]; /*es lo que usa en la función nueva pero no estoy segura*/
 int depth, nNodes;

 /* check that there are 2 input elements , if not failure*/
 if (argc != 2) return (EXIT_FAILURE);


 /*open file*/
 pf = fopen(argv[1], "r");
 if (!pf){
   mainCleanUp (t, NULL, pf);
   return EXIT_FAILURE;
 }

 t = tree_ini(string_destroy, string_copy, string_print, string_cmp);
 if (!t ){
   mainCleanUp (t, NULL, pf);
   return EXIT_FAILURE;
 }

 /*read file line by line*/
 while (!(feof(pf))){
   string = (void *)read_string_from_file(pf);

   if (!string){
     mainCleanUp (t, NULL, pf);
     return EXIT_FAILURE;
   }
   if (tree_insert(t, (void *)string) == ERROR) {
     mainCleanUp(t, string, pf);
     return EXIT_FAILURE;
   }
   string_destroy(string);

 }

 fclose(pf);

 nNodes = tree_numNodes(t);
 depth = tree_depth(t);

 fprintf(stdout, "Number of nodes: %d\n", nNodes);
 fprintf(stdout, "Depth: %d\n", depth);



 /*printing in order*/
 if (tree_inOrder(stdout,t) == ERROR){
   mainCleanUp (t, string, pf);
   return EXIT_FAILURE;
 }


 fprintf(stdout, ">Introduce a string to search in the tree: ");
 fscanf(stdin,"%s", aux);

 fprintf(stdout, "String introduced: %s\n", aux);

/*no estoy segura de las siguientes 3 lineas, como la entrada de la funcion es un pointer, lo copio en string*/

 string = (char *)malloc((1 + strlen(aux)) * sizeof(char));
 if (!string){
   mainCleanUp (t, NULL, pf);
   return EXIT_FAILURE;;
 }
 strcpy (/*(char*)*/string, aux);

 if (tree_find(t,string) == TRUE){
   fprintf(stdout, "%s is in the tree\n", aux);
 }
 else{
   fprintf(stdout, "%s is NOT in the tree\n", aux);
 }


 mainCleanUp (t, string, pf);
 return EXIT_SUCCESS;


}


void mainCleanUp (Tree *pt, void *pe, FILE *pf){
 fclose(pf);
 tree_free(pt);
 string_destroy(pe);
}
