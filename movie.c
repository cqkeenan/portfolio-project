#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scanner.h"
#include "movie.h"


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

/*void swap(struct movie* a, struct movie* b) {
	struct movie t = *a;
	*a = *b;
	*b = t;
}

int partition(Array *a, int low, int high) {
	char *pivot;
	pivot = a->array[high].primaryTitle;
	int i = (low - 1);
	for (int j = low; j <= high - 1; j++) {
		if (strcmp(a->array[j].primaryTitle, pivot) <= 0) {
			i++;
			swap(&a->array[i], &a->array[j]);
		}
	}
	swap(&a->array[i + 1], &a->array[high]);
	return (i + 1);
}

void quickSort(Array *a, int low, int high) {
	if (low < high) {
		int pi = partition(a, low, high);
		quickSort(a, low, pi - 1);
		quickSort(a, pi + 1, high);
	}
}*/


int exactMatch(char *title, char *search) {
	if(*title == '\0' && *search != '\0') return 0;
	if(*search == '\0') return 1;
	if(*title == *search || *title == *search - 32 || *title == *search + 32) return exactMatch(title + 1, search + 1);
	return 0;
}

int contains(char *title, char *search) {
	if(*title == '\0') return 0;
	if(*title == *search || *title == *search - 32 || *title == *search + 32) {
		if(exactMatch(title, search) == 1) return 1;
		else return contains(title + 1, search);
	}
	return contains(title + 1, search);
}

void printMovie(Array *a, int key) {
	printf("%d. %s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", key + 1, a->array[key].identifier, a->array[key].type, a->array[key].primaryTitle, a->array[key].originalTitle, a->array[key].isAdult, a->array[key].startYear, a->array[key].endYear, a->array[key].runtimeMinutes, a->array[key].genres);
	return;
}




void freeArray(Array *a) {
	free(a->array);
	a->array = NULL;
	a->used = a->size = 0;
}




