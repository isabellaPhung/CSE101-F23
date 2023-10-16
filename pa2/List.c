// Isabella Phung
// Student ID: 1702285
// Assignment: pa1
// for CSE 101 Fall 2023
// contains code from examples provided by instructor

//-----------------------------------------------------------------------------
// List.c
// Implementation file for List ADT
//-----------------------------------------------------------------------------
#include "List.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// structs --------------------------------------------------------------------

// private Node type
typedef struct NodeObj *Node;

// private NodeObj type
typedef struct NodeObj {
  ListElement data;
  Node next;
  Node prev;
} NodeObj;

// private ListObj type
typedef struct ListObj {
  Node front;
  Node back;
  int length;
  Node cursor;
  int cursorIndex;
} ListObj;

// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
Node newNode(ListElement data) {
  Node N = malloc(sizeof(NodeObj));
  assert(N != NULL);
  N->data = data;
  N->next = NULL;
  N->prev = NULL;
  return (N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeNode(Node *pN) {
  if (pN != NULL && *pN != NULL) {
    free(*pN);
    *pN = NULL;
  }
}

// newList()
// Returns reference to new empty List object.
// default behavior: front and back are set as Null
List newList() {
  List L;
  L = malloc(sizeof(ListObj));
  assert(L != NULL);         // checks allocation is not null
  L->front = L->back = NULL; // default: front and back are null
  L->length = 0;
  L->cursor = NULL;
  L->cursorIndex = -1; // cursor and cursor index set to undefined
  return (L);
}

// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.
void freeList(List *pL) {
  if (pL != NULL && *pL != NULL) { // checks if list is empty
    while (!isEmpty(*pL)) {
      deleteFront(*pL);
    }
    free(*pL);
    *pL = NULL; // dereferences pL and pointer to null
  }
}

// Access functions -----------------------------------------------------------

// length()
// Returns the length of L.
int length(List L) {
  if (L == NULL) {
    printf("List Error: calling length() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  return (L->length);
}

// index()
// returns index of cursor element if defined
// returns -1 otherwise
int index(List L) {
  if (L != NULL && L->cursor != NULL) {
    return (L->cursorIndex);
  }
  return (-1);
}

// front()
// Returns the value at the front of L.
// Pre: !isEmpty(L)
ListElement front(List L) {
  if (L == NULL) { // checks if empty list
    printf("List Error: calling front() on NULL List reference\n");
    exit(EXIT_FAILURE); // exits out of program
  }
  if (isEmpty(L)) {
    printf("List Error: calling front() on an empty List\n");
    exit(EXIT_FAILURE);
  }
  return (L->front->data); // returns data of front, not front pointer
}

// back()
// Returns the value at the back of L
// Pre: !isEmpty(L)
ListElement back(List L) {
  if (L == NULL) {
    printf("List Error: calling back() on Null List reference\n");
    exit(EXIT_FAILURE);
  }
  if (isEmpty(L)) {
    printf("List Error: calling front() on an empty List\n");
    exit(EXIT_FAILURE);
  }
  return (L->back->data); // returns data of back, not back pointer
}

// get()
// Returns value at cursor element L.
// Pre: !isEmpty(L), index()>=0
ListElement get(List L) {
  if (L == NULL) {
    printf("List Error: calling get() on Null List reference\n");
    exit(EXIT_FAILURE);
  }
  if (isEmpty(L)) {
    printf("List Error: calling get() on an empty List\n");
    exit(EXIT_FAILURE);
  }

  if (index(L) < 0) {
    printf("List Error: calling get() on an undefined cursor\n");
    exit(EXIT_FAILURE);
  }
  return (L->cursor->data);
}

// equals()
// Returns true if A is same int sequence as B, false otherwise.  bool
// equals(List A, List B){
bool equals(List A, List B) {
  if (A == NULL || B == NULL) {
    printf("List Error: calling equals() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }

  bool eq;
  Node N, M;

  eq = (A->length == B->length);
  N = A->front;
  M = B->front;
  while (eq && N != NULL) {
    eq = (N->data == M->data);
    N = N->next;
    M = M->next;
  }
  return eq;
}

// isEmpty()
// Returns true if L is empty, otherwise returns false.
bool isEmpty(List L) {
  if (L == NULL) {
    printf("List Error: calling isEmpty() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  return (L->length == 0);
}

// Manipulation procedures ----------------------------------------------------

// clear()
// Resets L to its original empty state
void clear(List L) {
  if (L != NULL) { // checks if list is null
    while (!isEmpty(L)) {
      deleteFront(L);
    }
    L->cursor = NULL;
    L->cursorIndex = -1;
  }
}

// set()
// Overwrites cursor element data with x
// Pre: !isEmpty(), index() >= 0
void set(List L, int x) {
  if (L == NULL) { // checks if empty list
    printf("List Error: calling set() on NULL List reference\n");
    exit(EXIT_FAILURE); // exits out of program
  }
  if (isEmpty(L)) {
    printf("List Error: calling set() on an empty List\n");
    exit(EXIT_FAILURE);
  }
  if (index(L) < 0) {
    printf("List Error: calling set() on an undefined cursor.\n");
    exit(EXIT_FAILURE);
  }
  L->cursor->data = x;
}

// moveFront()
// If L is non-empty, sets cursor to front element
// otherwise, does nothing
void moveFront(List L) {
  if (L != NULL && !isEmpty(L)) {
    L->cursor = L->front;
    L->cursorIndex = 0;
    // printf("%d", L->cursor->data);
  }
}

// moveBack()
// If L is non-empty, sets cursor to back element
// otherwise, does nothing
void moveBack(List L) {
  if (L != NULL && !isEmpty(L)) {
    L->cursor = L->back;
    L->cursorIndex = L->length - 1;
  }
}

// movePrev()
// If cursor defined and not at front,
// move one step toward front of L;
// if cursor defined and at front, make undefined
// if cursor undefined, do nothing
void movePrev(List L) {
  if (L != NULL && L->cursor != NULL) { // checks if list or cursor are null
    if (L->cursor == L->front) {        // if cursor at front
      L->cursor = NULL;
      L->cursorIndex = -1;
    } else {
      L->cursor = L->cursor->prev;
      L->cursorIndex--;
    }
  }
}

// moveNext()
// If cursor defined and not at back,
// move one step toward back of L;
// if cursor defined and at back, make undefined
// if cursor undefined, do nothing
void moveNext(List L) {
  if (L != NULL && L->cursor != NULL) { // checks if list or cursor are null
    if (L->cursor == L->back) {         // if cursor at back
      L->cursor = NULL;
      L->cursorIndex = -1;
    } else {
      L->cursor = L->cursor->next;
      L->cursorIndex++;
    }
  }
}

// prepend()
// Places new data at the front of L.
void prepend(List L, ListElement data) {
  Node N = newNode(data);

  if (L == NULL) {
    printf("List Error: calling prepend() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }

  if (isEmpty(L)) { // if list is empty, sets front and back to new node
    L->front = L->back = N;
  } else {              // else,
    L->front->prev = N; // sets front node's prev to be N
    N->next = L->front; // sets N's next to front node
    L->front = N;       // sets N as new front
    if (L->cursorIndex != -1) {
      L->cursorIndex++;
    }
  }
  L->length++;
}

// append()
// Places new data at the back of L.
void append(List L, ListElement data) {
  Node N = newNode(data);

  if (L == NULL) {
    printf("List Error: calling append() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }

  if (isEmpty(L)) { // if list is empty, sets front and back to new node
    L->front = L->back = N;
  } else {             // else,
    L->back->next = N; // sets back node's next to be N
    N->prev = L->back; // sets N's prev to back node
    L->back = N;       // sets N as new back
  }
  L->length++;
}

// insertBefore()
// Insert new element before cursor.
// Pre: !isEmpty(), index() >= 0
void insertBefore(List L, ListElement x) {
  if (L == NULL) {
    printf("List Error: calling insertBefore() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if (isEmpty(L)) {
    printf("List Error: calling insertBefore() on an empty List\n");
    exit(EXIT_FAILURE);
  }
  if (index(L) < 0) {
    printf("List Error: calling insertBefore() on an undefined cursor.\n");
    exit(EXIT_FAILURE);
  }

  if (index(L) == 0) { // if cursor at front, prepend
    prepend(L, x);
  } else {
    Node N = newNode(x);
    Node before = L->cursor->prev; // node before cursor
    before->next = N;
    N->prev = before;
    N->next = L->cursor;
    L->cursor->prev = N;
    L->length++;
    L->cursorIndex++;
  }
}

// insertAfter()
// Insert new element after cursor.
// Pre: !isEmpty(), index() >= 0
void insertAfter(List L, ListElement x) {
  if (L == NULL) {
    printf("List Error: calling insertAfter() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if (isEmpty(L)) {
    printf("List Error: calling insertAfter() on an empty List\n");
    exit(EXIT_FAILURE);
  }
  if (index(L) < 0) {
    printf("List Error: calling insertAfter() on an undefined cursor.\n");
    exit(EXIT_FAILURE);
  }

  if (L->cursor == L->back) { // if cursor at back, append
    append(L, x);
  } else {
    Node N = newNode(x);
    Node after = L->cursor->next; // node after cursor
    after->prev = N;
    N->next = after;
    N->prev = L->cursor;
    L->cursor->next = N;
    L->length++;
  }
}

// deleteFront()
// Deletes data at front of L.
// Pre: !isEmpty(L)
void deleteFront(List L) {
  Node N = NULL;

  if (L == NULL) {
    printf("List Error: calling deleteFront() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if (isEmpty(L)) {
    printf("List Error: calling deleteFront() on an empty List\n");
    exit(EXIT_FAILURE);
  }
  if (L->cursor == L->front) {
    L->cursor = NULL;
    L->cursorIndex = -1;
  }
  N = L->front; // gives deleted node temp name
  if (length(L) > 1) {
    L->front = L->front->next; // sets front to next value after deleted node
    L->front->prev = NULL;     // sets new front's prev to be null
  } else {
    L->front = L->back = NULL; // if list is only length 1, make empty by
                               // setting front and back to null
  }
  L->length--;
  if (L->cursorIndex != -1) {
    L->cursorIndex--;
  }

  freeNode(&N);
}

// deleteBack()
// Deletes data at back of L.
// Pre: !isEmpty(L)
void deleteBack(List L) {
  Node N = NULL;

  if (L == NULL) {
    printf("List Error: calling deleteBack() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if (isEmpty(L)) {
    printf("List Error: calling deleteBack() on an empty List\n");
    exit(EXIT_FAILURE);
  }

  if (L->cursor == L->back) {
    L->cursor = NULL;
    L->cursorIndex = -1;
  }

  N = L->back; // gives deleted node temp name
  if (length(L) > 1) {
    L->back = L->back->prev; // sets back to prev value before deleted node
    L->back->next = NULL;    // sets new back's next to be null
  } else {
    L->front = L->back = NULL; // if list is only length 1, make empty by
                               // setting front and back to null
  }
  L->length--;
  /**
  if(L->cursorIndex != -1){
    L->cursorIndex--;
  }
**/
  freeNode(&N);
}

// delete()
// deletes cursor element, makes cursor undefined
// Pre: !isEmpty(), index()>=0
void delete(List L) {
  Node N = NULL;
  if (L == NULL) {
    printf("List Error: calling delete() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if (isEmpty(L)) {
    printf("List Error: calling delete() on an empty List\n");
    exit(EXIT_FAILURE);
  }
  if (index(L) < 0) {
    printf("List Error: calling delete() on an undefined cursor.\n");
    exit(EXIT_FAILURE);
  }

  if (L->front ==
      L->cursor) { // checks if cursor is at front, performs deleteFront if true
    deleteFront(L);
  } else if (L->back == L->cursor) { // checks if cursor is at back, performs
                                     // deleteBack if true
    deleteBack(L);
  } else {
    N = L->cursor;         // gives deleted node temp name
    Node before = N->prev; // node before cursor
    Node after = N->next;  // node after cursor
    if (length(L) > 1) {
      before->next = after; // sets before's next to be node after cursor
      after->prev = before; // sets after's prev to node before cursor
    }
    L->cursor = NULL;
    L->cursorIndex = -1;
    L->length--;
    freeNode(&N);
  }
}

// Other Functions ------------------------------------------------------------

// printList()
// Prints a string representation of L consisting of a space separated list
// of ints to indicated file out.
void printList(FILE *out, List L) {
  Node N = NULL;

  if (L == NULL) {
    printf("List Error: calling printList() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }

  for (N = L->front; N != NULL; N = N->next) {
    if(N->next != NULL){
        fprintf(out, FORMAT " ", N->data);
    }else{
        fprintf(out, FORMAT, N->data);
    }
  }
  fprintf(out, "\n");
}

// copyList()
// Returns new List representing same integer sequence as given L.
// Cursor in new list undefined. L is unchanged.
List copyList(List L) {
  if (L == NULL) {
    printf("List Error: calling copyList() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }

  List B = newList();
  if (isEmpty(L)) {
    return B;
  }
  Node N = L->front;
  for (int i = 0; i < L->length; i++) {
    append(B, N->data);
    N = N->next;
  }
  return B;
}
