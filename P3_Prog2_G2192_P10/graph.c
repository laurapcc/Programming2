/*
 * File:   graph.c
 * Author: Paula Samper, Laura de Paz
 */


#include "graph.h"

#define MAX_NODES 4096
#define MAX_LINE 256

enum {NO_FILE_POS_VALUE = 2};

struct _Graph {
    Node *nodes[MAX_NODES];
    int num_nodes;
    Bool connections[MAX_NODES][MAX_NODES];
    int num_edges;
};


/*------------------private functions-----------------*/

int find_node_index(const Graph * g, int nId1) {
    int i;
    if (!g) return -1;
    for (i = 0; i < g->num_nodes; i++) {
        if (node_getId(g->nodes[i]) == nId1) return i;
    }
    /* ID not found*/
    return -1;
}

int *graph_getConectionsIndex(const Graph * g, int index) {
  int *array = NULL, i, j = 0, size;
  if (!g) return NULL;
  if (index < 0 || index > g->num_nodes) return NULL;
  /* get memory for the array with the connected nodes index*/
  size = node_getConnect(g->nodes[index]);
  array = (int *) malloc(sizeof (int) * size);
  if (!array) {
    /* print errorr message*/
    fprintf(stderr, "%s\n", strerror(errno));
    return NULL;
  }
  /* assign values to the array with the indexes of the connected nodes*/
  for (i = 0; i < g->num_nodes; i++) {
    if (g->connections[index][i] == TRUE) {
      array[j] = i;
      j++;
    }
  }
  return array;
}


Node *graph_findDeepSearch (Graph *g, int from_id, int to_id){
  /*Initialize variables*/
  Queue *q = NULL;
  Node *u = NULL;
  Node *w = NULL;
  Node *v = NULL;
  int i, con_u, *con_ids = NULL;
  Bool found = FALSE;

  /*Error control*/
  if (!g) return NULL;

  q = queue_ini(node_destroy,node_copy,node_print);
  v = graph_getNode(g, from_id);

  if (!q || !v) return NULL;

  queue_insert(q, (void *)v);
  while (queue_isEmpty(s) == FALSE && found == FALSE){
    u = (Node *)queue_extract(q);

    if (node_getLabel(u) == WHITE){
      u = node_setLabel(u,BLACK);
      graph_setNode(g,u);
      con_ids = graph_getConnectionsFrom(g,node_getId(u)); /* ids de conexiones del nodo*/
      con_u = node_getConnect(u);

      for (i = 0; i < con_u; i++){
         w = graph_getNode(g,con_ids[i]);

        if(con_ids[i] == to_id){
          w = node_setAntecesorId(w,node_getId(u));
          graph_setNode(g,w);
          found = TRUE;
          break;
        }

        else if (node_getLabel(w) == WHITE){
          w = node_setAntecesorId(w,node_getId(u)); /* set antecesor*/
          graph_setNode(g,w);
          queue_insert(q,(void *)w);
        }

        node_destroy(w);
        w = NULL;
      }

      free(con_ids);
      con_ids = NULL;
    }

    node_destroy(u);
  }

  node_destroy(v);
  queue_destroy(s);
  return w;
}


void graph_printPath (FILE *pf, Graph *g, int idNode){
  Node *n;
  int index, ant;
  if (!pf || !g || idNode == -1){
    return;
  }
  n = graph_getNode (g,idNode);
  index = find_node_index(g,idNode);
  ant = node_getAntecesorId(g->nodes[index]);
  node_print(pf,n);
  graph_printPath(pf,g,ant);
  node_destroy(n);
}



/*------------------primtive functions-----------------*/

Graph * graph_ini() {
  Graph *g = NULL;
	int i,j;
    if (!(g = (Graph *)malloc(sizeof (Graph)))) {
      fprintf(stderr, "%s\n",strerror(errno));
      return NULL;
  }

  g->num_edges = 0;
  g->num_nodes = 0;

  for(i = 0;i < MAX_NODES; i++){
    g->nodes[i] = NULL;
    for (j = 0;j < MAX_NODES; j++){
	    g->connections[i][j] = FALSE;
	  }
  }

  return g;
}


void graph_destroy (Graph *g) {
  int i;
  for (i = 0;i < MAX_NODES;i++){
    node_destroy(g->nodes[i]);
  }
  free(g);
}


Status graph_insertNode(Graph *g, const Node *n){
  Node *aux = NULL;
  int id, i;
  if(!g || !n) return ERROR;

  id = node_getId(n);
  if (find_node_index(g,id) != -1) return ERROR; /*There's already a node with that id in the graph g*/

  aux = node_copy(n);
  if(!aux) return ERROR;

  node_setConnect(aux,0);

  g->nodes[g->num_nodes] = aux;
  g->num_nodes ++;

  for (i = 0;i < g->num_nodes;i++){
    g->connections[i][g->num_nodes] = FALSE;
    g->connections[g->num_nodes][i] = FALSE;
  }

  return OK;

}


Status graph_insertEdge(Graph * g, const int nId1, const int nId2){
    int from, to, conn;
    if(!g) return ERROR;

    from = find_node_index(g, nId1);
    to = find_node_index(g, nId2);
    if (from == -1 || to == -1) return ERROR;

    g->connections[from][to] = TRUE;

    conn = node_getConnect(g->nodes[from]) + 1;
    node_setConnect(g->nodes[from], conn);

    g->num_edges++;

    return OK;

}


