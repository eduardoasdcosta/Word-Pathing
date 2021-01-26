#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
#include "heap.h"

struct _words
{
	int valid;		/* flag that signals if _words struct is valid */
	int max_mut;	/* number of max mutations */
	int occupied;	/* first free position in table */
	int t_size;		/* table size */
	char **table;	/* string table */
};

void checkArguments(int argc, char **argv)
{
	char *t = NULL;

	if(argc < 3){
		exit(0);
	}

	t = strrchr(argv[1], '.');
	if(strcmp(t, ".dic"))
		exit(0);

	t = strrchr(argv[2], '.');
	if(strcmp(t, ".pal"))
		exit(0);
}


Graph **readDictionary(char *filename1, char *filename2, int *max_size)
{
	int i;
	char str[100];
	Words *w;
	Graph **g;

	FILE * fp = fopen(filename1, "r"); 		/* opens .dic file */
	if(fp == (FILE *) NULL) exit(0);

	while(fscanf(fp, "%s", str) == 1){		/* gets lenght of biggest word */

		i = strlen(str);

		if(i > *max_size)
			*max_size = i;
	}
	rewind(fp);

	w = (Words *) calloc( *max_size, sizeof(Words));	/* allocs memory for Words table */
	if(w == (Words *) NULL) exit(0);

	readProb1(filename2, w, *max_size);

	while(fscanf(fp, "%s", str) == 1){		/* gets number of total words from each size */

		i = strlen(str) - 1;

		if(w[i].valid)
			w[i].t_size++;
	}
	rewind(fp);

	for(i = 0; i < *max_size; i++){
		if(w[i].valid){
			w[i].table = (char **) malloc((w[i].t_size) * sizeof(char *));	/* allocs memory for string tables */
			if(w[i].table == (char **) NULL) exit(0);
		}
	}

	while(fscanf(fp, "%s", str) == 1){

		i = strlen(str) - 1;

		if(w[i].valid){
			w[i].table[w[i].occupied] = (char *) malloc((i + 2) * sizeof(char));	/* allocs memory for string */
			if(w[i].table[w[i].occupied] == (char *) NULL) exit(0);

			strcpy(w[i].table[w[i].occupied], str);
			w[i].occupied++;	/* updates the first free table position */
		}
	}

	fclose(fp);		/* closes .dic file */

	for(i = 0; i < *max_size; i++){
		if(w[i].valid)
			qsort(w[i].table, w[i].t_size, sizeof(char *), cmpString);	/* sorts alphabetically each string table */
	}
	
	g = createGraph(w, *max_size);
	
	free(w);		/* frees Words table */

	return g;
}


int cmpString(const void * a, const void * b)
{
	char ** s1 = (char **) a;
	char ** s2 = (char **) b;
	return strcmp(*s1, *s2);
}


void readProb1(char *filename, Words *w, int size)
{
	char str1[100];
	char str2[100];
	int m, v, i;

	FILE * file_p = fopen(filename, "r");		/* opens .pal file */
	if(file_p == (FILE *) NULL) exit(0);

	while(fscanf(file_p, "%s %s %d", str1, str2, &m) == 3){ 
		
		v = heuristic((Item) str1, (Item) str2);	

		if(v < 2) continue;			/* if words differ from 1 or 0 characters, 
										there's no need to create a graph */	
		i = strlen(str1) - 1;

		w[i].valid = 1;
									/* updates the max mutations allowed */
		if(v >= m){
			if(m > w[i].max_mut)
				w[i].max_mut = m;
		}
		else if(v < m){
			if(v > w[i].max_mut)
				w[i].max_mut = v;
		}
	}

	fclose(file_p);		/* closes the .pal file */

	return;
}


void freeStringTable(Item * items, int size)
{
	int i;
	char **table = (char **) items;

	for(i = 0; i < size; i++) free(table[i]);
	free(table);
}


int heuristic(Item i1, Item i2)
{
	char *str1 = (char *) i1;
	char *str2 = (char *) i2;
	int i, w = 0;

	for(i = 0; str1[i] != '\0'; i++)
		if(str1[i] != str2[i]) w++;		/* if characters differ update distance counter */

	return w;
}


int cmpWords(char *str1, char *str2, int mutations)
{
	int i, w = 0;

	for(i = 0; str1[i] != '\0'; i++){
		if(str1[i] != str2[i]) w++;		/* if characters differ update distance counter */
		if(w > mutations) return w;		/* if distance is bigger than max mutations it's pointless to keep going */
	}

	return (w);
}


