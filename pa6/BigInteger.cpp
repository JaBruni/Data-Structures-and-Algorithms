/*********************************************************************************
* Jason Bruni, jabruni
* 2022 Winter CSE101 PA6
* BigInteger.cpp
* Source file for BigInteger ADT
*********************************************************************************/
#include<iostream>
#include<string>
#include<stdexcept>
#include<cstring>
#include"List.h"
#include"BigInteger.h"

const long BASE = 1000000000;
const int POWER = 9;

int normalizeList(List& L);
void sumList(List& S, List A, List B, int sgnA, int sgnB);
void negateList(List& L);

// Class Constructors & Destructors-------------------------

// BigInteger()
// Constructor that creates a new BigInteger in the zero state: 
// signum=0, digits=().
BigInteger::BigInteger(){
	signum = 0;
}

// BigInteger()
// Constructor that creates a new BigInteger from the string s.
// Pre: s is a non-empty string consisting of (at least one) base 10 digit
// {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
BigInteger::BigInteger(std::string s){
	int n = s.length();
	char cursor[n+1];
	std::strcpy(cursor, s.c_str());
	char* p = cursor;
	int length = 0;
	if(*p == '-'){
		signum = -1;
	}
	else if(*p == '+'){
		signum = 1;
	}
	else{
		signum = 1;
	}
	
	if(*p == '-' || *p == '+'){
		p = p + 1;
	}
	
	while(*p == '0'){
		p = p + 1;
	}
	while(*p != '\0'){
		if(!std::isdigit(*p)){
			throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
		}
		length++;
		p = p + 1;
	}
	
	if(length == 0){
		throw std::invalid_argument("BigInteger: Constructor: empty string");
	}
	
	int power = (length - 1) / POWER;
	int entries = power + 1;
	
	p = cursor;
	
	if(*p == '-' || *p == '+'){
		p = p + 1;
	}
	
	while(*p == '0'){
		p = p + 1;
	}
	
	for(int i = 1; i <= entries; i++){
		char str[9] = { '\0' };
		if( i == 1 && (length % POWER != 0)){
			int numDigits = length % POWER;
			for(int j = 1; j <= numDigits; j++){
				sprintf(str + strlen(str), "%d", (*p) - 48);
				p++;
			}
			long res = strtol(str, NULL, 10);
			digits.insertBefore(result);
			continue;
		}
		strncpy(str, "", sizeof(str));
		for (int j = 1; j <= POWER; j++){
			sprintf(str + strlen(str), "%d", (*p) - 48);
			p++;
		}
		long res = strtol(str, NULL, 10);
		digits.insertBefore(result);
	}
}
	
	// BigInteger()
   // Constructor that creates a copy of N.
   BigInteger::BigInteger(const BigInteger& N){
	 signum = 0;
	 this->signum = N.signum;
	 this->digits = N.digits;
   }

   // Optional Destuctor
   // ~BigInteger()
   // ~BigInteger();


   // Access functions --------------------------------------------------------

   // sign()
   // Returns -1, 1 or 0 according to whether this BigInteger is positive, 
   // negative or 0, respectively.
   int BigInteger::sign() const{
	   return (signum);
	   
   }

   // compare()
   // Returns -1, 1 or 0 according to whether this BigInteger is less than N,
   // greater than N or equal to N, respectively.
   int BigInteger::compare(const BigInteger& N) const{
	   List A = this->digits;
	   List B = N.digits;
	   int numReturn = 0;
	   if(this->sign() < N.sign()){
		   numReturn = -1;
	   }
	   else if(N.sign() < this->sign()){
		   numReturn = 1;
	   }
	   else{
		   if(A.length() > B.length()){
			   numReturn = 1;
		   }
		   else if(B.length() > A.length()){
			   numReturn = -1;
		   }
		   else{
			   A.moveFront();
			   B.moveFront();
			   while((A.position() != A.length()) && (B.position() != B.length())){
				   long thisElement = A.peekNext();
				   long nElement = B.peekNext();
				   if(thisElement < nElement){
					   if(this->sign() == 1){
						   numReturn = -1;
						   break;
					   }
					   else if(this->sign() == -1){
						   numReturn = 1;
						   break;
					   }
				   }
				   else if(nElement < thisElement){
					   if(this->sign() == 1){
						   numReturn = 1;
						   break;
					   }
					   else if(this->sign() == -1){
						   numReturn = -1;
						   break;
					   }
				   }
				   else{}
				   A.moveNext();
				   B.moveNext();
			   }
			   return numReturn;
		   }
	   }
	  return numReturn; 
   }


   // Manipulation procedures -------------------------------------------------

   // makeZero()
   // Re-sets this BigInteger to the zero state.
   void BigInteger::makeZero(){
	   signum = 0;
	   digits.clear();
   }

   // negate()
   // If this BigInteger is zero, does nothing, otherwise reverses the sign of 
   // this BigInteger positive <--> negative. 
   void BigInteger::negate(){
	   if (signum == 1){
		   signum = -1;
	   }
	   else if(signum == -1){
		   signum = 1;
	   } 
   }


   // BigInteger Arithmetic operations ----------------------------------------

   // add()
   // Returns a BigInteger representing the sum of this and N.
   BigInteger BigInteger::add(const BigInteger& N) const{
	   BigInteger A;
	   sumList(A.digits, this->digits, N.digits, this->sign(), N.sign());
	   A.signum = normalizeList(A.digits);
	   return A; 
   }
   
   // sumList()
   // Overwrites the state of S with A + sgn*B (considered as vectors).
   // Used by both sum() and sub().
   void sumList(List& S, List A, List B, int sgnA, int sgnB){
	   A.moveBack();
	   B.moveBack();
	   while(A.position() != 0 && B.position() != 0){
		   S.insertAfter((A.peekPrev() * sgnA) + (B.peekPrev() * sgnB));
		   A.movePrev();
		   B.movePrev();
	   }
	   if(A.position() != 0){
		   while(A.position() != 0){
			   S.insertAfter(sgnA * A.peekPrev());
			   A.movePrev();
		   }
	   }
	   if(B.position() != 0){
		   while(B.position() != 0){
			   S.insertAfter(sgnB * B.peekPrev());
			   B.movePrev();
		   }
	   }
   }

   // sub()
   // Returns a BigInteger representing the difference of this and N.
   BigInteger BigInteger::sub(const BigInteger& N) const{
	   BigInteger D = N;
	   D.BigInteger::negate();
	   return this->BigInteger::add(D);
   }
   
   // negateList()
   // Changes the sign of each integer in List L. Used by sub().
   void negateList(List& L){
		L.moveFront();
	    while(L.position() != L.length()){
		   L.setAfter(L.peekNext() * -1);
		   L.moveNext();
	    }
	}

   // mult()
   // Returns a BigInteger representing the product of this and N. 
   BigInteger BigInteger::mult(const BigInteger& N) const{
	   BigInteger M;
	   M.signum = 1;
	   BigInteger Temp;
	   Temp.signum = 1;
	   List A = this->digits;
	   List B = N.digits;
	   A.moveBack();
	   B.moveBack();
	   int counter = 0;
	   while(B.position() != 0){
		   Temp.digits.clear();
		   for(int i = 0; i < counter; i++){
			   Temp.digits.insertAfter(0);
		   }
		   A.moveBack();
		   while(A.position() != 0){
			   Temp.digits.insertAfter(B.peekPrev() * A.peekPrev());
			   A.movePrev();
		   }
		   Temp.signum = normalizeList(Temp.digits);
			M = M.BigInteger::add(Temp);
		    M.signum = normalizeList(M.digits);
		   B.movePrev();
		   counter++;
	   }
	   if(this->sign() == N.sign()){
		   M.signum = 1;
	   }
	   else{
		   M.signum = -1;
	   }
	   return M;
   }

	// normalizeList()
	// Performs carries from right to left (least to most significant
	// digits), then returns the sign of the resulting integer. Used
	// by add(), sub() and mult().
	int normalizeList(List& L){
		int sign;
		if(L.front() < 0){
			sign = -1;
			L.moveFront();
			while(L.position() != L.length()){
				L.setAfter(L.peekNext() * -1);
				L.moveNext();
			}
		}
		else{
		sign = 1;
		L.moveBack();
		long carry = 0;
		while(L.position() != 0){
			if(carry != 0){
				L.setBefore(L.peekPrev() + carry);
				carry = 0;
			}
			
			if(L.peekPrev() < 0){
				if((L.peekPrev() / BASE) == 0){
					carry = -1;
				}
				else{
					carry = ((L.peekPrev()) / BASE) - 1;
				}
				L.setBefore(L.peekPrev() + abs(BASE * carry));
			}
			else if(L.peekPrev() >= BASE){
				carry = L.peekPrev() / BASE;
				L.setBefore(L.peekPrev() - (BASE * carry));
			}
			else{}
			L.movePrev();
		}
		if(carry > 0){
			L.moveFront();
			L.insertAfter(carry);
		}
		L.moveFront();
		while(L.position() != L.length()){
			if(L.peekNext() == 0){
				L.eraseAfter();
				L.moveFront();
			}
			else{
				break;
			}
		}
		
		if(L.length() == 0){
			L.insertAfter(0);
			sign = 0;
		}
		}
		return sign;

	}


   // Other Functions ---------------------------------------------------------

   // to_string()
   // Returns a string representation of this BigInteger consisting of its
   // base 10 digits. If this BigInteger is negative, the returned string 
   // will begin with a negative sign '-'. If this BigInteger is zero, the
   // returned string will consist of the character '0' only.
   std::string BigInteger::to_string(){
	   std::string s = "";
	   if(this->sign() == 0){
		   s += '0';
	   }
	   else if(this->sign() == -1){
		   s += "-" + digits.List::to_string();
	   }
	   else{
		   s += digits.List::to_string();
	   }
	   return s;
	   
   }


   // Overriden Operators -----------------------------------------------------
   
   // operator<<()
   // Inserts string representation of N into stream.
    std::ostream& operator<<( std::ostream& stream, BigInteger N ){
	   return stream << N.BigInteger::to_string();
   }

   // operator==()
   // Returns true if and only if A equals B. 
    bool operator==( const BigInteger& A, const BigInteger& B ){
	   if(A.BigInteger::compare(B) == 0){
		   return 1;
	   }
	   else{
		   return 0;
	   }
   }

   // operator<()
   // Returns true if and only if A is less than B. 
    bool operator<( const BigInteger& A, const BigInteger& B ){
	   if(A.BigInteger::compare(B) == -1){
		   return 1;
	   }
	   else{
		   return 0;
	   }
   }

   // operator<=()
   // Returns true if and only if A is less than or equal to B. 
    bool operator<=( const BigInteger& A, const BigInteger& B ){
	   if(A.BigInteger::compare(B) == 0 || A.BigInteger::compare(B) == -1){
		   return 1;
	   }
	   else{
		   return 0;
	   }
   }

   // operator>()
   // Returns true if and only if A is greater than B. 
    bool operator>( const BigInteger& A, const BigInteger& B ){
	   if(A.BigInteger::compare(B) == 1){
		   return 1;
	   }
	   else{
		   return 0;
	   }
   }

   // operator>=()
   // Returns true if and only if A is greater than or equal to B. 
    bool operator>=( const BigInteger& A, const BigInteger& B ){
	   if(A.BigInteger::compare(B) == 0 || A.BigInteger::compare(B) == 1){
		   return 1;
	   }
	   else{
		   return 0;
	   }
   }

   // operator+()
   // Returns the sum A+B. 
    BigInteger operator+( const BigInteger& A, const BigInteger& B ){
	   return A.BigInteger::add(B);
   }

   // operator+=()
   // Overwrites A with the sum A+B. 
    BigInteger operator+=( BigInteger& A, const BigInteger& B ){
	   return A = A.BigInteger::add(B);
   }

   // operator-()
   // Returns the difference A-B. 
    BigInteger operator-( const BigInteger& A, const BigInteger& B ){
	   return A.BigInteger::sub(B);
   }

   // operator-=()
   // Overwrites A with the difference A-B. 
    BigInteger operator-=( BigInteger& A, const BigInteger& B ){
	   return A = A.BigInteger::sub(B);
   }

   // operator*()
   // Returns the product A*B. 
    BigInteger operator*( const BigInteger& A, const BigInteger& B ){
	   return A.BigInteger::mult(B);
   }

   // operator*=()
   // Overwrites A with the product A*B. 
    BigInteger operator*=( BigInteger& A, const BigInteger& B ){
	   return A = A.BigInteger::mult(B);
   }

	
