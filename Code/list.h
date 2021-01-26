#ifndef LIST_H
#define LIST_H

#include "definitions.h"

typedef struct _list List;

/*************************************************
	Func: l_init()
	Arguments:	---
	Return Value: NULL 	
	Side Efects: ---

	Initializes the list pointer to NULL.
*************************************************/
List *l_init();

/*************************************************
	Func: l_insert()
	Arguments: list pointer
	   		   Item
	Return Value: list pointer 
	Side Efects: Allocates memory for new node 
				 containing Item

	Inserts element at the beginning of the list
*************************************************/
List *l_insert(List *l, Item item);

/*************************************************
	Func: l_getNext()
	Arguments: list pointer
	Return Value: list pointer to next node
	Side Efects: ---
*************************************************/
List *l_getNext(List *l);

/*************************************************
	Func: l_getItem()
	Arguments: list pointer
	Return Value: Item pointed by argument
	Side Efects: ---
*************************************************/
Item l_getItem(List *l);

/*************************************************
	Func: l_remove()
	Arguments: list pointer	
			   freeItem function
	Return Value: list pointer
	Side Efects: Free's memory occupied by first
				element of the list
*************************************************/							
List *l_remove(List *l, void (*freeItem)(Item));

/*************************************************
	Func: l_find()
	Arguments: list pointer
			   Item
			   test function
	Return Value: list pointer or NULL if not found
	Side Efects: ---

	Searches the list for Item using the test 
	function
*************************************************/									
List *l_find(List *l, Item item, int (*test)(Item, Item));

/*************************************************
	Func: l_getAt()
	Arguments: list pointer
			   index
	Return Value: node at given index
	Side Efects: ---

	Note: Index begins at 0
*************************************************/
List *l_getAt(List *l, unsigned int index);

/*************************************************
	Func: l_destroy()
	Arguments: list pointer
			   freeItem function
	Return Value: NULL
	Side Efects: Free's memory occupied by list
*************************************************/
List *l_destroy(List *l, void (*freeItem)(Item));

#endif