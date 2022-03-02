/*********************************************************************************
* Jason Bruni, jabruni
* 2022 Winter CSE101 PA4
* Graph.c
* Source file for Graph ADT
*********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include "List.h"
#include "Matrix.h"

//structs---------------------

// private Entry typedef
typedef struct EntryObj* Entry;

// private EntryObj type
typedef struct EntryObj{
	int column;
	double value;
}EntryObj;

// private MatrixObj
typedef struct MatrixObj{
	List* row;
	int matrixSize;
	int NNZ;
}MatrixObj;

// Constructors-Destructors-------------------

// newEntry()
Entry newEntry(int column, double value){
	Entry entry;
	entry = (Entry)malloc(sizeof(EntryObj));
	entry->column = column;
	entry->value = value;
	return(entry);
}

// freeEntry()
void freeEntry(Entry* pE){
	if(pE!=NULL && *pE!=NULL){
		free(*pE);
		*pE = NULL;
	}
}

// newMatrix()
// Returns a reference to a new nXn Matrix object in the zero state.
Matrix newMatrix(int n){
	Matrix M;
	M = malloc(sizeof(MatrixObj));
	M->row = calloc(n+1, sizeof(List*));
	M->matrixSize = n;
	M->NNZ = 0;
	for (int i = 1; i <= n; i++){
		M->row[i] = newList();
	}
	return M;
}

// freeMatrix()
// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix* pM){
	if(pM != NULL && *pM != NULL){
		for(int i = 1; i <= size(*pM); i++){
			if(length((*pM)->row[i]) != 0){
				moveFront((*pM)->row[i]);
				while(index((*pM)->row[i]) != -1){
					Entry entry = (Entry)get((*pM)->row[i]);
					freeEntry(&entry);
					moveNext((*pM)->row[i]);
				}
			}
		}
	}
	
	free(*pM);
	*pM = NULL;
	
}

// Access functions--------------------------------

// size()
// Return the size of square Matrix M.
int size(Matrix M){
	if(M == NULL){
		printf("Matrix error: cannot call size() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	return M->matrixSize;
}

// NNZ()
// Return the number of non-zero elements in M.
int NNZ(Matrix M){
	if(M == NULL){
		printf("Matrix error: cannot call NNZ() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	return M->NNZ;
}

// equals()
// Return true (1) if matrices A and B are equal, 
// false (0) otherwise.
int equals(Matrix A, Matrix B){
	int eq = 1;
	if(A == NULL || B==NULL){
		printf("Matrix Error: calling equals() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	eq = (A->matrixSize == B->matrixSize);
	for(int i = 1; i <= size(A); i++){
		if(length(A->row[i]) != 0 && length(B->row[i]) != 0){
			moveFront(A->row[i]);
			moveFront(B->row[i]);
			while(index(A->row[i]) != -1 && index(B->row[i]) != -1){
				Entry entryA = (Entry)get(A->row[i]);
				Entry entryB = (Entry)get(B->row[i]);
				if(entryA->value != entryB->value || NNZ(A) != NNZ(B)){
					eq = 0;
					break;
				}
				else{
					moveNext(A->row[i]);
					moveNext(B->row[i]);
				}
			}
		}
	}
	return eq;
}

// Manipulation procedures-------------------------------------	
	
// makeZero()
// Re-sets M to the zero Matrix state.
void makeZero(Matrix M){
	if(M == NULL){
		printf("Matrix Error: calling makeZero() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	M->NNZ = 0;
	for (int i = 1; i <= size(M); i++){
		M->row[i] = newList();
	}
}

// changeEntry()
// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x){
	if((i <= 1 && i >= M->matrixSize) || (j <= 1 && j >= M->matrixSize)){
		printf("Matrix Error: changeEntry() called with invalid argument\n");
		exit(EXIT_FAILURE);
	}
	if(length(M->row[i]) == 0){
		if(x != 0){
			Entry E = newEntry(j, x);
			append(M->row[i], E);
			M->NNZ++;
		}
	}
	else{
		moveFront(M->row[i]);
		for(int rows = 1; rows <= j; rows++){
			Entry entry = (Entry)get(M->row[i]);
			if(entry->column == j){
				if(x == 0){
					delete(M->row[i]);
					M->NNZ--;
					break;
				}
				else{
					entry->value = x;
					break;
				}
			}
			else if(entry->column > j){
				if(x == 0){
					break;
				}
				else{
					insertBefore(M->row[i], newEntry(j,x));
					M->NNZ++;
					break;
				}
			}
			else{
				moveNext(M->row[i]);
				if(index(M->row[i]) == -1){
					if(x == 0){
						break;
					}
					else{
						append(M->row[i], newEntry(j, x));
						M->NNZ++;
						break;
					}
				}
			}
		}
	}
}

// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A){
	if(A == NULL){
		printf("Matrix Error: calling scalarMult() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	Matrix M = newMatrix(A->matrixSize);
	for(int i = 1; i <= size(A); i++){
		if(length(A->row[i]) != 0){
			moveFront(A->row[i]);
			while(index(A->row[i]) != -1){
				Entry entry = (Entry)get(A->row[i]);
				double scalarMult = x * entry->value;
				changeEntry(M, i, entry->column, scalarMult);
				moveNext(A->row[i]);
			}
		}
	}
	return M;
}

// double vectorDot(List P, List Q)
// helper function for mult
double vectorDot(List P, List Q){
	double sum = 0;
	Entry eP, eQ;
	moveFront(P);
	moveFront(Q);
	while(index(P) != -1 && index(Q) != -1){
		eP = (Entry)get(P);
		eQ = (Entry)get(Q);
		if(eP->column < eQ->column){
			moveNext(P);
		}
		else if(eP->column > eQ->column){
			moveNext(Q);
		}
		else{
			sum += (eP->value * eQ->value);
			moveNext(P);
			moveNext(Q);
		}
	}
	return sum;
}

// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B){
	if(A==NULL || B==NULL){
		printf("Matrix Error: calling sum() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	if(size(A) != size(B)){
		printf("Matrix Error: calling sum() on unequal matrices\n");
		exit(EXIT_FAILURE);
	}
	if(B == A){
		return scalarMult(2, A);
	}
	Matrix S = newMatrix(size(A));
	for(int i = 1; i <= size(A); i++){
		List P = A->row[i];
		List Q = B->row[i];
		moveFront(P);
		moveFront(Q);
		while(index(P) != -1 && index(Q) != -1){
			Entry eP = (Entry)get(P);
			Entry eQ = (Entry)get(Q);
			if(eP->column == eQ->column){
				if(eP->value + eQ->value != 0){
					changeEntry(S, i, eP->column, (eP->value + eQ->value));
					moveNext(P);
					moveNext(Q);
				}
				else{
					moveNext(P);
					moveNext(Q);
				}
			}
			else if(eP->column < eQ->column){
				changeEntry(S, i, eP->column, eP->value);
				moveNext(P);
			}
			else{
				changeEntry(S, i, eQ->column, eQ->value);
				moveNext(Q);
			}
		}
		if(index(P) == index(Q)){
			continue;
		}
		List R = newList();
		if(index(P) > -1){
			R = P;
		}
		else{
			R = Q;
		}
		while(index(R) > -1){
			Entry eR = (Entry)get(R);
			changeEntry(S, i, eR->column, eR->value);
			moveNext(R);
		}
	}
	return S;
}

// diff()
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B){
	if(A==NULL || B==NULL){
		printf("Matrix Error: calling diff() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	if(size(A) != size(B)){
		printf("Matrix Error: calling diff() on unequal matrices\n");
		exit(EXIT_FAILURE);
	}
	Matrix D = newMatrix(size(A));
	if(A == B){
		return D;
	}
	for(int i = 1; i <= size(A); i++){
		List P = A->row[i];
		List Q = B->row[i];
		moveFront(P);
		moveFront(Q);
		while(index(P) != -1 && index(Q) != -1){
			Entry eP = (Entry)get(P);
			Entry eQ = (Entry)get(Q);
			if(eP->column == eQ->column){
				if(eP->value - eQ->value != 0){
					changeEntry(D, i, eP->column, (eP->value - eQ->value));
					moveNext(P);
					moveNext(Q);
				}
				else{
					moveNext(P);
					moveNext(Q);
				}
			}
			else if(eP->column < eQ->column){
				changeEntry(D, i, eP->column, eP->value);
				moveNext(P);
			}
			else{
				changeEntry(D, i, eQ->column, -eQ->value);
				moveNext(Q);
			}
		}
		List R = newList();
		if(index(P) > -1){
			R = P;
		}
		else{
			R = Q;
		}
		int sign;
		if(index(P) > -1){
			sign = 1;
		}
		else{
			sign = -1;
		}
		while (index(R) > -1){
			Entry eR = (Entry)get(R);
			changeEntry(D, i, eR->column, sign * eR->value);
			moveNext(R);
		}
	}
	return D;
}

// product
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B){
	if(A==NULL || B==NULL){
		printf("Matrix Error: calling product() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	if(size(A) != size(B)){
		printf("Matrix Error: calling product() on unequal matrices\n");
	}
	Matrix temp = transpose(B);
	Matrix P = newMatrix(size(A));
	for(int i = 1; i <= size(A); i++){
		if(length(A->row[i]) == 0){
			continue;
		}
		for(int j = 1; j <= size(temp); j++){
			if(length(temp->row[j]) == 0){
				continue;
			}
			else{
				double dotProd = vectorDot(A->row[i], temp->row[j]);
				if(dotProd != 0.0){
					changeEntry(P, i, j, dotProd);
				}
			}
		}
	}
	return P;
}
// copy()
// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A){
	if(A==NULL){
		printf("Matrix Error: calling copy() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	Matrix C = newMatrix(size(A));
	for (int i = 1; i <= size(A); i++){
		if(length(A->row[i]) > 0){
			moveFront(A->row[i]);
			while(index(A->row[i]) != -1){
				Entry entry = (Entry) get(A->row[i]);
				changeEntry(C, i, entry->column, entry->value);
				moveNext(A->row[i]);
			}
		}
	}
	return C;
}

// transpose()
// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A){
	if(A==NULL){
		printf("Matrix Error: calling transpose() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	Matrix T = newMatrix(A->matrixSize);
	for(int i = 1; i <= size(A); i++){
		if(length(A->row[i]) != 0){
			moveFront(A->row[i]);
			for(int j = 1; j <= length(A->row[i]); j++){
				if (index(A->row[i]) != -1){
					Entry entry = (Entry) get(A->row[i]);
					changeEntry(T, entry->column, i, entry->value);
					moveNext(A->row[i]);
				}
			}
		}
	}
	return T;
}

// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero row is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M){
	if(M == NULL){
		printf("Matrix error: calling printMatrix() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
	}
	for (int i = 1; i <= size(M); i++){
		if(length(M->row[i]) > 0){
			fprintf(out, "%d: ", i);
			moveFront(M->row[i]);
			while(index(M->row[i]) != -1){
				Entry entry = (Entry)get(M->row[i]);
				fprintf(out, "(%d, %.1f) ", entry->column, entry->value);
				moveNext(M->row[i]);
			}
			fprintf(out, "\n");
		}
	}
}	