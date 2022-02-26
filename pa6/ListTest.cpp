/*********************************************************************************
* Jason Bruni, jabruni
* 2022 Winter CSE101 PA6
* ListTest.cpp
* Test Client for List ADT
*********************************************************************************/
#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

using namespace std;

int main(){

   int i, n=10;
   List A, B, C, D;
   for(i=1; i<=n; i++){
      A.insertAfter(i);
      B.insertBefore(i);
   }

   cout << endl;
   cout << "A = " << A << endl;
   cout << "A.length() = " << A.length() << endl;
   cout << "B = " << B << endl;
   cout << "B.length() = " << B.length() << endl;
   cout << "A.front() = " << A.front() << endl;
   cout << "B.front() = " << B.front() << endl;
   cout << "A.back() = " << A.back() << endl;
   cout << "B.back() = " << B.back() << endl;
   cout << "A.position() = " << A.position() << endl;
   cout << "B.position() = " << B.position() << endl;
   cout << endl;

   A.moveBack();
   B.moveFront();
   
   cout << "A = " << A << endl;
   cout << "A.position() = " << A.position() << endl;
   cout << "B = " << B << endl;
   cout << "B.position() = " << B.position() << endl;

   cout << "A.peekPrev() = " << A.peekPrev() << endl;
   cout << "B.peekNext() = " << B.peekNext() << endl;
   
   cout << A.movePrev() << endl;
   cout << A.movePrev() << endl;
   cout << B.moveNext() << endl;
   cout << B.moveNext() << endl;
   
   A.setAfter(4);
   B.setBefore(6);
   cout << A << endl;
   cout << B << endl;
   
   A.eraseAfter();
   B.eraseBefore();
   cout << A << endl;
   cout << B << endl;
   cout << "A.length() = " << A.length() << endl;
   cout << "B.length() = " << B.length() << endl;
   
   A.moveFront();
   B.moveFront();
   
   cout << A.findNext(5) << endl;
   cout << B.findNext(5) << endl;
   cout << A.findPrev(9) << endl;
   cout << B.findPrev(3) << endl;
   cout << endl;
   
   for( i=1; i<= 7; i++){
      C.insertBefore(1);
	  C.insertBefore(2);
	  C.insertBefore(3);
   }
   cout << C << endl;
   C.cleanup();
   cout << C << endl;
   
   cout << "B==A is " << (B==A?"true":"false") << endl;
   
   D = A.concat(B);
   cout << "D = " << D << endl;
   cout << "length: " << D.length() << endl;
   cout << "front: " << D.front() << endl;
   cout << "back: " << D.back() << endl;
   cout << "position: " << D.position() << endl;
   



   cout << "test exceptions: " << endl;
   cout << "A = " << A << endl;
   A.moveFront();
   try{
      A.peekPrev();
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.movePrev();
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.setBefore(5);
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.eraseBefore();
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   A.moveBack();
   try{
      A.peekNext();
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.moveNext();
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.setAfter(5);
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.eraseAfter();
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   A.clear();
   try{
      A.front();
   }catch( std::length_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.back();
   }catch( std::length_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }

   cout << endl;


   return( EXIT_SUCCESS );
}