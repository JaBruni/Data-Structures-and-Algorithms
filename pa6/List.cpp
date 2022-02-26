/*********************************************************************************
* Jason Bruni, jabruni
* 2022 Winter CSE101 PA6
* List.cpp
* Source file for List ADT
*********************************************************************************/
#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

// Private Constructor ------------------------------

// Node Constructor
List::Node::Node(ListElement x){
	data = x;
	next = nullptr;
	prev = nullptr;
}

// Class Constructors & Destructors ----------------------

// Creates a new List in the empty state
List::List(){
	frontDummy = new Node(0);
	backDummy = new Node(0);
	frontDummy->next = backDummy;
	backDummy->prev = frontDummy;
	frontDummy->prev = NULL;
	backDummy->next = NULL;
	beforeCursor = frontDummy;
	afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;
}

// Copy Constructor
List::List(const List& L){
	// make this an empty List
	frontDummy = new Node(0);
	backDummy = new Node(0);
	frontDummy->next = backDummy;
	backDummy->prev = frontDummy;
	frontDummy->prev = NULL;
	backDummy->next = NULL;
	beforeCursor = frontDummy;
	afterCursor = backDummy;
	pos_cursor = 0;
	num_elements = 0;
	
	//load elements of L into this List
	Node* N = L.backDummy->prev;
	while(N != L.frontDummy){
		this->insertAfter(N->data);
		N = N->prev;
	}
		
}

// Destructor
List::~List(){
	clear();
	delete(frontDummy);
	delete(backDummy);
}

// Access functions ----------------------

// length()
// Returns the length of this List.
int List::length() const{
	return(num_elements);
}

// front()
// Returns the front element in this List.
// pre: length()>0
ListElement List::front() const{
	if(num_elements == 0){
		throw std::length_error("List: front(): empty List");
	}
	return(frontDummy->next->data);
}

// back()
// Returns the back element in this List.
// pre: length()>0
ListElement List::back() const{
	if(num_elements == 0){
		throw std::length_error("List: back(): empty List");
	}
	return(backDummy->prev->data);
}

// position()
// Returns the position of cursor in this List: 0 <= position() <= length().
int List::position() const{
	return(pos_cursor);
}

// peekNext()
// Returns the element after the cursor.
// pre: position()<length()
ListElement List::peekNext() const{
	if(pos_cursor >= num_elements){
		throw std::range_error("List: peekNext(): cursor  at back");
	}
	return(afterCursor->data);
 }
 
// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
ListElement List::peekPrev() const{
	if(pos_cursor <= 0){
		throw std::range_error("List: peekPrev(): cursor at front");
	}
	return(beforeCursor->data);
}



// Manipulation procedures -------------------------------------------------

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear(){
	moveFront();
	while(this->length() != 0){
		eraseAfter();
	}
}

// moveFront()
// Moves cursor to position 0 in the list
void List::moveFront(){
	beforeCursor = frontDummy;
	afterCursor =  frontDummy->next;
	pos_cursor = 0;
}

// moveBack()
// Moves cursor to position length() in this list
void List::moveBack(){
	afterCursor = backDummy;
	beforeCursor = backDummy->prev;
	pos_cursor = num_elements;

}

// moveNext()
// Advances cursor to next higher position. Returns the List element that was passed over.
// pre: position()<length()
ListElement List::moveNext(){
	if(pos_cursor >= num_elements){
		throw std::range_error("List: moveNext(): cursor at back");
	}
	afterCursor = afterCursor->next;
	beforeCursor = beforeCursor->next;
	pos_cursor++;
	return(beforeCursor->data);
}

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over. 
// pre: position()>0
ListElement List::movePrev(){
	if(pos_cursor <= 0){
		throw std::range_error("List: movePrev(): cursor at front");
	}
	beforeCursor = beforeCursor->prev;
	afterCursor = afterCursor->prev;
	pos_cursor--;
	return(afterCursor->data);
}
		

// insertAfter()
// Inserts x after cursor.
void List::insertAfter(ListElement x){
	Node* N = new Node(x);
	beforeCursor->next->prev = N;
	N->next = afterCursor;
	N->prev = beforeCursor;
	beforeCursor->next = N;
	afterCursor = N;
	num_elements++;
}

// insertBefore()
// Inserts x before cursor.
void List::insertBefore(ListElement x){
	Node* N = new Node(x);
	afterCursor->prev->next = N;
	N->prev = afterCursor->prev;
	N->next = afterCursor;
	afterCursor->prev = N;
	beforeCursor = N;
	num_elements++;
	pos_cursor++;
}

// setAfter()
// Overwrites the List element after the cursor with x.
// pre: position()<length()
void List::setAfter(ListElement x){
	if(pos_cursor >= num_elements){
		throw std::range_error("List: setAfter(): cursor at back");
	}
	eraseAfter();
	insertAfter(x);
}

