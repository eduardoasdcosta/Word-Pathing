#include <stdlib.h>
#include <stdio.h>
#include "list.h"

struct _list
{
	List *next;			/* next list pointer */
	Item item;			/* item hold by list node */
};

List *l_init()
{
	return NULL;
}


List *l_insert(List *l, Item item)
{
	List *new = (List *) malloc (1 * sizeof(List));		/* allocs memory for List */
	if(new == (List *) NULL){
		exit(0);
	}

	new->next = l;
	new->item = item;

	return new;
}


List *l_getNext(List *l)
{
	return (l == (List *) NULL) ? NULL : l->next;
}


Item l_getItem(List *l)
{
	return (l == (List *) NULL) ? NULL : l->item;
}


List *l_remove(List *l, void (*freeItem)(Item))
{
	if(l == (List *) NULL) return l;

	List *new = l->next;	/* updates first element of the List */
	freeItem(l->item);		/* frees item */
	free(l);				/* frees memory occupied by the old first List */

	return new;
}


List *l_find(List *l, Item item, int (*test)(Item, Item))
{
	List *aux;

	for(aux = l; aux != NULL && !test(item, aux->item); aux = aux->next); /* runs through the list until item is found */

	return aux;
}


List *l_getAt(List *l, unsigned int index)
{
	List *aux;

	for(aux = l; aux != NULL && index > 0; aux = aux->next, index--);	   /* runs through the list until index */

	return aux;
}


List *l_destroy(List *l, void (*freeItem)(Item))
{
	while(l != NULL)
		l = l_remove(l, freeItem);		/* frees memory occupied by the first element of the list
										 until there are no more elements */

	return l;
}