#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scanner.h"
#include "array.h"


void initArray(Array *a, size_t initialSize) {
	a->array = (struct movie *)malloc(initialSize * sizeof(struct movie));
	a->used = 0;
	a->size = initialSize;
}

void BuildArray(Array *a) {
	FILE *dataFile;
	dataFile = fopen("movie_records", "r");
	if(dataFile == 0) {
		printf("Error, data file not found. The program will now terminate.");
		return;
	}
	while(!feof(dataFile)) {
		struct movie element;
		char *line;
		line = readLine(dataFile);
		element.identifier = strtok(line, "\t");
		element.type = strtok(NULL, "\t \n");
		element.primaryTitle = strtok(NULL, "\t \n");
		element.originalTitle = strtok(NULL, "\t \n");
		element.isAdult = strtok(NULL, "\t \n");
		element.year = strtok(NULL, "\t \n");
		element.genres = strtok(NULL, "\n");
		if (a->used == a->size) {
			a->size *= 2;
			a->array = (struct movie *)realloc(a->array, a->size * sizeof(struct movie));
		}
		a->array[a->used++] = element;
	}
	fclose(dataFile);
	return;
}

void freeArray(Array *a) {
	free(a->array);
	a->array = NULL;
	a->used = a->size = 0;
	return;
}


