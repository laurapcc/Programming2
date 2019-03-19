/*
 * File:   main.c
 * Author: Paula Samper, Laura de Paz
 */


#include "node.h"
#define NAMEL 100

struct _Node{
    char name[NAMEL];
    int id;
    int nConnect;
};

Node *node_ini(){
    Node *pn = NULL;
    if (!(pn = (Node *)malloc(sizeof(Node)))){
        fprintf(stderr,"Node cannot be initialized");
        return NULL;
    }
	strcpy(pn->name,"");
	pn->id = -1;
	pn->nConnect = 0;
    return pn;
}

void node_destroy(Node *n){
	if (n) free(n);
}

int node_getId(const Node *n){
    if (n) return n->id;
    return -1;
}

const char *node_getName(const Node *n){
	if (n) return (n->name);
	return NULL;
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

Node *node_setName(Node *n, const char *name){
    if (!n) return NULL;
    strcpy(n->name,name);
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

Node *node_copy(const Node *src){
    Node *target = NULL;
    target = node_ini();
	if (!src || !target){
		fprintf(stderr,"%s\n",strerror(errno));
		node_destroy(target);
		return NULL;
	}

    target->id = src->id;
    strcpy(target->name,src->name);
    target->nConnect = src->nConnect;

    return target;
}

int node_print(FILE *pf, const Node * n){
    int num_char = 0;
    if (!pf || !n) return -1;
    num_char += fprintf (pf,"[%d, %s, %d]\n",n->id,n->name,n->nConnect);
    return num_char;
}
