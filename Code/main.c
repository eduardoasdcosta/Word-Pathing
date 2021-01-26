#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"


int main(int argc, char **argv)
{
	int size = 0;
	Graph **g;

	checkArguments(argc, argv);

	g = readDictionary(argv[1], argv[2], &size);

	readProb2(g, argv[2], size);

	gArrayDestroy(g, size);
	
	return 0;	
}