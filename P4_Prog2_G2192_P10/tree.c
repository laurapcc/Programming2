/*
 * File:   tree.c
 * Author: Paula Samper, Laura de Paz
 */

#include "tree.h"

typedef struct _NodeBT {

  void* info;

  struct _NodeBT* left;
  struct _NodeBT* right;

} NodeBT ;

struct _Tree {

  NodeBT *root;

  destroy_element_function_type destroy_element_function;
  copy_element_function_type copy_element_function;
  print_element_function_type print_element_function;
  cmp_element_function_type cmp_element_function;

};

extern int errno;

/* ----------------------- PRIVATE FUNCTIONS ----------------------- */


void destroyNodeAB (NodeBT *pn, destroy_element_function_type f){
  if (!pn) return;
  f(pn);
}

void tree_freeRec(NodeBT* pn, destroy_element_function_type f){
  if (!pn) return;
  tree_freeRec(LEFT(pn),f);
  tree_freeRec(RIGHT(pn),f);

  destroyNodeAB(pn,f);
}


NodeBT **iniNodeAB(){
  
}

Status tree_insertRec(NodeBT** ppn, const void*po, copy_element_function_type f, cmp_element_function_type c){

  int cmp;

  if (!po || !f || !c) return ERROR;

  if (*ppn == NULL) {
    *ppn = iniNodeAB(); //no se si la funcion esta hecha
    if (*ppn == NULL) return ERROR;

    INFO(*ppn) = f(po);

    if (INFO(*ppn) == NULL) {
      bt_node_free(*ppn); //???
      return ERROR;
    }

    return OK;
    }


  if (c(po, INFO(*ppn)) == 0){
    return ERROR; //raro
  } else if (c(po, INFO(*ppn)) > 0){
    return tree_insertRec(&RIGHT(*ppn), po, f, c);
  } else {
    return tree_insertRec(&LEFT(*ppn), po, f, c);
  }

  return ERROR;//raro

}


/*Print the pn node information in the output stream pf.*/
int printNodeAB(FILE* pf, const NodeBT *pn, print_element_function_type f){
  if (!pf || !pn) return -1;
  f(pf,pn);
}

Status tree_preOrderRec(FILE* f, NodeBT* pn, print_element_function_type p){
  if (!f || !pn) return ERROR;

  printNodeAB(f, pn, p);
  tree_preOrderRec(f, LEFT(pn), p);
  tree_preOrderRec(f, RIGHT(pn), p);

  return OK;
}

Status tree_inOrderRec(FILE* f, NodeBT* pn, print_element_function_type p){
  if (!f || !pn) return ERROR;

  tree_preOrderRec(f, LEFT(pn), p);
  printNodeAB(f, pn, p);
  tree_preOrderRec(f, RIGHT(pn), p);

  return OK;
}

Status tree_postOrderRec(FILE* f, NodeBT* pn, print_element_function_type p){
  if (!f || !pn) return ERROR;

  tree_preOrderRec(f, LEFT(pn), p);
  tree_preOrderRec(f, RIGHT(pn), p);
  printNodeAB(f, pn, p);
}



int tree_depthRec(NodeBT* pn){
  int right_depth, left_depth;

  if (!pn) return -1;
  if ((RIGHT(pn) == NULL) && (LEFT(pn) == NULL)) return 0;

  right_depth = 1 + tree_depthRec(RIGHT(pn));
  left_depth = 1 + tree_depthRec(LEFT(pn));

  if (right_depth > left_depth) {
    return right_depth;
  }

  return left_depth;
}


int tree_numNodesRec(NodeBT* pn){
  if (!pn) return 0;

  return 1 + tree_numNodesRec(LEFT(pn)) + tree_numNodesRec(RIGHT(pn));
}



NodeBT * lookABRec( NodeBT* pn, const void* po, cmp_element_function_type c){

  if (!pn || !po || !c) return NULL;

  if (pn->cmp_element_function(po, INFO(pn) == 0) return pn;
  if (pn->cmp_element_function(po, INFO(pn) > 0) return lookABRec(RIGHT(pn), po, c);

  return lookABRec(LEFT(pn), po, c);
}


NodeBT * lookAB (const Tree *pa, const void* po){

  if (!pa || !po) return NULL;
  return lookABRec (ROOT(pa), po, pa->cmp_element_function);

}



/* ----------------------- PRIMITIVE FUNCTIONS ----------------------- */


Tree* tree_ini(destroy_element_function_type f1, copy_element_function_type f2, print_element_function_type f3, cmp_element_function_type f4){

  Tree *tree = NULL;
  tree = (Tree *)malloc(sizeof(Tree));

  if (tree == NULL) {
    fprintf(stderr, "%s\n", strerror(errno));
    return NULL;
  }

  ROOT(tree) = NULL;

  tree->destroy_element_function = f1;
  tree->copy_element_function = f2;
  tree->print_element_function = f3;
  tree->cmp_element_function = f4;

  return tree;

}


Bool tree_isEmpty( const Tree *pa){

  if (pa == NULL) return TRUE;
  if (ROOT(pa) == NULL) return TRUE;

  return FALSE;

}


void tree_free(Tree *pa){

  if (!pa) return;

  tree_freeRec(ROOT(pa),pa->destroy_element_function);
  free(pa);

}


Status tree_insert(Tree *pa, const void *po){

  if (!pa || !po) return ERROR;

  return tree_insertRec(&ROOT(po), po, pa->copy_element_function, pa->cmp_element_function);

}


Status tree_preOrder(FILE *f, const Tree *pa){

  if (!f || !pa) return ERROR;
  if (tree_isEmpty(pa)) return ERROR;

  return tree_preOrderRec(f, ROOT(pa), pa->print_element_function);

}


Status tree_inOrder(FILE *f, const Tree *pa){

  if(!f || !pa) return ERROR;
  if (tree_isEmpty(pa)) return ERROR;

  return tree_inOrderRec(f, ROOT(pa), pa->print_element_function);

}


Status tree_postOrder(FILE *f, const Tree *pa){

  if(!f || !pa) return ERROR;
  if (tree_isEmpty(pa)) return ERROR;

  return tree_postOrderRec(f, ROOT(pa), pa->print_element_function);

}


int tree_depth(const Tree *pa){

  if (!pa) return -1;
  f (tree_isEmpty(pa)) return ERROR;

  return tree_depthRec(ROOT(pa));

}


int tree_numNodes(const Tree *pa){

  if (!pa) return -1;
  if (tree_isEmpty(pa)) return 0;

  return tree_numNodesRec(ROOT(pa));
}


Bool tree_find(Tree* pa, const void* pe){

  if (!pa || !pe) return FALSE;
  if (tree_isEmpty(pa)) return FALSE;

  if (lookAB(pa,pe) != NULL){
    return TRUE;
  }

  return FALSE;

}
