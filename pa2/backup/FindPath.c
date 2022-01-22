/*********************************************************************************
* Jason Bruni, jabruni
* 2022 Winter CSE101 PA1
* FindPath.c
* Client module for Graph ADT
*********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"List.h"
#include"Graph.h"

#define MAX_LEN 300

int main(int argc, char* argv[]) 
{
	FILE *in, *out;
	char line[MAX_LEN];
	int n = 0;
	
	// check command line for correct number of arguments
    if (argc != 3){
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }
	// open files for reading and writing
	in = fopen(argv[1], "r");
    if (in == NULL){
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }
	
	out = fopen(argv[2], "w");
    if (out == NULL){
        printf("Unable to open file %s for writingn\n", argv[2]);
        exit(1);
    }

// 1. Read and store graph and print out its
// adjacency list representation.	
    fgets(line, MAX_LEN, in);
	sscanf(line, "%d", &n);
	Graph G = newGraph(n);
    while (fgets(line, MAX_LEN, in) != NULL){
		int u = 0;
		int v = 0;
		sscanf(line, "%d %d", &u, &v);
		if(u==0 && v==0){
			break;
		}
		addEdge(G,u,v);
	}
	printGraph(out,G);

// 2. Enter a loop and process the second part of input.
// Each iteration of the loop should read in one pair
// of vertices (source, destination), run BFS on the
// source vertex, print the distance to the the destination
// vertex, then find and print out the resulting shortest
// path if it exists, or print a message if no path from
// source to destination exists.
   while(fgets(line, MAX_LEN, in) != NULL){
		int u=0;
		int v=0;
		sscanf(line, "%d %d", &u, &v);
		if(u==0 && v==0){
			break;
		}
		fprintf(out, "%s", "\n");
		BFS(G,u);
		if(getDist(G, v) == INF){
			fprintf(out, "The distance from %d to %d is infinity\n", u, v);
			fprintf(out, "No %d-%d path exists\n\n", u, v);
		}
		else{
			fprintf(out, "The distance from %d to %d is %d\n", u, v, getDist(G,v));
			List L = newList();
			getPath(L,G,v);
			fprintf(out, "A shortest %d-%d path is: ", u, v);
			printList(out,L);
			fprintf(out, "%s", "\n");
			freeList(&L);
		}
	}
	freeGraph(&G);
	fclose(in);
	fclose(out);
	return(0);
}