/*
 * File:   main.c
 * Author: Paula Samper, Laura de Paz
 */


#include "graph.h"

#define MAX_NODES 4096
#define MAX_LINE 256

//extern int errno;



enum {NO_FILE_POS_VALUE = 2};

struct _Graph {
    Node *nodes[MAX_NODES];
    int num_nodes;
    Bool connections[MAX_NODES][MAX_NODES];
    int num_edges;
};


//------------------private functions-----------------

int find_node_index(const Graph * g, int nId1) {
    int i;
    if (!g) return -1;
    for (i = 0; i < g->num_nodes; i++) {
        if (node_getId(g->nodes[i]) == nId1) return i;
    }
    // ID not find
    return -1;
}

int *graph_getConectionsIndex(const Graph * g, int index) {
    int *array = NULL, i, j = 0, size;
    if (!g) return NULL;
    if (index < 0 || index > g->num_nodes) return NULL;
    // get memory for the array with the connected nodes index
    size = node_getConnect(g->nodes[index]);
    array = (int *) malloc(sizeof (int) * size);
    if (!array) {
        // print errorr message
        fprintf(stderr, "%s\n", strerror(errno));
        return NULL;
    }
    // assign values to the array with the indexes of the connected nodes
    for (i = 0; i < g->num_nodes; i++) {
        if (g->connections[index][i] == TRUE) {
            array[j] = i;
            j++;
        }
    }
    return array;
}
 /*
Node *graph_findDeepSearch (Graph *g, Node *v, Node *to){
    Stack *s = NULL;
    s = stack_ini((void *)node_destroy,(void *)node_copy, (void *)node_print);
    Node *u = NULL *w = NULL;
    int ind_u,i,*con_ids;

    if (!s || !g || !v || !to){
      fprintf(stderr, "%s\n", strerror(errno));
      return NULL;
    }

    stack_push(s,(void *)v);
    while (stack_isEmpty(s) == FALSE){
      u = (Node *)stack_pop(s);
      if (node_getLabel(u) == WHITE){
        u = node_setLabel(u,BLACK);
        graph_setNode(g,u);
        con_ids = graph_getConnectionsFrom(g,node_getId(u));
        for (i = 0; i < graph_getNumberOfConnectionsFrom(g,node_getId(u)); i++){
          w = graph_getNode(g,con_ids[i]);
          if(node_cmp(node_getId(w),node_getId(to)) == TRUE){
            w = node_setAntecesorId(w,node_getId(u));
            graph_setNode(g,w);
            break;
          }

          if (node_getLabel(w) == WHITE){
            w = node_setAntecesorId(w,node_getId(u));
            graph_setNode(g,w);
            stack_push(s,(void *)w);
          }
          node_destroy(w);
          w = NULL;
        }
        free(con_ids);
        con_ids = NULL;
      }

      if (node_getLabel(u) != WHITE){
        node_destroy(u);
        u = NULL;
      }
    }
    stack_destroy(s);
    return w;
}
*/



