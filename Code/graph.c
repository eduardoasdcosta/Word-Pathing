#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "heap.h"
#include "graph.h"

struct _edge 
{
	unsigned int v; 	/* adjacent vertex */
	unsigned int w;		/* weight of connection */
};

struct _graph
{
	unsigned int V;		/* vertex */
	Item *items;		/* table of items */
	List **adj;			/* table of adjacency lists */
};

Graph *g_init(Item *items, unsigned int size)
{
	int i;
	
	Graph *g = (Graph *) malloc( 1 * sizeof(Graph));	/* allocs memory for graph */
	if(g == (Graph *) NULL) exit(0);

	g->V = size;
	
	g->items = items;

	g->adj = (List **) malloc(size * sizeof(List*));	/* allocs memory for adjacency lists table */

	for(i = 0; i < size; i++) g->adj[i] = l_init();		/* initializes adjacency lists at NULL */

	return g;
}


int g_getV(Graph *g)
{
	return (g == (Graph *) NULL) ? 0 : g->V;
}


Item g_getItemAt(Graph *g, int idx)
{
	return g->items[idx];
}

Item *g_getItems(Graph *g)
{
	return g->items;
}

Edge *g_createEdge(unsigned int v, unsigned int w)
{
	Edge *e = (Edge *) malloc( 1 * sizeof(Edge));	/* allocs memory for edge */
	if( e == (Edge *) NULL) exit(0);

	e->v = v;
	e->w = w;

	return e;
}


Graph *g_insert(Graph *g, Edge *e, unsigned int vertex)
{
	g->adj[vertex] = l_insert(g->adj[vertex], (Item) e);

	return g;
}


unsigned int g_getWeight(Edge *e)
{
	return e->w;
}


unsigned int g_getVertex(Edge *e)
{
	return e->v;
}


int  g_findShortest(Graph *g, unsigned int startV, unsigned int endV, int *st, int mutations, int heuristic(Item, Item))
{
	int i, v, w, adj_v, adj_w;
	int pos[g->V];	/* table that indicates the current heap position of the vertices */
	List *l;
	Edge *e;

	h_reset();

	for(i = 0; i < g->V; i++){
		st[i] = -1;
		h_insert(INF);
		pos[i] = i;		/* the table is initialized */
	}

	h_setKeyg(startV, 0);
	h_setKeyf(startV, heuristic(g->items[startV], g->items[endV]));
	h_fixUp(startV, pos);

	while(!h_empty()){
		if((v = h_delMin(pos)) == endV) break;

		for(l = g->adj[v]; l != NULL; l = l_getNext(l)){
			e = (Edge *) l_getItem(l);
			adj_v = g_getVertex(e);
			adj_w = g_getWeight(e);

			if(adj_w > mutations * mutations) continue;

			w = h_getKeyg(pos[v]) + adj_w;

			if(w < h_getKeyg(pos[adj_v])){
				h_setKeyg(pos[adj_v], w);
				h_setKeyf(pos[adj_v], w + heuristic(g->items[adj_v], g->items[endV]));
				h_fixUp(adj_v, pos);
				st[adj_v] = v;
			}
		}
	}
	w = h_getKeyg(pos[endV]);

	return w;
}


void g_freeEdge(Item e)
{
	if(e != (Item) NULL) free((Edge *) e);
}


Graph *g_destroy(Graph *g, void freeItems(Item *, int size))
{
	int i;

	for(i = 0; i < g->V; i++){
		g->adj[i] = l_destroy(g->adj[i], g_freeEdge);	/* frees adjacency lists */
	}

	free(g->adj);					/* frees the adjacency lists' table */
	freeItems(g->items, g->V);		/* frees the items of the graph */
	free(g);						/* frees graph */

	return NULL;
}