Node *graph_getNode(const Graph *g, int nId){
  int i;
  Node *n = NULL;

  if (!g){
    fprintf(stderr, "%s\n", strerror(errno));
    return NULL;
  }

  for (i = 0; i < g->num_nodes; i++){
    if (node_getId(g->nodes[i]) == nId){
      n = node_copy(g->nodes[i]);
      break;
    }
  }

  if (!n) {
    fprintf(stderr, "%s\n", strerror(errno));
    return NULL;
  }

  return n;
}


Status graph_setNode(Graph *g, const Node * n){
	int index;
  Node *aux;
	index = find_node_index(g, node_getId(n));
  if (!g || !n || index < 0) return ERROR;

	aux = node_copy(n);
  if (!aux) return  ERROR;

  node_destroy(g->nodes[index]);
  g->nodes[index] = aux;

  return OK;

}


int *graph_getNodesId(const Graph *g){
    int *array = NULL;
    int i;
    if (!g) return NULL;

    array = (int *)malloc(g->num_nodes*sizeof(int));
    if (!array){
        fprintf(stderr,"%s\n",strerror(errno));
        return NULL;
    }

    for (i = 0; i < g->num_nodes; i++){
        array[i] = node_getId(g->nodes[i]);
    }

    return array;

}


int graph_getNumberOfNodes(const Graph * g){
    if(!g) return -1;
    return g->num_nodes;

}


int graph_getNumberOfEdges(const Graph * g){
    if(!g) return -1;
    return g->num_edges;

}


Bool graph_areConnected(const Graph * g, const int nId1, const int nId2){
    int index1 = find_node_index(g, nId1);
    int index2 = find_node_index(g, nId2);
    if(!g || index1 == -1 || index2 == -1)  return FALSE;

    if ((g->connections[index1][index2])==1) return TRUE;
    return FALSE;

}


int graph_getNumberOfConnectionsFrom(const Graph * g, const int fromId){
    int counter = 0, i;
    if (!g) return -1;
    for(i=0;  i<(g->num_nodes);i++){
        if (g->connections[fromId][i] == 1) counter ++;
        if (g->connections[i][fromId] == 1) counter ++;
    }

    return counter;

}


int *graph_getConnectionsFrom(const Graph * g, const int fromId){
    int *idNodes = NULL, *idConn = NULL;
    Node *n = NULL;
    int i, j = 0, nNodes;

    if (!g){
      fprintf(stderr, "%s\n", strerror(errno));
      return NULL;
    }

    for (i = 0; i < g->num_nodes; i++){
        if(node_getId(g->nodes[i]) == fromId){
            n = node_copy(g->nodes[i]);
            break;
        }
    }

    if (!n){
      fprintf(stderr, "%s\n", strerror(errno));
      return NULL;
    }

    nNodes = graph_getNumberOfNodes(g);
    idNodes = graph_getNodesId(g);

    if (nNodes == -1 || !idNodes){
      fprintf(stderr, "%s\n", strerror(errno));
      return NULL;
    }

    idConn = (int *)malloc(nNodes * sizeof(int));
    if (!idConn){
      fprintf(stderr, "%s\n", strerror(errno));
      return NULL;
    }

    for (i = 0; i < nNodes; i++){
      if (graph_areConnected(g, fromId, node_getId(g->nodes[i])) == TRUE){
        idConn[j] = node_getId(g->nodes[i]);
        j++;
      }
    }

    node_destroy(n);
    free(idNodes);
    return idConn;


}


int graph_print(FILE *pf, const Graph * g) {
    int numcar = 0, i, j;
    int *array = NULL;
    if (!pf || !g){
        fprintf(stderr, "%d",errno);
        return -1;
    }

    for (i=0; i<g->num_nodes; i++){
        numcar += fprintf(pf, "[%d, %s, %d]", node_getId(g->nodes[i]), node_getName(g->nodes[i]), node_getConnect(g->nodes[i]));
        array = graph_getConectionsIndex(g, i);

        for (j=0; j<node_getConnect(g->nodes[i]); j++){
          numcar += fprintf(pf, "%d ", node_getId(g->nodes[array[j]]));
        }

        fprintf(pf, "\n");
		    free(array);
        numcar--;
    }

    if (numcar<0) fprintf(stderr, "%s\n", strerror(errno));
    return numcar;
}


Status graph_readFromFile(FILE *fin, Graph * g){ /* from appendix 5*/
    Node *n;
    char buff[MAX_LINE], name[MAX_LINE];
    int i, nnodes = 0, id1, id2;
    Status flag = ERROR;

    /* read number of nodes*/
    if (fgets (buff, MAX_LINE, fin) != NULL){
        if (sscanf(buff, "%d", &nnodes) != 1) return ERROR;
    }

    /* init buffer_node*/
    n = node_ini();
    if (!n) return ERROR;

    /* read nodes line by line*/
    for(i=0; i < nnodes; i++) {
        if (fgets(buff, MAX_LINE, fin) != NULL){
            if (sscanf(buff, "%d %s", &id1, name) != NO_FILE_POS_VALUE) break;
        }
        /* set node name and node id*/
        node_setName (n, name);
        node_setId (n, id1);

        /* insert node in the graph*/
        if (graph_insertNode (g, n) == ERROR) break;
    }

    /* Check if all node have been inserted*/
    if (i < nnodes) {
        node_destroy(n);
        return ERROR;
    }

    /* read connections line by line and insert it*/
    while (fgets(buff, MAX_LINE, fin) ) {
        if (sscanf(buff, "%d %d", &id1, &id2) == NO_FILE_POS_VALUE ) if (graph_insertEdge(g, id1, id2) == ERROR) break;
    }

    /* check end of file*/
    if (feof(fin)) flag = OK;

    /* clean up, free resources*/
    node_destroy (n);
    return flag;

}
