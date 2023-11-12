/***
 * Isabella Phung
 * itphung
 * 2023 Fall CSE 101 PA5
 * List.cpp
 * List ADT in C++
 ***/

// List.cpp
// Implementation file for List ADT

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
   frontDummy = new Node(-1);
   backDummy = new Node(-1);
   beforeCursor = frontDummy;
   afterCursor = backDummy;
   pos_cursor = 0;
   num_elements = 0;
}

// Copy Constructor.
List::List(const List& L){
   // make this an empty List
   frontDummy = new Node(-1);
   backDummy = new Node(-1);
   beforeCursor = frontDummy;
   afterCursor = backDummy;
   pos_cursor = 0;
   num_elements = 0;

   // load elements of L into this L
   if(L.length()!=0){
    Node* N = L.backDummy->prev;
    while( N->prev!=nullptr ){
      this->insertAfter(N->data);
      N = N->prev;
    }
   }
   
   //std::cout << L.to_string(); 
   //std::cout << this->to_string(); 
}

// Destructor
List::~List(){
    clear();
    delete frontDummy;
    delete backDummy;
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
            throw std::length_error("List: front(): empty list");
        }
        return(frontDummy->next->data);
   }

   // back()
   // Returns the back element in this List.
   // pre: length()>0
   ListElement List::back() const{
        if(num_elements <= 0){
            throw std::length_error("List: back(): empty list");
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
            throw std::range_error("List: peekNext(): cursor at back");
        }
        return afterCursor->data;
   }

   // peekPrev()
   // Returns the element before the cursor.
   // pre: position()>0
   ListElement List::peekPrev() const{
        if(pos_cursor <= 0){
            throw std::range_error("List: peekPrev(): cursor at front");
        }
        return beforeCursor->data;
   }


   // Manipulation procedures -------------------------------------------------

   // clear()
   // Deletes all elements in this List, setting it to the empty state.
   void List::clear(){
     this -> moveFront();
     while(num_elements != 0){
         this->eraseAfter();   
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
            throw std::range_error("List: moveNext(): cursor at back");
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
            throw std::range_error("List: movePrev(): cursor at front");
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
        num_elements++;
        //std::cout << this->to_string(); 
        //printf("\nx: %d frontDummy->next: %d\n", x, frontDummy->next->data);  
        //printf("x: %d backDummy->prev: %d\n", x, backDummy->prev->data);
        
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
        pos_cursor++;
        num_elements++;
        //std::cout << this->to_string(); 
        //printf("\nx: %d frontDummy->next: %d\n", x, frontDummy->next->data);  
        //printf("x: %d backDummy->prev: %d\n", x, backDummy->prev->data);
   }

   // setAfter()
   // Overwrites the List element after the cursor with x.
   // pre: position()<length()
   void List::setAfter(ListElement x){
        if(pos_cursor >= num_elements){
            throw std::range_error("List: setAfter(): cursor at back");
        }
        
        afterCursor->data = x;
   }

   // setBefore()
   // Overwrites the List element before the cursor with x.
   // pre: position()>0
   void List::setBefore(ListElement x){
        if(pos_cursor <= 0){
            throw std::range_error("List: setBefore(): cursor at front");
        }
        
        beforeCursor -> data = x;
   }

   // eraseAfter()
   // Deletes element after cursor.
   // pre: position()<length()
   void List::eraseAfter(){
        if(pos_cursor >= num_elements){
            throw std::range_error("List: eraseAfter(): cursor at back");
        }
        Node* N = afterCursor;
        afterCursor = afterCursor->next;
        beforeCursor->next = afterCursor;
        afterCursor->prev = beforeCursor;
        num_elements--;
        delete N;
        //std::cout << this->to_string(); 
        //printf("\nfrontDummy->next: %d\n", frontDummy->next->data);  
        //printf("backDummy->prev: %d\n", backDummy->prev->data);

   }

   // eraseBefore()
   // Deletes element before cursor.
   // pre: position()>0
   void List::eraseBefore(){
        //printf("pos_cursor: %d\n", pos_cursor);
        //printf("num_elements: %d\n", num_elements);
        if(pos_cursor <= 0){
            throw std::range_error("List: eraseBefore(): cursor at front");
        }
        Node* N = beforeCursor;
        beforeCursor = beforeCursor->prev;
        afterCursor->prev = beforeCursor;
        beforeCursor->next = afterCursor;
        num_elements--;
        pos_cursor--;
        delete N;
        //std::cout << this->to_string(); 
        //printf("\nfrontDummy->next: %d\n", frontDummy->next->data);  
        //printf("backDummy->prev: %d\n", backDummy->prev->data);

   }


   // Other Functions ---------------------------------------------------------

   // findNext()
   // Starting from the current cursor position, performs a linear search (in 
   // the direction front-to-back) for the first occurrence of element x. If x
   // is found, places the cursor immediately after the found element, then 
   // returns the final cursor position. If x is not found, places the cursor 
   // at position length(), and returns -1. 
   int List::findNext(ListElement x){
        int steps = 0;
        Node* N = beforeCursor; 
        while(N->next != backDummy){
            steps++;
            N = N -> next;
            if(N->data == x){
                beforeCursor = N;
                afterCursor = N->next;
                pos_cursor+= steps;
                return pos_cursor;
            }
        }
        beforeCursor = backDummy -> prev;
        afterCursor = backDummy;
        pos_cursor = num_elements;
        return -1;
   }

   // findPrev()
   // Starting from the current cursor position, performs a linear search (in 
   // the direction back-to-front) for the first occurrence of element x. If x
   // is found, places the cursor immediately before the found element, then
   // returns the final cursor position. If x is not found, places the cursor 
   // at position 0, and returns -1. 
   int List::findPrev(ListElement x){
        Node* N = afterCursor; 
        int steps = 0; 
        while(N->prev != frontDummy){
            steps++;
            N = N -> prev;
            if(N->data == x){
                beforeCursor = N->prev;
                afterCursor = N;
                pos_cursor-=steps;
                return pos_cursor;
            }
        }
        beforeCursor = frontDummy;
        afterCursor = frontDummy->next;
        pos_cursor = 0;
        return -1;
   }

   // cleanup()
   // Removes any repeated elements in this List, leaving only unique elements.
   // The order of the remaining elements is obtained by retaining the frontmost 
   // occurrance of each element, and removing all other occurances. The cursor 
   // is not moved with respect to the retained elements, i.e. it lies between 
   // the same two retained elements that it did before cleanup() was called.
   void List::cleanup(){
        Node* N = frontDummy;
        Node* M;
        Node* temp;
        int i;
        while(N->next != backDummy){
            i = 0;
            N = N->next;
            M = N;
            while(M->next != backDummy && M != backDummy){
                M = M->next;
                i++;
                if(N->data == M->data){
                   temp = M;
                   M->prev->next = M->next;
                   M->next->prev = M->prev;
                   M = M->next;
                   num_elements--;
                   delete temp;
                   if(pos_cursor >= i){
                        i--;
                        pos_cursor--;
                   }
                }
            }
        }
   }
 
   // concat()
   // Returns a new List consisting of the elements of this List, followed by
   // the elements of L. The cursor in the returned List will be at postion 0.
   List List::concat(const List& L) const{
        List M;
        Node* N = this->frontDummy;
        while( N->next!=backDummy ){
            N = N->next;
            M.insertBefore(N->data);
        }
        N = L.frontDummy;
        while(N->next != L.backDummy){
            N = N->next;
            M.insertBefore(N->data);
        }
        M.moveFront();
        return M;
   }

   // to_string()
   // Returns a string representation of this List consisting of a comma 
   // separated sequence of elements, surrounded by parentheses.
   std::string List::to_string() const{
        Node* N = nullptr;
        std::string s = "(";
        N=frontDummy;;
        while(N->next!=backDummy){
            N=N->next;
            if(N->next != backDummy){
                s += std::to_string(N->data) + ", ";
            }else{
                s += std::to_string(N->data) + ")";
            }
        }
        return s;
   }

   // equals()
   // Returns true if and only if this List is the same integer sequence as R.
   // The cursors in this List and in R are unchanged.
   bool List::equals(const List& R) const{
        //printf("E elements: %d\n", num_elements);
        //printf("A elements: %d\n", R.num_elements);
        if(this->num_elements != R.num_elements){
            return false;
        }
        Node* n = this->frontDummy->next;
        Node* m = R.frontDummy->next;
        while(n!=backDummy){
            if(n->data != m->data){
                return false;
            }
            n = n->next;
            m = m->next;
        }
        return true;
   }


   // Overriden Operators -----------------------------------------------------
   
   // operator<<()
   // Inserts string representation of L into stream.
   std::ostream& operator<<( std::ostream& stream, const List& L ){
        return stream << L.to_string();
   }

   // operator==()
   // Returns true if and only if A is the same integer sequence as B. The 
   // cursors in both Lists are unchanged.
   bool operator==( const List& A, const List& B ){
        return A.equals(B); 
   }

   // operator=()
   // Overwrites the state of this List with state of L.
   List& List::operator=( const List& L ){
        if(this != &L){
            List temp = L;
            std::swap(frontDummy, temp.frontDummy);
            std::swap(backDummy, temp.backDummy);
            std::swap(beforeCursor, temp.beforeCursor);
            std::swap(afterCursor, temp.afterCursor);
            std::swap(pos_cursor, temp.pos_cursor);
            std::swap(num_elements, temp.num_elements);
        }
        return *this;
   }

