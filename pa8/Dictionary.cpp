/*********************************************************************************
* Jason Bruni, jabruni
* 2022 Winter CSE101 PA8
* Dictionary.cpp
* Source file for Dictionary ADT
*********************************************************************************/
#include<iostream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"

#define BLACK 0
#define RED 1

// Private Constructor------------------------

// Node Constructor
Dictionary::Node::Node(keyType k, valType v){
	key = k;
	val = v;
	parent = nullptr;
	left = nullptr;
	right = nullptr;
	color = BLACK;
}

// Class Constructors & Destructors---------------

// Creates a new Dictionary in the empty state
Dictionary::Dictionary(){
	nil = new Node("nil", -1);
	nil->left = nil;
	nil->right = nil;
	nil->parent = nil;
	
	root = nil;
	root->left = nil;
	root->right = nil;
	root->parent = nil;
	current = nil;
	num_pairs = 0;
}

// Copy Constructor 
Dictionary::Dictionary(const Dictionary& D){
	nil = new Node("\000", -1);
	nil->left = nil;
	nil->right = nil;
	nil->parent = nil;
	
	root = nil;
	root->left = nil;
	root->right = nil;
	root->parent = nil;
	current = nil;
	num_pairs = 0;
	
	// load elements of D into this Dictionary
	preOrderCopy(D.root, D.nil);
}

// Destructor
Dictionary::~Dictionary(){
	clear();
	delete(nil);
	
}

// Access functions ---------------------

	// size()
	// Returns the size of this Dictionary.
	int Dictionary::size() const{
		return num_pairs;
	}

	// contains()
	// Returns true if there exists a pair such that key==k, and returns false
	// otherwise.
	bool Dictionary::contains(keyType k) const{
		Node *N = search(root, k);
		if(N->key == k){
			return true;
		}
		else{
			return false;
		}
	}

	// getValue()
	// Returns a reference to the value corresponding to key k.
	// Pre: contains(k)
	valType& Dictionary::getValue(keyType k) const{
		if((this->Dictionary::contains(k)) == false){
			throw std::logic_error("Dictionary: getValue(): key " + k + " does not exist");
		}
		else{
			Node* N = Dictionary::search(root, k);
			return N->val;
		}
	}
	
	// hasCurrent()
	// Returns true if the current iterator is defined, and returns false 
	// otherwise.
	bool Dictionary::hasCurrent() const{
		if(current != nil){
			return true;
		}
		else{
			return false;
		}
	}
	
	// currentKey()
	// Returns the current key.
	// Pre: hasCurrent() 
	keyType Dictionary::currentKey() const{
		if(hasCurrent() == true){
			return current->key;
		}
		else{
			throw std::logic_error("Dictionary: currentKey(): current undefined");
		}
	}
	
	// currentVal()
	// Returns a reference to the current value.
	// Pre: hasCurrent()
	valType& Dictionary::currentVal() const{
		if(hasCurrent() == true){
			return current->val;
		}
		else{
			throw std::logic_error("Dictionary: currentVal(): current undefined");
		}		
	}

   // Manipulation Procedures --------------------

   // clear()
   // Resets this Dictionary to the empty state, containing no pairs.
	void Dictionary::clear(){
		Dictionary::postOrderDelete(root);
	}
	
   // setValue()
   // If a pair with key==k exists, overwrites the corresponding value with v, 
   // otherwise inserts the new pair (k, v).
   void Dictionary::setValue(keyType k, valType v){
	    if(num_pairs == 0){
			Node* N = new Node(k, v);
			root = N; // tree T was empty
			N->left = nil;
			N->right = nil;
			N->parent = nil;
			num_pairs++;
			return;
		}
		Node* A = nil;
		Node* B = root;
		while(B != nil || B->key == k){
			A = B;
			if(k < A->key){
				B = A->left;
			}
			else if(k > A->key){
				B = A->right;
			}
			else if(A->key == k){
				A->val = v;
				return;			
			}
		}
		Node* N = new Node(k, v);
		N->parent = A;
		N->left = nil;
		N->right = nil;
		num_pairs++;
		if(k < A->key){
			A->left = N;
		}
		else{
			A->right = N;
		}
		N->left = nil;
		N->right = nil;
		N->color = RED;
		RB_InsertFixUp(N);
    }
   
	// remove()
	// Deletes the pair for which key==k. If that pair is current, then current
	// becomes undefined.
	// Pre: contains(k).
	void Dictionary::remove(keyType k){
		if(Dictionary::contains(k) == false){
			throw std::logic_error("Dictionary: remove(): key " + k + " does not exist");
		}
		else{
			Node* R = search(root, k);
			if(current == R){
				current = nil;
			}
			RB_Delete(R);
			num_pairs--;
		}			  
	}
   
   // begin()
   // If non-empty, places current iterator at the first (key, value) pair
   // (as defined by the order operator < on keys), otherwise does nothing. 
   void Dictionary::begin(){
	   if(num_pairs > 0){
			Node* R = Dictionary::findMin(root);
			current = R;
	   }
   }

   // end()
   // If non-empty, places current iterator at the last (key, value) pair
   // (as defined by the order operator < on keys), otherwise does nothing. 
   void Dictionary::end(){
	   if(num_pairs > 0){
			Node* R = Dictionary::findMax(root);
			current = R;
	   }
   }

   // next()
   // If the current iterator is not at the last pair, advances current 
   // to the next pair (as defined by the order operator < on keys). If 
   // the current iterator is at the last pair, makes current undefined.
   // Pre: hasCurrent()
   void Dictionary::next(){
	   if(hasCurrent() == true){
		   Node* R = Dictionary::findMax(root);
		   if(current != R){
			   current = Dictionary::findNext(current);
		   }
		   else if(current == R){
			   current = nil;
		   }
	   }
	   else{
		   throw std::logic_error("Dictionary: next(): current undefined");
	   } 
   }

   // prev()
   // If the current iterator is not at the first pair, moves current to  
   // the previous pair (as defined by the order operator < on keys). If 
   // the current iterator is at the first pair, makes current undefined.
   // Pre: hasCurrent()
   void Dictionary::prev(){
	   if(hasCurrent() == true){
		   Node* R = Dictionary::findMin(root);
		   if(current != R){
			   current = Dictionary::findPrev(current);
		   }
		   else if(current == R){
			   current = nil;
		   }
	   }
	   else{
		   throw std::logic_error("Dictionary: prev(): current undefined");
	   }
   }
 

