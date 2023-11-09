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
      B.insertAfter(11-i);
      C.insertBefore(i);
      D.insertBefore(11-i);
   }
   //checking findNext for memory leaks
   printf("%d\n", B.findNext(5));
   //checking erase for memory leaks
   B.eraseBefore();
   B.eraseAfter();
   
   //checking cleanup for memory leaks
   A.moveBack();
   for( i=10; i>=1; i--){
      A.insertAfter(i);
      A.movePrev();
   }
   cout<<A<<endl;
  
   printf("A length: %d\n", A.length());
   A.cleanup();

   cout<<A<<endl;
   printf("A length: %d\n", A.length());

   //checking concat for memory leaks
   List F = A.concat(B);
   cout<<F<<endl;
}
