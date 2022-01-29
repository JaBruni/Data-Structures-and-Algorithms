/*********************************************************************************
* Jason Bruni, jabruni
* 2022 Winter CSE101 PA3
* FindComponents.c
* Client module for the Graph ADT
*********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"List.h"
#include"Graph.h"

#define MAX_LEN 300

int main(int argc, char* argv[]){
	FILE *in, *out;
	char line[MAX_LEN];
	int n = 0;
	
	// check command line for correct number of arguments
	if(argc != 3){
		fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
		exit(1);
	}
	
	// open files for reading and writing
	in = fopen(argv[1], "r");
	if(in == NULL){
		printf("Unable to open file %s for reading\n", argv[1]);
		exit(1);
	}
	
	out = fopen(argv[2], "w");
	if(out == NULL){
		printf("Unable to open file %s for writing\n", argv[2]);
		exit(1);
	}
	
	// Read the input file
	// Assemble a graph object G using newGraph() and addArc()
	// Print the adjacency list representation of G to the output file
	
		fgets(line, MAX_LEN, in);
		sscanf(line, "%d", &n);
		Graph G = newGraph(n);
		while(fgets(line,MAX_LEN, in) != NULL){
			int u = 0;
			int v = 0;
			sscanf(line, "%d %d", &u, &v);
			if(u==0 && v==0){
				break;
			}
			addArc(G,u,v);
		}
		fprintf(out, "Adjacency list representation of G:\n");
		printGraph(out,G);
		fprintf(out, "\n");
	
	// Run DFS on G and G^T, processing the vertices in the second call by decreasing finish times
	// from the first call.
	
	List S = newList();
	for(int i=1; i<=n; i++) append(S, i);
	Graph T = transpose(G);
	DFS(G, S);
	DFS(T, S);
	
	// Determine the strong components of G
	int count = 0;
	for(int i = 1; i <= getOrder(T); i++){
		if(getParent(T, i) == NIL){
			count++;
		}
	}
	fprintf(out, "G contains %d strongly connected components:\n", count);
	
	printList(stdout,S);
	
	// Print the strong components of G to the output file in topologically sorted order
	List sc = newList();
	if(length(S) > 0){
		moveBack(S);
		int x = 1;
		for(int i = 1; i <= length(S); i++){
			if(getParent(T, get(S)) == NIL){
				prepend(sc, get(S));
				fprintf(out, "Component %d: ", x);
				printList(out, sc);
				fprintf(out, "\n");
				clear(sc);
				x++;
			}
			else{
				prepend(sc, get(S));
			}
			movePrev(S);
		}
	}
	fprintf(out, "\n");
	freeList(&sc);
	freeList(&S);
	freeGraph(&G);
	freeGraph(&T);
	fclose(in);
	fclose(out);
	return(0);
}