// Other Functions ---------------------------------------------------------

   // to_string()
   // Returns a string representation of this Dictionary. Consecutive (key, value)
   // pairs are separated by a newline "\n" character, and the items key and value 
   // are separated by the sequence space-colon-space " : ". The pairs are arranged 
   // in order, as defined by the order operator <.
   std::string Dictionary::to_string() const{
	   std::string s = "";
	   s.reserve(20);
	   Dictionary::inOrderString(s, root);
	   return s;
   }

   // pre_string()
   // Returns a string consisting of all keys in this Dictionary. Consecutive
   // keys are separated by newline "\n" characters. The key order is given
   // by a pre-order tree walk.
   std::string Dictionary::pre_string() const{
	   std::string s = "";
	   s.reserve(10);
	   Dictionary::preOrderString(s, root);
	   return s;
   }

	// equals()
	// Returns true if and only if this Dictionary contains the same (key, value)
	// pairs as Dictionary D.
	bool Dictionary::equals(const Dictionary& D) const{
		bool eq = false;
		std::string s = "";
		std::string d = "";
		std::string s2 = "";
		std::string d2 = "";
		Dictionary temp = D;
		eq = (this->num_pairs == temp.num_pairs);
		inOrderString(s, root);
		D.inOrderString(d, D.root);
		preOrderString(s2, root);
		D.preOrderString(d2, D.root);
		if(s.compare(d) == 0 && s2.compare(d2) == 0){
			eq = true;
		}
		else{
			eq = false;
		}
		return eq;
	}


// Overloaded Operators ----------------------------------------------------
   
	// operator<<()
	// Inserts string representation of Dictionary D into stream, as defined by
	// member function to_string().
	std::ostream& operator<<( std::ostream& stream, Dictionary& D ){
		return stream << D.Dictionary::to_string();
	}

	// operator==()
	// Returns true if and only if Dictionary A equals Dictionary B, as defined
	// by member function equals(). 
	bool operator==( const Dictionary& A, const Dictionary& B ){
		   return A.Dictionary::equals(B);
	}

	// operator=()
	// Overwrites the state of this Dictionary with state of D, and returns a
	// reference to this Dictionary.
	Dictionary& Dictionary::operator=( const Dictionary& D ){
		if(this != &D){
			Dictionary temp = D;
			std::swap(nil, temp.nil);
			std::swap(root, temp.root);
			std::swap(num_pairs, temp.num_pairs);
			std::swap(current, temp.current);
		}
		return *this;
	}


