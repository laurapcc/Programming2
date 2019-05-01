/*
 * File:   node.c
 * Author: Paula Samper, Laura de Paz
 */

#include "node.h"
extern int errno;

struct _Node{
    char name[NAMEL];
    int id;
};

Node *node_ini(){
    Node *pn = NULL;
    if (!(pn = (Node *)malloc(sizeof(Node)))){
        fprintf(stderr,"%s\n",strerror(errno));
        return NULL;
    }
	strcpy(pn->name,"");
	pn->id = -1;
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

const char *node_getName(const Node *n){
	if (n) return (n->name);
	return NULL;
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

int node_cmp (const void *n1, const void *n2){
    int res;
    Node *n1_c = NULL;
    Node *n2_c = NULL;
    n1_c = node_copy(n1);
    n2_c = node_copy(n2);
    if (n1_c->id == n2_c->id) res = 0;
    else if (n1_c->id < n2_c->id) res = -1;
    else res = 1;
    node_destroy(n1_c);
    node_destroy(n2_c);
    return res;
}

void *node_copy(const void *src){
    Node *target = NULL;
    src = (Node *)src;
    target = node_ini();

	  if (!src || !target){
		     fprintf(stderr,"%s\n",strerror(errno));
		     node_destroy(target);
		     return NULL;
	  }

    target->id = node_getId(src);
    strcpy(target->name,node_getName(src));

    return (void *)target;
}

int node_print(FILE *pf, const void * n){
    int num_char = 0;
    n = (Node *)n;

    if (!pf || !n) return -1;

    num_char += fprintf (pf,"[%d, %s]\n",node_getId(n),node_getName(n));
    return num_char;
}
