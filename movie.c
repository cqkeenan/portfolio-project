#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scanner.h"
#include "movie.h"


//Dynamic array functions can be found at https://stackoverflow.com/questions/3536153/c-dynamically-growing-array

//Recursive function for substring search can be found at https://www.geeksforgeeks.org/recursive-function-to-do-substring-search/




void initArray(Array *a, size_t initialSize) {
	a->array = (struct movie *)malloc(initialSize * sizeof(struct movie));
	a->used = 0;
	a->size = initialSize;
}

void insertArray(Array *a, struct movie m) {
	if (a->used == a->size) {
		a->size *= 2;
		a->array = (struct movie *)realloc(a->array, a->size * sizeof(struct movie));
	}
	a->array[a->used++] = m;
}

int exactMatch(char *title, char *search) {
	if(*title == '\0' && *search != '\0') return 0;
	if(*search == '\0') return 1;
	if(*title == *search) return exactMatch(title + 1, search + 1);
	return 0;
}

int contains(char *title, char *search) {
	if(*title == '\0') return 0;
	if(*title == *search) {
		if(exactMatch(title, search) == 1) return 1;
		else return contains(title + 1, search);
	}
	return contains(title + 1, search);
}

void printMovie(Array *a, int key) {
	printf("%d.\t%s\t%s\t%s\t%s\n", key + 1, a->array[key].title, a->array[key].year, a->array[key].runtimeMinutes, a->array[key].genres);
	return;
}




void freeArray(Array *a) {
	free(a->array);
	a->array = NULL;
	a->used = a->size = 0;
}