// Helper Functions------------------------------
void Dictionary::inOrderString(std::string& s, Node* R) const{
	if(R != nil){
		Dictionary::inOrderString(s, R->left);
		s.append(R->key + " : " + std::to_string(R->val) + "\n");
		Dictionary::inOrderString(s, R->right);
	}
}

void Dictionary::preOrderString(std::string& s, Node* R) const{
	if(R != nil){
		s.append(R->key + "\n");
		Dictionary::preOrderString(s, R->left);
		Dictionary::preOrderString(s, R->right);
	}
}

// search()
// Searches the subtree rooted at R for a Node with key==k. Returns
// the address of the Node if it exists, returns nil otherwise.
Dictionary::Node* Dictionary::search(Node* R, keyType k) const{
	if(R == nil || k == R->key){
		return R;
	}
	else if(k < R->key){
		return search(R->left, k);
	}
	else{
		return search(R->right, k);
	}
}

// findMin()
// If the subtree rooted at R is not empty, returns a pointer to the 
// leftmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMin(Node* R){
	if(R != nil){
		while(R->left != nil){
			R = R->left;
		}
	}
	return R;
}

// findMax()
// If the subtree rooted at R is not empty, returns a pointer to the 
// rightmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMax(Node* R){
	if(R != nil){
		while(R->right != nil){
			R = R->right;
		}
	}
	return R;
}

// findNext()
// If N does not point to the rightmost Node, returns a pointer to the
// Node after N in an in-order tree walk.  If N points to the rightmost 
// Node, or is nil, returns nil. 
Dictionary::Node* Dictionary::findNext(Node* N){
	if(N->right != nil){
		return findMin(N->right);
	}
	Node* A = N->parent;
	while(A != nil && N == A->right){
		N = A;
		A = A->parent;
	}
	return A;
}


// findPrev()
// If N does not point to the leftmost Node, returns a pointer to the
// Node before N in an in-order tree walk.  If N points to the leftmost 
// Node, or is nil, returns nil.
Dictionary::Node* Dictionary::findPrev(Node* N){
	if(N->left != nil){
		return findMax(N->left);
	}
	Node* A = N->parent;
	while(A != nil && N == A->left){
		N = A;
		A = A->parent;
	}
	return A;
	
}

// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this 
// Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Node* R, Node* N){
	if(R != N){
		this->setValue(R->key, R->val);
		Dictionary::preOrderCopy(R->left, N);
		Dictionary::preOrderCopy(R->right, N);
	}
}

// transplant()
void Dictionary::transplant(Node* U, Node* V){
	if(U->parent == nil){
		root = V;
	}
	else if(U == U->parent->left){
		U->parent->left = V;
	}
	else{
		U->parent->right = V;
	}
	if(V != nil){
		V->parent = U->parent;
	}
}

// postOrderDelete()
// Deletes all Nodes in the subtree rooted at R, sets R to nil.
void Dictionary::postOrderDelete(Node* R){
	if(R != nil){
		Dictionary::postOrderDelete(R->left);
		Dictionary::postOrderDelete(R->right);
		Dictionary::remove(R->key);
	}
}
	
