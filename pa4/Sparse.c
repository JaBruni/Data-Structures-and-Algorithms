/*********************************************************************************
* Jason Bruni, jabruni
* 2022 Winter CSE101 PA4
* Sparse.c
* Client for Matrix ADT 
*********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"List.h"
#include"Matrix.h"

#define MAX_LEN 300


int main(int argc, char* argv[]){
	FILE *in, *out;
	char line[MAX_LEN];
	int n = 0;
	int a = 0;
	int b = 0;
	char ch;
	Matrix A = NULL;
	Matrix B = NULL;
	Matrix SC = NULL;
	Matrix S = NULL;
	Matrix I = NULL;
	Matrix D = NULL;
	Matrix ID = NULL;
	Matrix T = NULL;
	Matrix P = NULL;
	Matrix IP = NULL;
	
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
	fgets(line, MAX_LEN, in);
	sscanf(line, "%d %d %d", &n, &a, &b);
	fgets(line, MAX_LEN, in);
	sscanf(line, " %c", &ch);
	A = newMatrix(n);
	B = newMatrix(n);
	while(fgets(line, MAX_LEN, in) != NULL){
		int rowA = 0;
		int colA = 0;
		double valA = 0;
		if(line[0] != '\r' && line[0] != '\n'){
			for (int i = 1; i <= a; i++){
			sscanf(line, "%d %d %lf", &rowA, &colA, &valA);
			changeEntry(A, rowA, colA, valA);
			}
		}
		else{
			break;
		}
	}
	
	while(fgets(line, MAX_LEN, in) != NULL){
		int rowB = 0;
		int colB = 0;
		double valB = 0;
		if(line[0] != '\r' && line[0] != '\n'){
			for( int i = 1; i <= b; i++){
				sscanf(line, "%d %d %lf", &rowB, &colB, &valB);
				changeEntry(B, rowB, colB, valB);
			}
		}
	}
	fprintf(out, "A has %d non-zero entries:\n", a);
	printMatrix(out, A);
	fprintf(out, "\n");
	
	fprintf(out, "B has %d non-zero entries:\n", b);
	printMatrix(out, B);
	fprintf(out, "\n");
	
	fprintf(out, "(1.5)*A = \n");
	SC = scalarMult(1.5, A);
	printMatrix(out, SC);
	fprintf (out, "\n");
	
	fprintf(out, "A+B = \n");
	S = sum(A, B);
	printMatrix(out, S);
	fprintf (out, "\n");
	
	fprintf(out, "A+A = \n");
	I = sum(A,A);
	printMatrix(out, I);
	fprintf (out, "\n");
	
	fprintf(out, "B-A = \n");
	D = diff(B, A);
	printMatrix(out, D);
	fprintf(out, "\n");
	
	fprintf(out, "A-A = \n");
	ID = diff(A, A);
	printMatrix(out, ID);
	fprintf(out, "\n");
	
	fprintf(out, "Transpose(A) = \n");
	T = transpose(A);
	printMatrix(out, T);
	fprintf (out, "\n");
	
	fprintf(out, "A*B = \n");
	P = product(A, B);
	printMatrix(out, P);
	fprintf(out, "\n");
	
	fprintf(out, "B*B = \n");
	IP = product(B, B);
	printMatrix(out, IP);
	fprintf(out, "\n");
	
	freeMatrix(&A);
	freeMatrix(&B);
	freeMatrix(&SC);
	freeMatrix(&I);
	freeMatrix(&D);
	freeMatrix(&ID);
	freeMatrix(&T);
	freeMatrix(&P);
	freeMatrix(&IP);
	fclose(in);
	fclose(out);
	return(0);
}
