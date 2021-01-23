// CSCI 2530
// Assignment: 6
// Author:     Cason White
// File:       pqueue.h
// Tab stops:  8

#include "tree.h"

// ItemType represents the type of item stored in each cell, and can
// be changed here.

typedef Tree ItemType;


// PriorityType represents the type of priority stored in each cell, and can
// be changed here.

typedef int  PriorityType;


typedef void (*ItemPrinter)(ItemType);
typedef void (*PriorityPrinter)(PriorityType);

struct PQCell;


// An object of type PriorityQueue represents the entirety of a list
// of prioritised objects.
//
// The only field is:
//
//    list      A pointer to the first cell in the list.

struct PriorityQueue
{
	PQCell* list;

	PriorityQueue()
		{
			list = NULL;
		}
};
    
bool isEmpty(const PriorityQueue& q);

void insert(PriorityQueue& q, ItemType x, PriorityType p);

void remove(PriorityQueue& q, ItemType& item, PriorityType& pri);

void printPriorityQueue(const PriorityQueue& q,
                          ItemPrinter printItem,
                          PriorityPrinter printPriority);


