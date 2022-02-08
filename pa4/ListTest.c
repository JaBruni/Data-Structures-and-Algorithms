/*********************************************************************************
* Jason Bruni, jabruni
* 2022 Winter CSE101 PA4
* ListTest.c
* Test Client for the List ADT
*********************************************************************************/
#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include"List.h"

int main(){
   List A = newList();
   List B = newList();
   bool equal = false;
   int X[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
   int i, u = -1, v = -2, w = -3;
  
   for(i=1; i<=20; i++){
      append(A, &X[i]);
      prepend(B, &X[i]);
   }

   
   for(moveFront(A); index(A)>=0; moveNext(A)){
      printf("%d ", *(int*)get(A));
   }
   printf("\n");
   for(moveFront(B); index(B)>=0; moveNext(B)){
      printf("%d ", *(int*)get(B));
   }
   printf("\n");

  
   for(moveBack(A); index(A)>=0; movePrev(A)){
      printf("%d ", *(int*)get(A));
   }
   printf("\n");
   for(moveBack(B); index(B)>=0; movePrev(B)){
      printf("%d ", *(int*)get(B));
   }
   printf("\n");


   equal = (length(A)==length(B));
   moveFront(A);
   moveFront(B);
   while( index(A)>=0 && equal){
      equal = ( get(A)==get(B) );
      moveNext(A);
      moveNext(B);
   }
   printf("A equals B is %s\n", (equal?"true":"false") );

   moveFront(A);
   for(i=0; i<5; i++) moveNext(A);    
   printf("index(A)=%d\n", index(A));
   insertBefore(A, &u);                
   printf("index(A)=%d\n", index(A));
   for(i=0; i<9; i++) moveNext(A);     
   printf("index(A)=%d\n", index(A));
   insertAfter(A, &v);                 
   printf("index(A)=%d\n", index(A));
   for(i=0; i<5; i++) movePrev(A);     
   printf("index(A)=%d\n", index(A));
   delete(A);                          
   printf("index(A)=%d\n", index(A));
   moveBack(A);                       
   printf("index(A)=%d\n", index(A));
   for(i=0; i<10; i++) movePrev(A);   
   printf("index(A)=%d\n", index(A));
   set(A, &w);

   printf("%d\n", length(A));
   clear(A);
   printf("%d\n", length(A));

   freeList(&A);
   freeList(&B);

   return(0);
}
	
