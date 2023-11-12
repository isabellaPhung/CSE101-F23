/***
 * Isabella Phung
 * itphung
 * 2023 Fall CSE 101 PA5
 * Shuffle.cpp
 * Client program for List ADT that performs riffle shuffle on a deck
 ***/

#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"
#include<cmath>

using namespace std;

void shuffle(List& D){
 if(D.length() != 0 && D.length() != 1){
     //cout<<D<<endl;
     List left;
     List right;
     D.moveFront();
     for(int i = 0; i<D.length()/2; i++){
        left.insertBefore(D.moveNext());
     }
     
     //cout<<"left: "<<left<<endl;

     for(int i = std::floor(D.length()/2)+1; i<D.length(); i++){
        right.insertBefore(D.moveNext());
     }
     right.insertBefore(D.back());

     //cout<<"right: "<<right<<endl;
     left.moveFront();
     right.moveFront();
     for(int i = 0; i<right.length()-1; i++){
        left.insertBefore(right.moveNext());
        left.moveNext();
     }
     left.insertBefore(right.back());
     
     //cout<<"combined: "<<left<<endl;
     D = left;

 }
}

int main(int argc, char* argv[]){
  if (argc != 2) {
    throw std::invalid_argument("Shuffle: Please provide one integer deck size.");
  }
  int deckSize = stoi(argv[1]);
  int shuffleCount;
  //printf("Deck Size: %d\n", deckSize); 

  List deck;
  List deckCopy;
  printf("deck size\tshuffle count\n");
  printf("------------------------------\n");
  for(int i = 0; i<deckSize; i++){
    deck.insertBefore(i);
    deckCopy = deck;
    shuffleCount = 0;
    do{ 
        shuffleCount++;
        shuffle(deckCopy);
    }while(!deck.equals(deckCopy));
    printf(" %d\t\t %d\n", i+1, shuffleCount);
  }
  return 0;
}
