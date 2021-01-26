#ifndef GRAPH_H
#define GRAPH_H
#include "definitions.h"

#define INF 134217729		/* 2^27 + 1 */

typedef struct _edge Edge;

typedef struct _graph Graph;

/*******************************************
	Func: g_init()
	Arguments: item table
			   number of vertices
	Return Value: Graph pointer
	Side Effects: Allocates memory for graph
				  and its adjacent list table
*******************************************/
Graph *g_init(Item *items, unsigned int size);

/*******************************************
	Func: g_getV()
	Arguments: Graph pointer
	Return Value: number of vertices
	Side Effects: ---
*******************************************/
int g_getV(Graph *g);

/*******************************************
	Func: g_getItemAt()
	Arguments: Graph pointer
			   Index
	Return Value: Item at index
	Side Effects: ---
*******************************************/
Item g_getItemAt(Graph *g, int idx);

/*******************************************
	Func: g_getItems()
	Arguments: Graph pointer
	Return Value: Item array
	Side Effects: ---
*******************************************/
Item *g_getItems(Graph *g);

/*******************************************
	Func: g_createEdge()
	Arguments: Vertex
			   Weight
	Return Value: Edge
	Side Effects: Allocates memory for new
				  Edge
*******************************************/
Edge *g_createEdge(unsigned int v, unsigned int w);

/*******************************************
	Func: g_insert()
	Arguments: Graph pointer
			   Edge
			   Vertex
	Return Value: Graph pointer
	Side Effects: Allocates memory for new
				  Edge node
*******************************************/
Graph *g_insert(Graph *g, Edge *e, unsigned int vertex);

/*******************************************
	Func: g_getWeight()
	Arguments: Edge
	Return Value: weight of the edge
	Side Effects: ---
*******************************************/
unsigned int g_getWeight(Edge *e);

/*******************************************
	Func: g_getVertex()
	Arguments: Edge
	Return Value: vertex of the edge
	Side Effects: ---
*******************************************/
unsigned int g_getVertex(Edge *e);

/*******************************************
	Func: g_findShortest()
	Arguments: Graph pointer
			   Start vertex
			   End vertex
			   Search tree
			   mutations allowed
			   heuristic function
	Return Value: path weight
	Side Effects: ---

	finds the shortest path in the graph
	between the two vertices using a
	heuristic function
*******************************************/
int g_findShortest(Graph *g, unsigned int startV, unsigned int endV, int *st, int mutations, int heuristic(Item, Item));

/*******************************************
	Func: g_freeEdge()
	Arguments: Item 
	Return Value: ---
	Side Effects: Free's memory occupied by
				  Edge
*******************************************/
void g_freeEdge(Item e);

/*******************************************
	Func: g_destroy()
	Arguments: Graph pointer
			   freeItems function
	Return Value: NULL
	Side Effects: Free's memory occupied by
				  Graph
*******************************************/
Graph *g_destroy(Graph *g, void freeItems(Item *, int size));

#endif