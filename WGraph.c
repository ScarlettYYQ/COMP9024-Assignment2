// Weighted Directed Graph ADT
// Adjacency Matrix Representation ... COMP9024 18s2
#include "WGraph.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
extern List L;//Reference external variable
typedef struct GraphRep {
   int **edges;  // adjacency matrix storing positive weights
		 // 0 if nodes not adjacent
   int nV;       // #vertices
   int nE;       // #edges
} GraphRep;

//time complexity is O(n),The highest time complexity is a for loop.
Graph newGraph(int V) {
   assert(V >= 0);
   int i;
   Graph g = malloc(sizeof(GraphRep));
   assert(g != NULL);
   g->nV = 1;
   g->nE = 0;
   // allocate memory for each row
   g->edges = malloc((V) * sizeof(int *));
   assert(g->edges != NULL);
   L=insertLL(L,V);//make a linked list with all vertices
   for(i = V/2; i >= 1; i--){
      if (V % i==0){
         g->edges[i-1] = calloc((V), sizeof(int));
         assert(g->edges[i-1] != NULL);
         L=insertLL(L,i);//make a linked list with all vertices
         g->nV++;
      }
   }
   g->edges[V-1] = calloc(V, sizeof(int));
   assert(g->edges[V-1] != NULL);
   return g;
}

int numOfVertices(Graph g) {
   return g->nV;
}

// check if vertex is valid in a graph
int validV(Graph g, Vertex v) {
   return (g != NULL && v >= 0);
}

void insertEdge(Graph g, Edge e) {
   assert(g != NULL && validV(g,e.v) && validV(g,e.w));
   g->edges[e.v][e.w] = e.weight;
   g->nE++;
}

void removeEdge(Graph g, Edge e) {
   assert(g != NULL && validV(g,e.v) && validV(g,e.w));

   if (g->edges[e.v][e.w] != 0) {   // edge e in graph
      g->edges[e.v][e.w] = 0;
      g->nE--;
   }
}

int adjacent(Graph g, Vertex v, Vertex w) {
   assert(g != NULL && validV(g,v) && validV(g,w));

   return g->edges[v][w];
}

void showGraph(Graph g) {
    assert(g != NULL);
    int i, j;

    printf("Number of vertices: %d\n", g->nV);
    printf("Number of edges: %d\n", g->nE);
    for (i = 0; i < g->nV; i++)
       for (j = 0; j < g->nV; j++)
	  if (g->edges[i][j] != 0)
	     printf("Edge %d - %d: %d\n", i, j, g->edges[i][j]);
}

void freeGraph(Graph g) {
   assert(g != NULL);

   List i;
   for (i = L;i!=NULL; i=i->next)
      free(g->edges[i->v-1]);
   free(g->edges);
   free(g);
}