// RBT Helper Functions (Optional) -----------------------------------------
   
   // LeftRotate()
   void Dictionary::LeftRotate(Node* N){
	   Node* Y = N->right;
	   N->right = Y->left;
	   if(Y->left != nil){
		   Y->left->parent = N;
	   }
	   
	   Y->parent = N->parent;
	   if(N->parent == nil){
		   root = Y;
	   }
	   else if(N == N->parent->left){
		   N->parent->left = Y;
	   }
	   else{
		   N->parent->right = Y;
	   }
	   Y->left = N;
	   N->parent = Y;
   }

   // RightRotate()
   void Dictionary::RightRotate(Node* N){
	   Node* Y = N->left;
	   N->left = Y->right;
	   if(Y->right != nil){
		   Y->right->parent = N;
	   }
	   Y->parent = N->parent;
	   if(N->parent == nil){
		   root = Y;
	   }
	   else if(N == N->parent->right){
		   N->parent->right = Y;
	   }
	   else{
		   N->parent->left = Y;
	   }
	   
	   Y->right = N;
	   N->parent = Y;
   }

   // RB_InsertFixUP()
   void Dictionary::RB_InsertFixUp(Node* N){
	   Node* Y;
	   while(N->parent->color == RED){
		   if(N->parent == N->parent->parent->left){
			   Y = N->parent->parent->right;
			   if(Y->color == RED){
				   N->parent->color = BLACK;
				   Y->color = BLACK;
				   N->parent->parent->color = RED;
				   N = N->parent->parent;
			   }
			   else{
				   if(N == N->parent->right){
					   N = N->parent;
					   LeftRotate(N);
				   }
				   N->parent->color = BLACK;
				   N->parent->parent->color = RED;
				   RightRotate(N->parent->parent);
			   }
		   }
		   else{
			   Y = N->parent->parent->left;
			   if(Y->color == RED){
				   N->parent->color = BLACK;
				   Y->color = BLACK;
				   N->parent->parent->color = RED;
				   N = N->parent->parent;
			   }
			   else{
				   if(N == N->parent->left){
					   N = N->parent;
					   RightRotate(N);
				   }
				   N->parent->color = BLACK;
				   N->parent->parent->color = RED;
				   LeftRotate(N->parent->parent);
			   }
		   }
		   root->color = BLACK;
	   }
   }

   // RB_Transplant()
   void Dictionary::RB_Transplant(Node* u, Node* v){
	   if(u->parent == nil){
		   root = v;
	   }
	   else if(u == u->parent->left){
		   u->parent->left = v;
	   }
	   else{
		   u->parent->right = v;
	   }
	   v->parent = u->parent;
   }

   // RB_DeleteFixUp()
   void Dictionary::RB_DeleteFixUp(Node* N){
	   Node* W;
	   while(N != root && N->color == BLACK){
		   if(N == N->parent->left){
			   W = N->parent->right;
			   if(W->color == RED){
				   W->color = BLACK;
				   N->parent->color = RED;
				   LeftRotate(N->parent);
				   W = N->parent->right;
			   }
			   if(W->left->color == BLACK && W->right->color == BLACK){
				   W->color = RED;
				   N = N->parent;
			   }
			   else{
				   if(W->right->color == BLACK){
					   W->left->color = BLACK;
					   W->color = RED;
					   RightRotate(W);
					   W = N->parent->right;
				   }
				   W->color = N->parent->color;
				   N->parent->color = BLACK;
				   W->right->color = BLACK;
				   LeftRotate(N->parent);
				   N = root;
			   }
		   }
		   else{
				W = N->parent->left;
				if(W->color == RED){
				    W->color = BLACK;
					N->parent->color = RED;
					RightRotate(N->parent);
					W = N->parent->left;
				}
				if(W->right->color == BLACK && W->left->color == BLACK){
					W->color = RED;
					N = N->parent;
				}
				else{
					if(W->left->color == BLACK){
						W->right->color = BLACK;
						W->color = RED;
						LeftRotate(W);
						W = N->parent->left;
					}
					W->color = N->parent->color;
					N->parent->color = BLACK;
					W->left->color = BLACK;
					RightRotate(N->parent);
					N = root;
				}
				   
			}
		}
		N->color = BLACK;
    }

   // RB_Delete()
   void Dictionary::RB_Delete(Node* N){
	   Node* Y = N;
	   Node* X;
	   int Y_original_color = Y->color;
	   if(N->left == nil){
		   X = N->right;
		   RB_Transplant(N, N->right);
	   }
	   else if(N->right == nil){
		   X = N->left;
		   RB_Transplant(N, N->left);
	   }
	   else{
		   Y = findMin(N->right);
		   Y_original_color = Y->color;
		   X = Y->right;
		   if(Y->parent == N){
			   X->parent = Y;
		   }
		   else{
			   RB_Transplant(Y, Y->right);
			   Y->right = N->right;
			   Y->right->parent = Y;
		   }
		   RB_Transplant(N, Y);
		   Y->left = N->left;
		   Y->left->parent = Y;
		   Y->color = N->color;
	   }
	   if(Y_original_color == BLACK){
		   RB_DeleteFixUp(X);
	   }
	   
   }