Graph **createGraph(Words *w, int size) 
{
	int i, j, k, weight;
	Edge *e;
	Graph **g = NULL;

	g = (Graph **) calloc(size, sizeof(Graph*));	/* initializes graph array */

	for(k = 0; k < size; k++){
		if(!w[k].valid) continue; /* unnecessary graphs are not created */
		/* initializes graph */
		g[k] = g_init((Item *) w[k].table, w[k].t_size);

		for(i = 0; i < w[k].t_size; i++){
			for(j = i + 1; j < w[k].t_size; j++){
				if((weight = cmpWords(w[k].table[i], w[k].table[j], w[k].max_mut)) <= w[k].max_mut){
					/* creates both edges if weight is allowed */
					weight = weight * weight;
					e = g_createEdge(j, weight);
					g[k] = g_insert(g[k], e, i);
					e = g_createEdge(i, weight);
					g[k] = g_insert(g[k], e, j);
				}
			}	
		}
	}

	return g;
}


void readProb2(Graph **g, char *filename, int size)
{
	char str1[100];
	char str2[100];
	char fileout[100];
	char **w;
	char *t;
	int max_size = 0, mutations, startV, endV, weight, v, i;
	int *path;

	FILE *fp = fopen(filename, "r");		/* opens .pal file */
	if(fp == (FILE *) NULL) exit(0);

	strcpy(fileout, filename);
	t = strrchr(fileout, '.');
	*t = '\0';
	strcat(fileout, ".path");

	FILE *file_p = fopen(fileout, "w");		/* opens .path file */
	if(file_p == (FILE *) NULL) exit(0);

	for(i = 0; i < size; i++)
		if(g_getV(g[i]) > max_size) max_size = g_getV(g[i]);	/* gets the number of vertices in the biggest graph */
	
	path = (int *) malloc(max_size * sizeof(int));		/* allocs memory for the search tree, which size if equal
														to the biggest graph size, so that every tree fits here */
		if(path == (int *) NULL) exit(0);

	h_init(max_size);	/* initializes heap table */

	while(fscanf(fp,"%s %s %d", str1, str2, &mutations) == 3){

		v = heuristic((Item) str1, (Item) str2);

		if(v < 2){		/* if the solution is immediate */
			writeExplicit(file_p, str1, str2, v);
			continue;
		}

		i = strlen(str1) - 1;

		w = (char **) g_getItems(g[i]);
		startV = findIndex(w, str1, 0, g_getV(g[i]) - 1);	/* gets the starting word index */	
		endV = findIndex(w, str2, 0, g_getV(g[i]) - 1);		/* gets the ending word index */

		weight = g_findShortest(g[i], startV, endV, path, mutations, heuristic);
	
		writeFile(w, file_p, startV, endV, path, weight);
		fprintf(file_p, "\n");
	}

	h_destroy();		/* frees the heap table */
	free(path);			/* frees the search tree */
	fclose(fp);			/* closes .pal file */
	fclose(file_p);		/* closes .path file */
}


int findIndex(char **table, char *str, int l, int r)
{
	int m = (l + r)/2;

	if(l > r)
		return -1;

	if(strcmp(table[m], str) < 0)
		m = findIndex(table, str, m + 1, r);
	else if(strcmp(table[m], str) > 0)
		m = findIndex(table, str, l, m - 1);

	return m;
}


void writeFile(char **w, FILE *fp, int startV, int endV, int *path, int weight)
{
	int i = path[endV];		/* gets the previous vertex */

	if(i != -1)		/* if it's not the starting vertex, recalls the function to get another previous vertex */
		writeFile(w, fp, startV, i, path, weight);

	if(weight == INF) fprintf(fp, "%s -1\n%s\n", w[startV], w[endV]);	/* in case path doesn't exist, prints -1 */
	else if(i == -1) fprintf(fp, "%s %d\n", w[endV], weight);	/* in case path exists, prints the starting word
																and the path total weight */
	else fprintf(fp, "%s\n", w[endV]);		/* prints the remaining path words */

	return;
}


void writeExplicit(FILE *file_p, char *str1, char *str2, int distance)
{
	if(distance == 0) fprintf(file_p, "%s 0\n%s\n\n", str1, str2);	/* in case the words are equal */
	else 			  fprintf(file_p, "%s 1\n%s\n\n", str1, str2);	/* in case the words differ by only one character */

	return;
}


void gArrayDestroy(Graph **g, int size)
{
	int i;

	for(i = 0; i < size; i++){
		if(g[i] != NULL)	/* if the graph was created, destroy graph */
			g[i] = g_destroy(g[i], freeStringTable);
	}
	free(g);
}