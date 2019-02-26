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
    return pn;
}

void node_destroy(Node *n){
    free(n);
}

int node_getId(const Node *n){
    if (n) return n->id;
    else return -1;
}

char *node_getName(const Node *n){
    if (n) return n->name;
    else return NULL;
}

int node_getConnect(const Node *n){
    if (n) return n->nConnect;
    else return -1;
}

Node *node_setId(Node *n, const int id){
    if (!n) return NULL;
    else{
        n->id = id;
        return n;
    }
}

Node *node_setName(Node *n, const char *name){
    if (!n) return NULL;
    else{
        strcpy(n->name,name);
        return n;
    }
}

Node *node_setConnect(Node *n, const int cn){
    if (!n) return NULL;
    else{
        n->nConnect = cn;
        return n;
    }
}

int node_cmp (const Node *n1, const Node *n2){
    if (n1->id == n2->id) return 0;
    else if (n1->id < n2->id) return -1;
    else return 1;
}

Node *node_copy(const Node *src){
    if (!src) return NULL;
    Node *target = NULL;
    if (!(target = (Node *)malloc(sizeof(Node)))) return NULL;
    target->id = src->id;
    strcpy(target->name,src->name);
    target->nConnect = src->nConnect;
    return target;
}

int node_print(FILE *pf, const Node * n){
    if (!pf || !n) return -1;
    fprintf (pf,"[%d, %s, %d]\n",n->id,n->name,n->nConnect);
    return 1;
}
