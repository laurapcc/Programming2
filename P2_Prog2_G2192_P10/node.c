/*
 * File:   main.c
 * Author: Paula Samper, Laura de Paz
 */


#include "node.h"
#define NAMEL 100

struct _Node{
    char name[NAMEL];
    Label etq;
    int id;
    int nConnect;
    int antecessor_id;
};

Node *node_ini(){
    Node *pn = NULL;
    if (!(pn = (Node *)malloc(sizeof(Node)))){
        fprintf(stderr,"Node cannot be initialized");
        return NULL;
    }
	strcpy(pn->name,"");
  pn->etq = WHITE;
	pn->id = -1;
	pn->nConnect = 0;
  pn->antecessor_id = -1;
    return pn;
}

void node_destroy(void *n){
  n = (Node *)n;
	if (n) free(n);
}

int node_getId(const Node *n){
    if (n) return n->id;
    return -1;
}

int node_getAntecesorId(const Node*n){
  if (n) return n->antecessor_id;
  return -1;
}


const char *node_getName(const Node *n){
	if (n) return (n->name);
	return NULL;
}

Label node_getLabel(const Node *n){
	if (n) return (n->etq);
	return WHITE;
}

int node_getConnect(const Node *n){
    if (n) return n->nConnect;
    return -1;
}

Node *node_setId(Node *n, const int id){
    if (!n) return NULL;
    n->id = id;
    return n;
}

Node* node_setAntecesorId(Node *n, int id){
  if (!n) return NULL;
  n->antecessor_id = id;
  return n;
}

Node *node_setName(Node *n, const char *name){
    if (!n) return NULL;
    strcpy(n->name,name);
    return n;
}

Node *node_setLabel(Node *n, Label label){
    if (!n) return NULL;
    n->etq = label;
    return n;
}


Node *node_setConnect(Node *n, const int cn){
    if (!n) return NULL;
    n->nConnect = cn;
    return n;
}

int node_cmp (const Node *n1, const Node *n2){
    if (n1->id == n2->id) return 0;
    else if (n1->id < n2->id) return -1;
    else return 1;
}

void *node_copy(const void *src){
    Node *target = NULL;
    target = node_ini();
	  if (!src || !target){
		     fprintf(stderr,"%s\n",strerror(errno));
		     node_destroy(target);
		     return NULL;
	  }

    target->id = node_getId(src->id);
    strcpy(target->name,node_getName(src->name));
    target->etq = node_getLabel(src->etq);
    target->nConnect = node_getLabel(src->nConnect);
    target->antecessor_id = node_getAntecesorId(src->antecessor_id);

    return (void *)target;
}

int node_print(FILE *pf, const void * n){
    n = (Node *)n;
    int num_char = 0;
    if (!pf || !n) return -1;
    num_char += fprintf (pf,"[%d, %s, %d]\n",node_getId(n->id),node_getName(n->name),node_getConnect(n->nConnect));
    return num_char;
}
