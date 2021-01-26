#ifndef FILE_H
#define FILE_H
#include "graph.h"

typedef struct _words Words;

/*******************************************
	Func: checkArguments()
	Arguments: number of program arguments
			   program arguments table
	Return Value: ---
	Side Effects: ---

	checks if the arguments are valid
*******************************************/
void checkArguments(int argc, char **argv);

/*******************************************
	Func: readDictionary()
	Arguments: dictionary's filename
			   problem's filename
			   max size
	Return Value: graph table pointer
	Side Effects: ---

	reads the .dic file and loads all 
	necessary words with the necessary mutations
	to the graph table
*******************************************/
Graph **readDictionary(char *filename1, char *filename2, int *size);

/*******************************************
	Func: cmpString()
	Arguments: void pointer
			   void pointer
	Return Value: relative distance between
				two strings
	Side Effects: ---
*******************************************/
int cmpString(const void * a, const void * b);

/*******************************************
	Func: readProb1()
	Arguments: problem's filename
			   words table
			   max lenght size
	Return Value: lenghts table
	Side Effects: ---

	checks what lenghts exist in problem file
*******************************************/
void readProb1(char *filename, Words *w, int size);

/*******************************************
	Func: freeStringTable()
	Arguments: item table
			   array size
	Return Value: ---
	Side Effects: frees memory occupied by
				strings table
*******************************************/
void freeStringTable(Item * items, int size);

/*******************************************
	Func: heuristic()
	Arguments: item
			   item
	Return Value: different characters
				between the two strings
	Side Effects: ---
*******************************************/
int heuristic(Item i1, Item i2);

/*******************************************
	Func: cmpWords()
	Arguments: string
			   string
			   max mutations allowed
	Return Value: relative distance between	
				the two strings
	Side Effects: ---
*******************************************/
int cmpWords(char *str1, char *str2, int mutations);

/*******************************************
	Func: createGraph()
	Arguments: words table
			   max lenght size
	Return Value: graph array pointer
	Side Effects: allocs memory for graph's
				array
*******************************************/
Graph **createGraph(Words *w, int size);

/*******************************************
	Func: readProb2()
	Arguments: graph array pointer
			   problems filename
			   max lenght size
	Return Value: ---
	Side Effects: ---

	reads the problems in the .pal file and 
	writes their solutions in the .path file
*******************************************/
void readProb2(Graph **g, char *filename, int size);

/*******************************************
	Func: findIndex()
	Arguments: strings' table
			   string
			   table's left bound
			   table's right bound
	Return Value: index
	Side Effects: ---

	finds the index of the string in the
	strings' table
*******************************************/
int findIndex(char **table, char *str, int l, int r);

/*******************************************
	Func: writeFile()
	Arguments: string table
			   path filename
			   start vertex
			   end vertex
			   path table
			   total path weight
	Return Value: ---
	Side Effects: ---

	writes the solution of a problem in the
	.path file
*******************************************/
void writeFile(char **w, FILE *fp, int startV, int endV, int *path, int weight);

/*******************************************
	Func: writeExplicit()
	Arguments: path filename
			   string
			   string
			   distance
	Return Value: ---
	Side Effects: ---

	writes the solution of a problem in the
	.path file in case of trivial problems
*******************************************/
void writeExplicit(FILE *file_p, char *str1, char *str2, int distance);

/*******************************************
	Func: gArrayDestroy()
	Arguments: graph table pointer
			   max lenght size
	Return Value: ---
	Side Effects: frees memory occupied by
				the graph table
*******************************************/
void gArrayDestroy(Graph **g, int size);

#endif