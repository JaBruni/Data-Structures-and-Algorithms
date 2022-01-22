/*********************************************************************************
* Jason Bruni, jabruni
* 2022 Winter CSE101 PA2
* List.c
* List ADT source file
*********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "List.h"

// structs--------------------------

// private Node type
typedef struct NodeObj* Node;

// private NodeObj type
typedef struct NodeObj{
	int data;
	Node next;
	Node prev;
}NodeObj;

// private ListObj type
typedef struct ListObj{
	Node front;
	Node back;
	Node cursor;
	int length;
	int index;
} ListObj;

// Constructors-Destructors-------------------------

// newNode()
Node newNode(int data){
	Node N = malloc(sizeof(NodeObj));
	N->data = data;
	N->next = NULL;
	N->prev = NULL;
	return(N);
}

// freeNode()
void freeNode(Node* pN){
	if( pN!=NULL && *pN!=NULL ) {
		free(*pN);
		*pN = NULL;
	}
}

// newList()
// Returns reference to new empty List object
List newList(){
	List L;
	L = malloc(sizeof(ListObj));
	L->front = L->back = NULL;
	L->cursor = NULL;
	L->length = 0;
	L->index = -1;
	return(L);
}
	
// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL
void freeList(List* pL){
	if(pL!=NULL && *pL!=NULL){
		clear(*pL);
	}
	free(*pL);
	*pL = NULL;
}

// Access functions--------------------------

// length()
// Returns the number of elements in L.
int length(List L){
	if(L==NULL){
		printf("List Error: calling length() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	return L->length;
}

// index()
// Returns the index of cursor element if defined, -1 otherwise.
int index(List L){
	if(L==NULL){
		printf("List Error: calling index() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(length(L)<=0){
		return -1;
	}
	return L->index;
}

// front()
// Returns front element of L.
// Pre: length() > 0
int front(List L){
	if(L==NULL){
		printf("List Error: calling front() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(length(L)<=0){
		printf("List Error: calling front() on empty List\n");
		exit(EXIT_FAILURE);
	}
	return L->front->data;
}
		

// back()
// Returns back element of L.
// Pre: length() > 0
int back(List L){
	if(L==NULL){
		printf("List Error: calling back() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(length(L)<=0){
		printf("List Error: calling back() on empty List\n");
		exit(EXIT_FAILURE);
	}
	return L->back->data;
}

// get()
// Returns cursor element of L.
// Pre: length()>0, index()>=0
int get(List L){
	if(L==NULL){
		printf("List Error: calling back() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(length(L)>0 && index(L)>=0){
		return L->cursor->data;
	}
	else{
		printf("List Error: calling get() on empty List or cursor is undefined\n");
		exit(EXIT_FAILURE);
	}
}
		
// equals()
// Returns true iff Lists A and B are in same state,
// and returns false otherwise.
bool equals(List A, List B){
	int eq = 0;
	Node N = NULL;
	Node M = NULL;
	if(A==NULL || B==NULL){
		printf("List Error: calling equals() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	eq = (A->length == B->length);
	N = A->front;
	M = B->front;
	while(eq && N!= NULL){
		eq = (N->data==M->data);
		N = N->next;
		M = M->next;
	}
	return eq;
}

// Manipulation Procedures-----------------------------------

// clear()
// Resets L to its original empty state.
void clear(List L) {
	if(L==NULL){
		printf("List Error: calling clear() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	while(length(L)>0){
		deleteFront(L);
	}
	L->front = NULL;
	L->back = NULL;
	L->cursor = NULL;
	L->length = 0;
	L->index = -1;
}

// set()
// Overwrites the cursor element's data with x.
// Pre: length()>0, index()>=0
 void set(List L, int x){
 if(L==NULL){
		printf("List Error: calling set() on NULL List reference\n");
	    exit(EXIT_FAILURE);
	 }
	 if(length(L)>0 && index(L)>=0){
		insertBefore(L, x);
		delete(L);
	 }
	 else{
		printf("List Error: calling set() on empty List or undefined cursor\n");
	 }
 }
 
// moveFront()
// If L is non-empty, sets cursor under the front element,
// otherwide does nothing.
void moveFront(List L){
	if(L==NULL){
		printf("List Error: calling moveFront() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	// if(length(L)==0){
		// printf("List Error: calling moveFront() on empty List\n");
		// exit(EXIT_FAILURE);
	// }
	else{
		L->cursor = NULL;
		L->cursor = L->front;
		L->index = 0;
	}
}

// moveBack()
// If L is non-empty, sets cursor under the back element,
// otherwise does nothing.
void moveBack(List L){
	if(L==NULL){
		printf("List Error: calling moveBack() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(length(L)==0){
		printf("List Error: calling moveBack() on an empty list\n");
	}
	else{
		L->cursor = L->back;
		L->index = L->length - 1;
	}
}

// movePrev()
// If cursor is defined and not at the front, move cursor one
// step toward the front of L; if cursor is defined and at
// front, cursor becomes undefined; if cursor is undefined
// do nothing
void movePrev(List L){
	if (L==NULL) {
		printf("List Error: calling movePrev() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(index(L)==-1){}
	else if(L->cursor == L->front){
		L->cursor = NULL;
		L->index = -1;
	}
	else{
		L->cursor = L->cursor->prev;
		L->index--;
	}
}

// moveNext()
// If cursor is defined and not at back, move cursor one
// step toward the back of L; if cursor is defined and at
// back, cursor becomes undefined; if cursor is undefined
// do nothing
void moveNext(List L){
	if(L==NULL){
		printf("List Error: calling moveNext() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(index(L)==-1){}
	else if(L->cursor == L->back){
		L->cursor = NULL;
		L->index = -1;
	}
	else{
		L->cursor = L->cursor->next;
		L->index++;
	}
}

// prepend()
// Insert new element into L. If L is non-empty,
// insertion takes place before the front element.
void prepend(List L, int x){
	if(L==NULL){
		printf("List Error: calling prepend() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	Node N = newNode(x);
	if(length(L)==0){
		L->front = N;
		L->back = N;
	}
	else{
		L->front->prev = N;
        N->next = L->front;
        L->front = N;
        L->index++;
	}
	L->length++;
}

// append()
// Insert new element into L. If L is non-empty,
// insertion takes place after the back element.
void append(List L, int x){
	if (L==NULL){
		printf("List Error: calling append() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	Node N = newNode(x);
	if(length(L)==0){
		L->front = N;
		L->back = N;
	}
	else{
		L->back->next = N;
        N->prev = L->back;
		L->back = N;
		N->next = NULL;
	}
	L->length++;
}

// insertBefore()
// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, int x){
	if(L==NULL){
		printf("List Error: calling insertBefore() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(length(L)==0 && index(L)<0){
		printf("List Error: calling delete() on empty List or cursor is undefined\n");
		exit(EXIT_FAILURE);
	}
	if (L->cursor == L->front){
        prepend(L, x);
    }
	else{
		Node N = newNode(x);
        L->cursor->prev->next = N;
		N->prev = L->cursor->prev;
		N->next = L->cursor;
		L->index++;
		L->length++;
	}
}

// insertAfter()
// Insert new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, int x){
	if(L==NULL){
		printf("List Error: calling insertAfter() on NULL List referene\n");
		exit(EXIT_FAILURE);
	}
	if(length(L)==0 && index(L)<0){
		printf("List Error: calling delete() on empty List or cursor is undefined\n");
		exit(EXIT_FAILURE);
	}
	if(L->cursor == L->back){
		append(L, x);
	}
	else{
		Node N = newNode(x);
        L->cursor->next->prev = N;
        N->next = L->cursor->next;
        N->prev = L->cursor;
        L->cursor->next = N;
		L->index++;
		L->length++;
	}
}

// deleteFront()
// Delete the front element.
// Pre: length()>0
void deleteFront(List L){
	if(L==NULL){
		printf("List Error: calling deleteFront() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(length(L)<=0){
		printf("List Error: calling deleteFront() on empty List\n");
		exit(EXIT_FAILURE);
	}
	if(length(L) > 1){
		Node N = L->front;
		L->front = L->front->next;
		L->front->prev = NULL;
		if(L->cursor != NULL){
			L->index--;
		}
		freeNode(&N);
		L->length--;
	}
	else if(length(L)==1){
		Node N = L->front;
		L->cursor = NULL;
		L->front = L->back = NULL;
		L->index = -1;
		freeNode(&N);
		L->length--;
	}
	
 }

// deleteBack()
// Delete the back element.
// Pre: length()>0
void deleteBack(List L){
	if(L==NULL){
		printf("List Error: calling deleteBack() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(length(L)<=0){
		printf("List Error: calling deleteBack() on empty List\n");
		exit(EXIT_FAILURE);
	}
	if(length(L) > 1){
		Node N = L->back;
		L->back = L->back->prev;
		L->back->next = NULL;
		if(L->index == L->length - 1){
			L->index = -1;
		}
		freeNode(&N);
		L->length--;
	}
	else if(length(L)==1){
		Node N = L->back;
		L->cursor = NULL;
		L->front = L->back = NULL;
		L->index = -1;
		freeNode(&N);
		L->length--;
	}
}

// delete()
// Delete cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete(List L){
	if(L==NULL){
		printf("List Error: calling delete() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if(length(L)==0 && index(L)<0){
		printf("List Error: calling delete() on empty List or cursor is undefined\n");
		exit(EXIT_FAILURE);
	}
	 if (L->cursor == L->front)
    {
        deleteFront(L);
    }
    else if (L->cursor == L->back)
    {
        deleteBack(L);
    }
    else
    {
        Node N = L->cursor;
        L->cursor->prev->next = L->cursor->next;
        L->cursor->next->prev = L->cursor->prev;
        freeNode(&N);
        L->length--;
    }
    L->index = -1;
}

// printList()
// Prints to the file pointed to by out, a
// string representation of L consisting
// of a space separated sequence of integers,
// with front on left.
void printList(FILE* out, List L){
	if(L==NULL){
		printf("List Error: callinf printList() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	Node N = L->front;
	while(N != NULL){
		fprintf(out, "%d ", N->data);
		N = N->next;
	}
}

// copyList()
// Returns a new List representing the same integer
// sequence as L. The cursor in the new list is undefined,
// regardless of the states of the cursors in A and B.
// The states of A and B are unchanged.
List copyList(List L){
	if(L==NULL){
		printf("List Error: calling copyList() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	List R = newList();
	Node N = L->front;
	for(int i=0; i<length(L); i++){
		append(R, N->data);
		N = N->next;
	}
	R->cursor = NULL;
	R->index = -1;
	return R;
}

	