#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

using namespace std;

int main(){
    /**
    List A, B;
    List C;
    A.insertBefore(1);
    A.insertAfter(3);
    A.insertAfter(2);
    B.insertBefore(3);
    B.insertBefore(2);
    B.insertBefore(1);
    C = A;
    cout << A<<endl;
    cout << C << endl;
    **/
    /**
    C.insertAfter(1);
    C.insertAfter(2);
    C.insertAfter(3);
    C.insertAfter(3);
    C.insertAfter(2);
    C.insertAfter(1);
    cout << A.concat(B)<<endl;
    cout << C << endl;
    if (!C.equals(A.concat(B)))
      printf("1\n");
    printf("0\n");
    **/

    /**
    A.insertBefore(1);
    A.insertBefore(2);
    A.insertBefore(2);
    A.insertBefore(1);
    A.insertBefore(2);
    A.insertBefore(3);
    A.insertBefore(1);

    A.findPrev(3);
    
    printf("A position: %d\n",A.position());
    A.cleanup();
    printf("A position: %d\n",A.position());
    if (A.position() != 2)
      printf("1\n");

    B.insertBefore(1);
    B.insertBefore(2);
    B.insertBefore(2);
    B.insertBefore(1);
    B.insertBefore(2);
    B.insertBefore(3);
    B.insertBefore(1);
    B.findPrev(3);
    B.movePrev();
    B.cleanup();
    if (B.position() != 2)
      printf("2\n");
    printf("0\n");
    **/
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
