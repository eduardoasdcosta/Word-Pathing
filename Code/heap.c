#include <stdlib.h>
#include <stdio.h>
#include "heap.h"
#define EXCHH(a, b) ({ h_node c = a; a = b; b = c; })	/* exchanges two heap nodes */
#define EXCHP(a, b) ({ int p = a; a = b; b = p; })		/* exchanges two integers */
#define LESS(a, b) (a < b)								/* returns 1 if a < b, 0 otherwise */

static Heap h;
static int h_free;		/* heap's first free position */
static int h_size; 		/* heap's size */

struct _h_node
{
	int v;				/* vertex */
	int keyg;			/* real key */
	int keyf;			/* heuristic key */
};

void h_init(unsigned int size)
{
	h_size = size;
	h_free = 0;

	h = (Heap) malloc(size * sizeof(h_node));		/* allocs memory for heap */
	if(h == (Heap) NULL) exit(0);
}


void h_reset()
{
	h_free = 0;
}


void h_insert(int key)
{
	h_node n;

	if(h_free >= h_size) return;	/* if heap is full */

	n.v = h_free;
	n.keyg = key;
	n.keyf = key;

	h[h_free] = n;
	h_free++;
}


int h_getKeyg(int t)
{
	return h[t].keyg;
}


int h_getKeyf(int t)
{
	return h[t].keyf;
}


void h_setKeyg(int t, int key)
{
	h[t].keyg = key;
}


void h_setKeyf(int t, int key)
{
	h[t].keyf = key;
}


int h_delMin(int *pos)
{
	int i = h[0].v;
	h_free = h_free - 1;

	EXCHH(h[0], h[h_free]);
	EXCHP(pos[h[0].v], pos[h[h_free].v]);
	h_fixDown(h[0].v, pos);

	return i;
}


void h_fixDown(int t, int *pos)
{
	int child, idx = pos[t];

	while(idx < (h_free - 1) / 2){
		child = 2*idx + 1;

		if(child < h_free - 1 && LESS(h[child + 1].keyf, h[child].keyf)) child++;

		if(LESS(h[idx].keyf, h[child].keyf)) break;

		EXCHH(h[idx], h[child]);
		EXCHP(pos[h[idx].v], pos[h[child].v]);
		idx = child;
	}
}


void h_fixUp(int t, int *pos)
{
	int aux, v = pos[t];

	while(v > 0){
		aux = (v - 1) / 2;

		if(LESS(h[v].keyf, h[aux].keyf)){
			EXCHH(h[aux], h[v]);
			EXCHP(pos[h[aux].v], pos[h[v].v]);
			v = aux;
		}
		else break;
	}
}


int h_empty()
{
	return (h_free == 0) ? 1 : 0;
}


void h_destroy()
{
	free(h);		/* frees heap */
	h_free = 0;
	h_size = 0;
}