Node *graph_findDeepSearch (Graph *g, int from_id, int to_id){
//Node *graph_findDeepSearch (Graph *g, Node *v, Node *to){ ( adapt)

  // crea e inicializa el stack
  Stack *s = NULL;
  s = stack_ini((void *)node_destroy,(void *)node_copy, (void *)node_print);
  // crea dos nodos
  Node *u = NULL, *w = NULL;

  // creo v ini(adapt)
  Node *v = graph_getNode(g, from_id);
  Node *to = graph_getNode(g, to_id);


  // inicializa int
  int ind_u, i, *con_ids;
  // control de errores
  if (!s || !g || !v || !to){
    fprintf(stderr, "%s\n", strerror(errno));
    return NULL;
  }

  // metes v (inicial) en el stack
  stack_push(s,(void *)v);

    while (stack_isEmpty(s) == FALSE){ // ¿Cuándo guardas todo el path en el stack?
      // u es el nodo que vas sacando, lo cambias a negro, guardas cambios
      u = (Node *)stack_pop(s);
      if (node_getLabel(u) == WHITE){
        u = node_setLabel(u,BLACK);
        graph_setNode(g,u);

        con_ids = graph_getConnectionsFrom(g,node_getId(u)); // num de conexiones del nodo

        for (i = 0; i < graph_getNumberOfConnectionsFrom(g,node_getId(u)); i++){
          w = graph_getNode(g,con_ids[i]); // copia de los nodos conectados

          if(node_cmp(w,to) == TRUE){
          //if(node_cmp(node_getId(w),node_getId(to)) == TRUE){ // si = nodo final, set antecesor y fin (adapt)

            w = node_setAntecesorId(w,node_getId(u));
            graph_setNode(g,w);
            break;
          }

          if (node_getLabel(w) == WHITE){
            w = node_setAntecesorId(w,node_getId(u)); // set antecesor
            graph_setNode(g,w);
            stack_push(s,(void *)w); // meter en el stack
          }
          node_destroy(w);
          w = NULL;
        }
        free(con_ids);
        con_ids = NULL;
      }

      if (node_getLabel(u) != WHITE){
        node_destroy(u);
        u = NULL;
      }
    }


    //adapt
    node_destroy(v);
    node_destroy(to);


    stack_destroy(s);
    return w;
}


void graph_printPath (FILE *pf, Graph *g, int idNode){
  Node *n = NULL, *na = NULL;
  int antecessor;
  if (!pf || !g || idNode == -1){
    fprintf(stderr, "%s\n", strerror(errno));
    return;
  }
  n = graph_getNode(g,idNode);
  antecessor = node_getAntecesorId(n);
  na = graph_getNode(g,antecessor);
  if (antecessor != -1){
    fprintf(pf, "%d\n",node_getId(n));
    graph_printPath(pf,g,antecessor);
  }
  node_destroy(n);
  node_destroy(na);
}



//------------------primtive functions-----------------

