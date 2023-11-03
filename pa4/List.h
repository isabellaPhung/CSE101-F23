/***
 * Isabella Phung
 * itphung
 * 2023 Fall CSE 101 PA4
 * List.h
 * Header file for List ADT
 ***/

//-----------------------------------------------------------------------------
// List.h
// Header file for List ADT
//-----------------------------------------------------------------------------
#ifndef LIST_H_INCLUDE_
#define LIST_H_INCLUDE_
#include <stdbool.h>
#include <stdio.h>

//#define FORMAT "%d" // format string for ListElement

// Exported types -------------------------------------------------------------
typedef void* ListElement;
typedef struct ListObj *List;

// Constructors-Destructors ---------------------------------------------------

// newList()
// Returns reference to new empty List object.
List newList();

// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.
void freeList(List *pL);

// Access functions -----------------------------------------------------------

// length()
// Returns the length of L.
int length(List L);

// index()
// Returns index of cursor element if defined, -1 otherwise
int index(List L);

// front()
// Returns the value at the front of L.
// Pre: !isEmpty(L)
ListElement front(List L);

// back()
// Returns value at back of L.
// Pre: !isEmpty(L)
ListElement back(List L);

// get()
// Returns cursor element of L.
// Pre: !isEmpty(L), index()>=0
ListElement get(List L);

// equals()
// Returns true if A is same int sequence as B, false otherwise.
//bool equals(List A, List B);

// isEmpty()
// Returns true if L is empty, otherwise returns false.
bool isEmpty(List L);

// Manipulation procedures ----------------------------------------------------

// clear()
// Resets L to its original empty state
void clear(List L);

// set()
// Overwrites cursor element's data with x.
void set(List L, ListElement x);

// moveFront()
// If L is non-empty, sets cursor element as front
// otherwise does nothing.
void moveFront(List L);

// moveBack()
// If L is non-empty, sets cursor element as back
// otherwise does nothing.
void moveBack(List L);

// movePrev()
// If cursor is defined and not at front,
// move cursor 1 step toward front
// If cursor at front, set cursor undefined
// if cursor undefined, do nothing
void movePrev(List L);

// moveNext()
// If cursor is defined and not at back,
// move cursor 1 step toward back
// if cursor is at back, set cursor undefined
// if cursor undefined, do nothing
void moveNext();

// prepend()
// If list is non-empty, insert element before front element
void prepend(List L, ListElement x);

// append()
// Places new data at the back of L.
void append(List L, ListElement x);

// insertBefore()
// Insert new element before cursor
// Pre: !isEmpty, index()>=0
void insertBefore(List L, ListElement x);

// insertAfter()
// Insert new element after cursor
// Pre: !isEmpty, index()>=0
void insertAfter(List L, ListElement x);

// deleteFront()
// Deletes data at front of L.
// Pre: !isEmpty(L)
void deleteFront(List L);

// deleteBack()
// Deletes data at back of L.
// Pre: !isEmpty(L)
void deleteBack(List L);

// delete()
// Delete cursor element, makes cursor undefined
void delete(List L);

// Other Functions ------------------------------------------------------------

// printList()
// Prints a string representation of L consisting of a space separated list,
// with front on left of ints to file out.
//void printList(FILE *out, List L);

// copyList()
// Returns new list representing same integer sequence as L
// new list cursor is undefined, state of L unchanged
//List copyList(List L);

#endif
