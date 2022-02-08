/*********************************************************************************
* Jason Bruni, jabruni
* 2022 Winter CSE101 PA4
* List.h
* Header file for List ADT
*********************************************************************************/
#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_
#include <stdbool.h>

// Exported Type
typedef struct ListObj* List;
typedef void* element;

// Constructors-Destructors -------------

// newList()
// Returns reference to new empty List object
List newList(void);

// freeList()
// Frees all heap memory associated with Queue *pL, and sets *pL to NULL
void freeList(List* pL);

// Access Functions -------------

// length()
// Returns the number of elements in L.
int length(List L);

// index()
// Returns the index of cursor element if defined, -1 otherwise.
int index(List L);

// front()
// Returns front element of L.
// Pre: length() > 0
element front(List L);

// back()
// Returns back element of L.
// Pre: length() > 0
element back(List L);

// get()
// Returns cursor element of L.
// Pre: length()>0, index()>=0
element get(List L);

// Manipulation Procedures-------------

// clear()
// Resets L to its original empty state.
void clear(List L);

// set()
// Overwrites the cursor element's data with x.
// Pre: length()>0, index()>=0
void set(List L, element x);

// moveFront()
// If L is non-empty, sets cursor under the front element,
// otherwide does nothing.
void moveFront(List L);

// moveBack()
// If L is non-empty, sets cursor under the back element,
// otherwise does nothing.
void moveBack(List L);

// movePrev()
// If cursor is defined and not at the front, move cursor one
// step toward the front of L; if cursor is defined and at
// front, cursor becomes undefined; if cursor is undefined
// do nothing
void movePrev(List L);

// moveNext()
// If cursor is defined and not at back, move cursor one
// step toward the back of L; if cursor is defined and at
// back, cursor becomes undefined; if cursor is undefined
// do nothing
void moveNext(List L);

// prepend()
// Insert new element into L. If L is non-empty,
// insertion takes place before the front element.
void prepend(List L, element x);

// append()
// Insert new element into L. If L is non-empty,
// insertion takes place after the back element.
void append(List L, element x);

// insertBefore()
// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, element x);

// insertAfter()
// Insert new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, element x);

// deleteFront()
// Delete the front element.
// Pre: length()>0
void deleteFront(List L);

// deleteBack()
// Delete the back element.
// Pre: length()>0
void deleteBack(List L);

// delete()
// Delete cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete(List L);

// Other Functions------------------

// printList()
// Prints to the file pointed to by out, a
// string representation of L consisting
// of a space separated sequence of integers,
// with front on left.
void printList(FILE* out, List L);


#endif