Graph * graph_ini() {
    Graph *g = NULL;
	int i,j;
    if (!(g = (Graph *)malloc(sizeof (Graph)))) {
        fprintf(stderr, "Graph cannot be initialized");
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
    for (int i = 0;i < MAX_NODES;i++) node_destroy(g->nodes[i]);
    free(g);
}


Status graph_insertNode(Graph *g, const Node *n){
    if(!g || !n) return ERROR;

    Node *aux = NULL;
    int id = node_getId(n), i;
    if (find_node_index(g,id) != -1) return ERROR; //There's already a node with that id in the graph g

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

/* Adds an edge between the nodes of id "nId1" and "nId2".
 * Updates the necessary graph’s attributes.
 * Returns OK or ERROR. */
Status graph_insertEdge(Graph * g, const int nId1, const int nId2){
    if(!g) return ERROR;
    int from, to;

    from = find_node_index(g, nId1);
    to = find_node_index(g, nId2);
    if (from == -1 || to == -1) return ERROR;

    g->connections[from][to] = TRUE;

    int conn = node_getConnect(g->nodes[from]) + 1;
    node_setConnect(g->nodes[from], conn);

    g->num_edges++;

    return OK;

}

/* Returns a copy of the node of id "nId"*/
Node *graph_getNode(const Graph *g, int nId){
	int index;
	index = find_node_index(g, nId);
    if (!g || index == -1) return NULL;

    return node_copy(g->nodes[index]);
}

/* Actualize the graph node with the same id */
Status graph_setNode(Graph *g, const Node * n){
	int index;
	index = find_node_index(g, node_getId(n));
    if (!g || !n || index < 0) return ERROR;

    Node *aux;
	aux = node_copy(n);
    if (!aux) return  ERROR;

    node_destroy(g->nodes[index]);
    g->nodes[index] = aux;

    return OK;

}

/* Returns the address of an array with the ids of all nodes in the graph.
 * Reserves memory for the array. */
int *graph_getNodesId(const Graph *g){
    if (!g) return NULL;

    int *array;
    array = (int *)malloc(g->num_nodes*sizeof(int));
    if (!array){
        fprintf(stderr,"%s\n",strerror(errno));
        return NULL;
    }

    for (int i = 0; i < g->num_nodes; i++){
        array[i] = node_getId(g->nodes[i]);
    }

    return array;

}

/* Returns the number of nodes in the graph. -1 if there have been errors */
int graph_getNumberOfNodes(const Graph * g){
    if(!g) return -1;
    return g->num_nodes;

}

/* Returns the number of edges of the graph. -1 if there have been errors */
int graph_getNumberOfEdges(const Graph * g){
    if(!g) return -1;
    return g->num_edges;

}

/* Determines if two nodes are connected */
Bool graph_areConnected(const Graph * g, const int nId1, const int nId2){
    int index1 = find_node_index(g, nId1);
    int index2 = find_node_index(g, nId2);
    if(!g || index1 == -1 || index2 == -1)  return FALSE;

    if ((g->connections[index1][index2])==1) return TRUE;
    return FALSE;

}

/* Returns the number of connections from the id node fromId */
int graph_getNumberOfConnectionsFrom(const Graph * g, const int fromId){
    if (!g) return -1;
    int counter = 0;
    for(int i=0;  i<(g->num_nodes);i++){
        if (g->connections[fromId][i] == 1) counter ++;
        if (g->connections[i][fromId] == 1) counter ++;
    }

    return counter;

}


/* Returns the address of an array with the ids of all nodes in the graph.
 * Reserves memory for the array.*/
int *graph_getConnectionsFrom(const Graph * g, const int fromId){
    if (!g) return NULL;

    int *array;
    array = (int *)malloc(g->num_nodes*sizeof(int));
    if (!array){
        fprintf(stderr,"Error\n");
        return NULL;
    }

    for (int i = 0, j = 0; i < g->num_nodes; i++){
        if(g->connections[fromId][node_getId(g->nodes[i])] == 1){
            array[j] = node_getId(g->nodes[i]);
            j++;
        }

    }
    return array;


}

/* Prints in the flow pf the data of a graph, returning the number of printed
 characters.
 * Checks if there have been errors in the Output flow. If so, prints Error
 * message Error in stderror and returns the value -1.
 * The format to be followed is: print a line by node with the information
 associated with the node and
 * the id of their connections. The Output for the graph of the EXERCISE 2.3 of
 *part 1 is:
 * [1id, aname, 2nconnect] 2 3
 * [2, b, 2] 1 3
 * [3, c, 2]] 1 2 */
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
        for (j=0; j<node_getConnect(g->nodes[i]); j++) numcar += fprintf(pf, "%d ", node_getId(g->nodes[array[j]]) );
        fprintf(pf, "\n");
		free(array);
        numcar--;
    }

    if (numcar<0)
        fprintf(stderr, "%s\n", strerror(errno));
    return numcar;
}

// Read from the stream fin the graph information
Status graph_readFromFile(FILE *fin, Graph * g){ // from appendix 5
    Node *n;
    char buff[MAX_LINE], name[MAX_LINE];
    int i, nnodes = 0, id1, id2;
    Status flag = ERROR;
    // read number of nodes
    if (fgets (buff, MAX_LINE, fin) != NULL){
        if (sscanf(buff, "%d", &nnodes) != 1) return ERROR;
    }

    // init buffer_node
    n = node_ini();
    if (!n) return ERROR;

    // read nodes line by line
    for(i=0; i < nnodes; i++) {
        if (fgets(buff, MAX_LINE, fin) != NULL){
            if (sscanf(buff, "%d %s", &id1, name) != NO_FILE_POS_VALUE) break;
        }
            // set node name and node id
        node_setName (n, name);
        node_setId (n, id1);
            // insert node in the graph
        if (graph_insertNode (g, n) == ERROR) break;
    }

    // Check if all node have been inserted
    if (i < nnodes) {
        node_destroy(n);
        return ERROR;
    }


    // read connections line by line and insert it
    while (fgets(buff, MAX_LINE, fin) ) {
        if (sscanf(buff, "%d %d", &id1, &id2) == NO_FILE_POS_VALUE ) if (graph_insertEdge(g, id1, id2) == ERROR) break;
    }

    // check end of file
    if (feof(fin)) flag = OK;

    // clean up, free resources
    node_destroy (n);
    return flag;

}
