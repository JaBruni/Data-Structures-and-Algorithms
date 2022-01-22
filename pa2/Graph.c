/*********************************************************************************
* Jason Bruni, jabruni
* 2022 Winter CSE101 PA2
* Graph.c
* Graph ADT source file
*********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"

#define WHITE 0
#define GRAY 1
#define BLACK 2

// private GraphObj type
typedef struct GraphObj{
	List* neighbors;
	int* color;
	int* parent;
	int* distance;
	int order; // number of vertices
	int size; // number of edges
	int source; // vertex source
}GraphObj;

// Constructors-Destructor-------------------

// newGraph()
// Returns a Graph pointing to a newly created GraphObj
// representing a graph having n vertices and no edges.
Graph newGraph(int n){
	Graph G;
	G = malloc(sizeof(GraphObj));
	G->neighbors = calloc(n+1, sizeof(List*));
	G->color = calloc(n+1, sizeof(int*));
	G->parent = calloc(n+1, sizeof(int*));
	G->distance = calloc(n+1, sizeof(int*));
	G->order = n;
	G->size = 0;
	G->source = NIL;
	
	for(int i = 1; i <= n ; i++){
		G->neighbors[i] = newList();
		G->color[i] = WHITE;
		G->parent[i] = NIL;
		G->distance[i] = INF;
		
	}
	return G;
}

// freeGraph()
// Frees all heap memory associated with Graph *pG, and sets *pG to NULL.
void freeGraph(Graph *pG){
	if(pG != NULL && *pG!= NULL){
		makeNull(*pG);
		free((*pG)->neighbors);
		free((*pG)->color);
		free((*pG)->parent);
		free((*pG)->distance);
	}
	free(*pG);
	*pG = NULL;
}

// Access functions-----------------------------

// getOrder()
// Returns Order of G
int getOrder(Graph G){
	if(G == NULL){
		printf("Graoh rror: calling getOrder() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	return G->order;
}

// getSize()
// Returns size of G
int getSize(Graph G){
	if(G == NULL){
		printf("Graph Error: calling getSize() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	return G->size;
}


// getSource()
// Returns the source vertex most recently used in function BFS(),
// or NIL if BFS() has not yet been called.
int getSource(Graph G){
	if(G == NULL){
		printf("Graph Error: calling getSource() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	return G->source;
}

// getParent()
// Returns the parent of vertex u in the Breadth-first tree created by BFS(),
// or NIL if BFS() has not yet been called.
// Pre: 1 <= u <= getOrder(G)
int getParent(Graph G, int u){
	if(G == NULL){
		printf("Graph Error: calling getParent() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	if(u < 1 || u > getOrder(G)){
		printf("Graph Error: calling getParent() on out of bounds vertex\n");
		exit(EXIT_FAILURE);
	}
	return G->parent[u];
}

// getDist()
// Returns the distance from the most recent BFS source to vertex u, or INF 
// if BFS() has not yet been called.
// Pre: 1 <= u <= getOrder(G)
int getDist(Graph G, int u){
	if(G == NULL){
		printf("Graph Error: calling getDist() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	if(u < 1 || u > getOrder(G)){
		printf("Graph Error: calling getDist() on out of bounds vertex\n");
		exit(EXIT_FAILURE);
	}
	return G->distance[u];
}

// getPath()
// Appends to the List L the vertices of a shortest path in G from source to u,
// or appends to L the value NIL if no such path exists.
// Pre: getSource(G) != NIL
// Pre: 1 <= u <= getOrder(G)
void getPath(List L, Graph G, int u){
	if(G == NULL){
		printf("Graph Error: calling getPath() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	if( u < 1 || u > getOrder(G)){
		printf("Graph error: calling getPath() on out of bounds vertex\n");
		exit(EXIT_FAILURE);
	}
	if(getSource(G) == NIL){
		printf("Graph error: calling getPath() when BFS() has not been called\n");
		exit(EXIT_FAILURE);
	}
	if(u == getSource(G)){
		append(L, getSource(G));
	}
	else if(G->parent[u] == NIL){
		append(L, NIL);
	}
	else{
		getPath(L, G, G->parent[u]);
		append(L, u);
	}
}

// Manipulation procedures-----------

// makeNull()
// deletes all edges of G, restoring it to its original(no edge)state.
void makeNull(Graph G){
	if(G == NULL){
		printf("Graph Error: calling makeNull() on Null Graph reference\n");
		exit(EXIT_FAILURE);
	}
	for (int i = 1; i <= getOrder(G); i++){
		freeList(&G->neighbors[i]);
	}
	G->size = 0;

}

// addEdge()
// Inserts a new edge joining u to v, i.e. u is added to the adjacency List
// of v, and v to the adjacency List of u. 
void addEdge(Graph G, int u, int v){
	if(G == NULL){
		printf("Graph Error: calling addEdge on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	if((u < 1 || u >getOrder(G)) && (v < 1 || v > getOrder(G))){
		printf("Graph Error: calling addEdge on out of bounds vertices\n");
		exit(EXIT_FAILURE);
	}
	else{
	addArc(G,u,v);
	addArc(G,v,u);
	G->size--;	
	}
}
	
// addArc()
// inserts a new directed edge from u to v, i.e. v is added to the 
// adjacency List of u (but not u to the adjacency List L of v).
void addArc(Graph G, int u, int v){
	if(G == NULL){
		printf("Graph Error: calling addEdge on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	if((u < 1 || u >getOrder(G)) && (v < 1 || v > getOrder(G))){
		printf("Graph Error: calling addArc on out of bounds vertices\n");
		exit(EXIT_FAILURE);
	}
	List neighbors = G->neighbors[u];
	if(length(neighbors) == 0 ) {
		append(G->neighbors[u],v);
	}
	else{
		int j = length(G->neighbors[u])-1;
		moveFront(neighbors);
		while(j >= 0 && get(neighbors) <= v ){
				moveNext(neighbors);
				j--;
			}
			if(index(neighbors) >= v){
 				insertBefore(neighbors,v);
 			}
 			else{
 				append(neighbors,v);
 			}
	}
	G->size++;
}

// BFS()
// Runs the BFS algorithm on the Graph G with source s, setting the color,
// distance, parent, and source fields of G accordingly.
void BFS(Graph G, int s){
	if(G==NULL){
		printf("Graph Error: calling BFS on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	for (int i = 1; i <= getOrder(G); i++) 
    {
        G->color[i] = WHITE;
        G->distance[i] = INF;
        G->parent[i] = NIL;
    }
    G->source = s;
    G->color[s] = GRAY; // discover the source of s
    G->distance[s] = 0;
    G->parent[s] = NIL;
    List L = newList();
    append(L, s);
    while(length(L) > 0) 
    {
		moveFront(L);
        int x = get(L);
        deleteFront(L);
		if(length(G->neighbors[x]) > 0){
			moveFront(G->neighbors[x]);
		}
		while(index(G->neighbors[x]) >= 0){
            int y = get(G->neighbors[x]);
            if (G->color[y] == WHITE) 
            {
                G->color[y] = GRAY;
                G->distance[y] = G->distance[x] + 1;
                G->parent[y] = x;
                append(L, y);
            }
            moveNext(G->neighbors[x]);
        }
        G->color[x] = BLACK;
    }
    freeList(&L);
	
}

// Other operations--------------------

// Prints the adjacency list representation of G to the file pointed by out.
void printGraph(FILE* out, Graph G){
	if(G == NULL){
		printf("Graph error: calling printGraph() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	for (int i= 1; i <= getOrder(G); i++){
		fprintf(out, "%d", i);
		fprintf(out, "%s", ": ");
		printList(out, G->neighbors[i]);
		fprintf(out, "%s", "\n");
	}
}

