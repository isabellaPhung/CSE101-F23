//-----------------------------------------------------------------------------
// List.cpp
// Implementation file for Queue ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"


// Private Constructor --------------------------------------------------------

// Node constructor
List::Node::Node(ListElement x){
   data = x;
   next = nullptr;
   prev = nullptr;
}


// Class Constructors & Destructors -------------------------------------------

// Creates a new Queue in the empty state.
List::List(){
   frontDummy = new Node(-1);;
   backDummy = new Node(-1);
   beforeCursor = frontDummy;
   afterCursor = backDummy;
   pos_cursor = 0;
   num_elements = 0;
}

// Copy Constructor.
List::List(const List& L){
   // make this an empty List
   frontDummy = nullptr;
   backDummy = nullptr;
   beforeCursor = nullptr;
   afterCursor = nullptr;
   pos_cursor = 0;
   num_elements = 0;

   // load elements of L into this L
   Node* N = L.frontDummy->next;
   while( N!=nullptr ){
      frontDummy->insertAfter(N->data);
      N = N->next;
   }
}

// Destructor
List::~List(){
   while( num_elements>0 ){
      //TODO:dequeue?
   }
}

   // Access functions --------------------------------------------------------

   // length()
   // Returns the length of this List.
   int List::length() const{
        return(num_elements);
   }

   // front()
   // Returns the front element in this List.
   // pre: length()>0
   ListElement List::front() const{
        if(num_elements <= 0){
            throw std::length_error("List: front(): empty List")
        }
        return(frontDummy->next);
   }

   // back()
   // Returns the back element in this List.
   // pre: length()>0
   ListElement List::back() const{
        if(num_elements <= 0){
            throw std::length_error("List: back(): empty List")
        }
        return(backDummy->prev);

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
            throw std::position_error("List: peekNext(): cursor position past or at end of list")
        }
        return afterCursor->data;
   }

   // peekPrev()
   // Returns the element before the cursor.
   // pre: position()>0
   ListElement List::peekPrev() const{
        if(pos_cursor <= 0){
            throw std::position_error("List: peekPrev(): cursor position less than or equal 0")
        }
        return beforeCursor->data;
   }


   // Manipulation procedures -------------------------------------------------

   // clear()
   // Deletes all elements in this List, setting it to the empty state.
   void List::clear(){
     this.moveFront();
     while(num_elements != 0){
         this.eraseAfter();   
     }
   }
   
   // moveFront()
   // Moves cursor to position 0 in this List.
   void List::moveFront(){
        pos_cursor = 0;
        beforeCursor = frontDummy;
        afterCursor = frontDummy->next;
   }

   // moveBack()
   // Moves cursor to position length() in this List.
   void List::moveBack(){
        pos_cursor = num_elements;
        afterCursor = backDummy;
        beforeCursor = backDummy->prev;
   }

   // moveNext()
   // Advances cursor to next higher position. Returns the List element that
   // was passed over. 
   // pre: position()<length() 
   ListElement List::moveNext(){
        if(pos_cursor >= num_elements){
            throw std::position_error("List: moveNext(): cursor position past or at end of List")
        }
        
        int data = afterCursor -> data;
        beforeCursor = afterCursor;
        afterCursor = afterCursor->next;
        pos_cursor++;
        return data;
   }

   // movePrev()
   // Advances cursor to next lower position. Returns the List element that
   // was passed over. 
   // pre: position()>0
   ListElement List::movePrev(){
        if(pos_cursor <= 0){
            throw std::position_error("List: movePrev(): cursor position at start or before list.")
        }
        int data = beforeCursor -> data;
        afterCursor=beforeCursor;
        beforeCursor = beforeCursor->prev;
        pos_cursor--;
        return data;
   }

   // insertAfter()
   // Inserts x after cursor.
   void List::insertAfter(ListElement x){
        Node* N = new Node(x);
        N->prev = beforeCursor;
        beforeCursor->next = N;
        N->next = afterCursor;
        afterCursor->prev = N;
        afterCursor = N;
   }

   // insertBefore()
   // Inserts x before cursor.
   void List::insertBefore(ListElement x){
        Node* N = new Node(x);
        N->prev = beforeCursor;
        beforeCursor->next = N;
        N->next = afterCursor;
        afterCursor->prev = N;
        beforeCursor = N;
   }

   // setAfter()
   // Overwrites the List element after the cursor with x.
   // pre: position()<length()
   void List::setAfter(ListElement x){
        if(pos_cursor >= num_elements){
            throw std::position_error("List: moveNext(): cursor position past or at end of List")
        }
        
        afterCursor->data = x;
   }

   // setBefore()
   // Overwrites the List element before the cursor with x.
   // pre: position()>0
   void List::setBefore(ListElement x){
        if(pos_cursor <= 0){
            throw std::position_error("List: movePrev(): cursor position at start or before list.")
        }
        
        beforeCursor -> data = x;
   }

   // eraseAfter()
   // Deletes element after cursor.
   // pre: position()<length()
   void List::eraseAfter(){
        if(pos_cursor >= num_elements){
            throw std::position_error("List: eraseAfter(): cursor position past or at end of List")
        }
        Node* N = afterCursor;
        afterCursor = afterCursor->next;
        beforeCursor->next = afterCursor;
        afterCursor->prev = beforeCursor;
        num_elements--;
        delete N;
   }

   // eraseBefore()
   // Deletes element before cursor.
   // pre: position()>0
   void List::eraseBefore(){
        if(pos_cursor <= num_elements){
            throw std::position_error("List: eraseBefore(): cursor position at start or before list.")
        }
        Node* N = beforeCursor;
        beforeCursor = beforeCursor->prev;
        afterCursor->prev = beforeCursor;
        beforeCursor->next = afterCursor;
        num_elements--;
        delete N;
   }


   // Other Functions ---------------------------------------------------------

   // findNext()
   // Starting from the current cursor position, performs a linear search (in 
   // the direction front-to-back) for the first occurrence of element x. If x
   // is found, places the cursor immediately after the found element, then 
   // returns the final cursor position. If x is not found, places the cursor 
   // at position length(), and returns -1. 
   int findNext(ListElement x);

   // findPrev()
   // Starting from the current cursor position, performs a linear search (in 
   // the direction back-to-front) for the first occurrence of element x. If x
   // is found, places the cursor immediately before the found element, then
   // returns the final cursor position. If x is not found, places the cursor 
   // at position 0, and returns -1. 
   int findPrev(ListElement x);

   // cleanup()
   // Removes any repeated elements in this List, leaving only unique elements.
   // The order of the remaining elements is obtained by retaining the frontmost 
   // occurrance of each element, and removing all other occurances. The cursor 
   // is not moved with respect to the retained elements, i.e. it lies between 
   // the same two retained elements that it did before cleanup() was called.
   void cleanup();
 
   // concat()
   // Returns a new List consisting of the elements of this List, followed by
   // the elements of L. The cursor in the returned List will be at postion 0.
   List concat(const List& L) const;

   // to_string()
   // Returns a string representation of this List consisting of a comma 
   // separated sequence of elements, surrounded by parentheses.
   std::string to_string() const;

   // equals()
   // Returns true if and only if this List is the same integer sequence as R.
   // The cursors in this List and in R are unchanged.
   bool equals(const List& R) const;


   // Overriden Operators -----------------------------------------------------
   
   // operator<<()
   // Inserts string representation of L into stream.
   friend std::ostream& operator<<( std::ostream& stream, const List& L );

   // operator==()
   // Returns true if and only if A is the same integer sequence as B. The 
   // cursors in both Lists are unchanged.
   friend bool operator==( const List& A, const List& B );

   // operator=()
   // Overwrites the state of this List with state of L.
   List& operator=( const List& L );

