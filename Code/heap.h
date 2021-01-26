#ifndef HEAP_H
#define HEAP_H

typedef struct _h_node h_node;

typedef h_node *Heap;

/******************************************
	Func: h_init()
	Arguments: Size
	Return type: ---
	Side Effects: Allocates memory for heap
				  table
******************************************/
void h_init(unsigned int size);

/******************************************
	Func: h_reset()
	Arguments: ---
	Return type: ---
	Side Effects: ---

	resets heap, by making it believe it
	is empty
******************************************/
void h_reset();

/******************************************
	Func: h_insert()
	Arguments: integer
	Return type: ---
	Side Effects: ---

	inserts keyg and keyf in the first 
	free position
******************************************/
void h_insert(int key);

/******************************************
	Func: h_getKeyg()
	Arguments: integer
	Return type: keyg
	Side Effects: ---

	gets the keyg in t
******************************************/
int h_getKeyg(int t);


/******************************************
	Func: h_getKeyf()
	Arguments: integer
	Return type: keyf
	Side Effects: ---

	gets the keyf in t
******************************************/
int h_getKeyf(int t);

/******************************************
	Func: h_setKey()
	Arguments: integer
			   integer
	Return type: ---
	Side Effects: ---

	sets the keyg in t
******************************************/
void h_setKeyg(int t, int key);

/******************************************
	Func: h_setKey()
	Arguments: integer
			   integer
	Return type: ---
	Side Effects: ---

	sets the keyf in t
******************************************/
void h_setKeyf(int t, int key);

/******************************************
	Func: h_delMin()
	Arguments: table pos
	Return type: Member at top of binary tree
	Side Effects: ---

	Removes the top priority member of the heap
******************************************/
int h_delMin(int *pos);

/******************************************
	Func: h_fixDown()
	Arguments: integer
			   table pos
	Return type: ---
	Side Effects: ---

	Fixes the heap, in which "t" had it's
	priority decreased
******************************************/
void h_fixDown(int t, int *pos);

/******************************************
	Func: h_fixup()
	Arguments: integer
			   table pos
	Return type: ---
	Side Effects: ---

	Fixes the heap, in which "t" had it's
	priority increased
******************************************/
void h_fixUp(int t, int *pos);

/******************************************
	Func: h_empty()
	Arguments: ---
	Return type: 1 if not empty, 0 otherwise
	Side Effects: ---
******************************************/
int h_empty();

/******************************************
	Func: h_destroy()
	Arguments: ---
	Return type: ---
	Side Effects: Free's memory occupied by
	   			  Heap
******************************************/
void h_destroy();
#endif