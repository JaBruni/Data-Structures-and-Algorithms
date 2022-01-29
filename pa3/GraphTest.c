/*********************************************************************************
* Jason Bruni, jabruni
* 2022 Winter CSE101 PA3
* GraphTest.c
* Test client for Graph ADT
*********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include"List.h"
#include"Graph.h"


// int main(int argc, char* argv[]){
   // int i, n=8;
   // List S = newList();
   // Graph G = newGraph(n);
   // Graph T=NULL, C=NULL;

   // for(i=1; i<=n; i++) append(S, i);

   // addArc(G, 1,2);
   // addArc(G, 1,5);
   // addArc(G, 2,5);
   // addArc(G, 2,6);
   // addArc(G, 3,2);
   // addArc(G, 3,4);
   // addArc(G, 3,6);
   // addArc(G, 3,7);
   // addArc(G, 3,8);
   // addArc(G, 6,5);
   // addArc(G, 6,7);
   // addArc(G, 8,4);
   // addArc(G, 8,7);
   // printGraph(stdout, G);

   // DFS(G, S);
   // fprintf(stdout, "\n");
   // fprintf(stdout, "x:  d  f  p\n");
   // for(i=1; i<=n; i++){
      // fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(G, i), getFinish(G, i), getParent(G, i));
   // }
   // fprintf(stdout, "\n");
   // printList(stdout, S);
   // fprintf(stdout, "\n");

   // T = transpose(G);
   // C = copyGraph(G);
   // fprintf(stdout, "\n");
   // printGraph(stdout, C);
   // fprintf(stdout, "\n");
   // printGraph(stdout, T);
   // fprintf(stdout, "\n");

   // DFS(T, S);
   // fprintf(stdout, "\n");
   // fprintf(stdout, "x:  d  f  p\n");
   // for(i=1; i<=n; i++){
      // fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(T, i), getFinish(T, i), getParent(T, i));
   // }
   // fprintf(stdout, "\n");
   // printList(stdout, S);
   // fprintf(stdout, "\n");

   // freeList(&S);
   // freeGraph(&G);
   // freeGraph(&T);
   // freeGraph(&C);
   // return(0);
// }

int main(int argc, char* argv[]){
	Graph G = newGraph(8);
	List S = newList();
	for(int i = 1; i <= 8; i++) append(S,i);
	addEdge(G,1,2);
	addEdge(G,1,3);
	addEdge(G,2,4);
	addEdge(G,2,5);
	addEdge(G,2,6);
	addEdge(G,3,4);
	addEdge(G,4,5);
	addEdge(G,5,6);
	addEdge(G,5,1);
	addEdge(G,6,7);
	addEdge(G,7,8);
	addEdge(G,8,6);
	
	printGraph(stdout,G);
	fprintf(stdout, "\n");
	fprintf(stdout, "DFS: \n");
	DFS(G,S);
	fprintf(stdout, "\n");
	fprintf(stdout, "x:  d  f  p\n");
	for (int i = 1; i <= 8; i++){
		fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(G, i), getFinish(G, i), getParent(G, i));
	}
	fprintf(stdout, "\n");
	printList(stdout, S);
	fprintf(stdout, "\n");
	
	addArc(G,1,2);
	addArc(G,2,3);
	addArc(G,2,5);
	addArc(G,2,6);
	addArc(G,3,4);
	addArc(G,3,7);
	addArc(G,4,3);
	addArc(G,4,8);
	addArc(G,5,1);
	addArc(G,5,6);
	addArc(G,6,7);
	addArc(G,7,6);
	addArc(G,7,8);
	addArc(G,8,8);
	
	Graph T = transpose(G);
	Graph C = copyGraph(G);
	fprintf(stdout,"\n");
	printGraph(stdout, C);
	fprintf(stdout,"\n");
	printGraph(stdout, T);
	fprintf(stdout,"\n");
	
	fprintf(stdout, "DFS Transpose: \n");
	DFS(T, S);
	fprintf(stdout,"\n");
	fprintf(stdout, "x:  d  f  p\n");
	for (int i = 1; i <= 8; i++){
		fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(T, i), getFinish(T, i), getParent(T, i));
	}
	
	freeList(&S);
	freeGraph(&G);
	freeGraph(&T);
	freeGraph(&C);
	
	
	// makeNull(G);
	
	
	return(0);
}
