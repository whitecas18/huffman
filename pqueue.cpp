// CSCI 2530
// Assignment: 6
// Author:     Cason White
// File:       pqueue.cpp
// Tab stops:  8

// pqueue is a tool that is meant to be used as part of a
// larger application.
//
// pqueue's main usage is in creating lists of objects, of type
// ItemType, which are sorted in terms of type PriorityType in
// an order from lowest to highest.
//
// The type definition of both ItemType and PriorityType can be
// easily changed by modifying the cooresponding lines in pqueue.h.
//
// pqueue.cpp can perform the following actions:
//
// It can create a variable q of type PriorityQueue, as follows.
// PriorityQueue q; - The PriorityQueue is initially empty.
//
// It can use the following functions:
//
// Function isEmpty(q), which is true if the PriorityQueue is empty
// and false otherwise.
//
// Function insert(q, x, p), which inserts item x with priority p into q.
//
// Function remove(q, item, pri), which removes the item that has the
// smallest priority from q, and stores the priority and item
// in the cooresponding out-parameters pri and item.
//
// Function printPriorityQueue(q, printItem, printPriority) prints
// the contents of priority queue q in a readable format for debugging.
// Parameters printItem and printPriority are functions. PrintPriorityQueue uses
// printItem(x) to print item x and uses printPriority(p) to print priority p. 

#include <cstdio>
#include <cstdlib>
#include "pqueue.h"

using namespace std;


// An object of type PQCell represents one Cell in the PriorityQueue.
// The fields are:
//
//    item	The item which is stored in the cell.
//
//    priority  The priority of the cell.
//
//    tail      A pointer to the next cell in the PriorityQueue.

struct PQCell
{
	ItemType item;
	PriorityType priority;
	PQCell* tail;
    
	PQCell(ItemType x, PriorityType p, PQCell* t)
		{
			item = x;
			priority = p;
			tail = t;
		}
};


// Function isEmpty(q) returns true if q is an empty priority queue.

bool isEmpty(const PriorityQueue& q)
{
	return q.list == NULL;
}



// insertCell(L, x, p) inserts a cell
// into PriorityQueue L with item x and priority p.

void insertCell(PQCell*& L, ItemType x, PriorityType p)
{
	if(L == NULL || p <= L->priority)
	{
		L = new PQCell(x, p, L);
	}
	else
	{
		insertCell(L->tail, x, p);
	}
}


// Function insert(q, x, p) inserts item x with priority p into q.

void insert(PriorityQueue& q, ItemType x, PriorityType p)
{
	
	insertCell(q.list, x, p);
}


// Function printPriorityQueue(q, printItem, printPriority) prints
// the contents of priority queue q in a readable format for debugging.
// Parameters printItem and printPriority are functions. PrintPriorityQueue uses
// printItem(x) to print item x and uses printPriority(p) to print priority p.

void printPriorityQueue(const PriorityQueue& q,
			ItemPrinter printItem,
			PriorityPrinter printPriority)
{
	PQCell* ptr = q.list;
	if(!isEmpty(q))
	{
		PriorityQueue x;
		x.list = ptr->tail;
	
		if(ptr->tail == NULL)
		{	
			printItem(ptr->item);
			printf(" ");
			printPriority(ptr->priority);
			printf("\n");

		}
		else
		{
			printItem(ptr->item);
			printf(" ");
			printPriority(ptr->priority);
			printf("\n");
			printPriorityQueue(x, printItem, printPriority);
		}
	}
	else
	{
		printf("There is nothing in the list\n");
	}
}


// Function remove(q, item, pri) removes the item that has the smallest priority
// from q, and stores the priority and item
// in the cooresponding out-parameters pri and item.

void remove(PriorityQueue& q, ItemType& item, PriorityType& pri)
{
	if(!isEmpty(q))
	{
		PQCell* ptr = q.list;
		item = ptr->item;
		pri = ptr->priority;
		q.list = ptr->tail;
		delete ptr;

	}
	else
	{

		exit(1);
	}
}
	    