// setBefore()
// Overwrites the List element before the cursor with x.
// pre: position()>0
void List::setBefore(ListElement x){
	if(pos_cursor <= 0){
		throw std::range_error("List: setBefore(): cursor at front");
	}
	eraseBefore();
	insertBefore(x);
}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<length()
void List::eraseAfter(){
	if(pos_cursor >= num_elements){
		throw std::range_error("List: eraseAfter(): cursor at back");
	}
	Node* N = afterCursor;
	afterCursor->prev->next = afterCursor->next;
	afterCursor->next->prev = afterCursor->prev;
	beforeCursor = afterCursor->prev;
	afterCursor = beforeCursor->next;
	delete(N);

	num_elements--;
}

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore(){
	if(pos_cursor <= 0){
		throw std::range_error("List: eraseBefore(): cursor at front");
	}
	Node* N = beforeCursor;
	beforeCursor->prev->next = beforeCursor->next;
	beforeCursor->next->prev = beforeCursor->prev;
	beforeCursor = afterCursor->prev;
	afterCursor = beforeCursor->next;
	delete N;
	num_elements--;
	pos_cursor--;
}
   
// Other Functions ---------------------------------------------------------

// findNext()
// Starting from the current cursor position, performs a linear search (in 
// the direction front-to-back) for the first occurrence of element x. If x
// is found, places the cursor immediately after the found element, then 
// returns the final cursor position. If x is not found, places the cursor 
// at position length(), and returns -1. 
int List::findNext(ListElement x){
	Node* N = nullptr;
	for(N = afterCursor; N != backDummy; N = N->next){
		moveNext();
		if(N->data == x){
			beforeCursor = N;
			afterCursor = N->next;
			return(this->position());
		}
		
	}
	this->moveBack();
	return -1;
}

// findPrev()
// Starting from the current cursor position, performs a linear search (in 
// the direction back-to-front) for the first occurrence of element x. If x
// is found, places the cursor immediately before the found element, then
// returns the final cursor position. If x is not found, places the cursor 
// at position 0, and returns -1. 
int List::findPrev(ListElement x){
	Node* N = nullptr;
	for(N = beforeCursor; N != frontDummy; N = N->prev){
		movePrev();
		if(N->data == x){
			beforeCursor = N->prev;
			afterCursor = N;
			return(this->position());
		}
	}
	this->moveFront();
	return -1;
}

// cleanup()
// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost 
// occurrance of each element, and removing all other occurances. The cursor 
// is not moved with respect to the retained elements, i.e. it lies between 
// the same two retained elements that it did before cleanup() was called.
void List::cleanup(){
	Node* N = nullptr;
	Node* M = nullptr;;
	Node* D = nullptr;
	
	for(N = frontDummy->next; N != backDummy; N = N->next){
		int count = 0;
		for(M = N->next; M != backDummy; M = M->next){
			if(N->data == M->data){
				D = M;
				if(afterCursor == M){
					afterCursor = afterCursor->next;
				}
				else if(beforeCursor == M ){
					beforeCursor = beforeCursor->prev;
					pos_cursor--;
				}
				else if(beforeCursor != M && count < position()){
					pos_cursor--;
				}
				M->prev->next = M->next;
				M->next->prev = M->prev;
				delete(D);
				num_elements--;
			}
			count++;
		}
	}
}

 
// concat()
// Returns a new List consisting of the elements of this List, followed by
// the elements of L. The cursor in the returned List will be at postion 0.
List List::concat(const List& L) const{
	List R;
	Node* N = this->frontDummy->next;
	Node* M = L.frontDummy->next;
	while(N != this->backDummy){
		R.insertBefore(N->data);
		N = N->next;
	}
	while(M != L.backDummy){
		R.insertBefore(M->data);
		M = M->next;
	}
	R.moveFront();
	return R;
}
	

// to_string()
// Returns a string representation of List consiting of a space separated
// list of data values.
std::string List::to_string() const{
	Node* N = nullptr;
	std::string r;
	std::string p;
	std::string s = "";
	for(N = frontDummy->next; N!= backDummy; N=N->next){
		s += std::to_string(N->data);
	}
	// p = "(" + s + std::to_string(backDummy->prev->data) + ")";
	return s;
}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R) const{
	bool eq = false;
	Node *N = nullptr;
	Node *M = nullptr;
	
	eq = (this->num_elements == R.num_elements);
	N = this->frontDummy->next;
	M = R.frontDummy->next;
	while(eq && N != backDummy){
		eq = (N->data == M->data);
		N = N->next;
		M = M->next;
	}
	return(eq);
}

// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of L into stream.
std::ostream& operator<< (std::ostream& stream, const List& L){
	return stream << L.List::to_string();
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The 
// cursors in both Lists are unchanged.
bool operator== (const List& A, const List& B){
	return A.List::equals(B);
}
	
// operator=()
// Overwrites the state of this List with state of L.
List& List::operator=(const List& L){
	if(this != &L){
		// make a copy of L
		List temp = L;
		
		std::swap(frontDummy, temp.frontDummy);
		std::swap(backDummy, temp.backDummy);
		std::swap(afterCursor, temp.afterCursor);
		std::swap(beforeCursor, temp.beforeCursor);
		std::swap(pos_cursor, temp.pos_cursor);
		std::swap(num_elements, temp.num_elements);
	}
	
	// return this with the new data installed
	return *this;
	
	// the copy, is there is one, is deleted upon return
	
}
	
	
	
	 
		 
	

