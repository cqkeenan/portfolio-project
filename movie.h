#ifndef MOVIE_H
#define MOVIE_H

struct movie
{
	char *identifier;
	char *type;
	char *primaryTitle;
	char *originalTitle;
	char *isAdult;
	char *startYear;
	char *endYear;
	char *runtimeMinutes;
	char *genres;
};

typedef struct {
        struct movie *array;
        size_t used;
        size_t size;
} Array;


void initArray(Array *a, size_t initialSize);
void insertArray(Array *a, struct movie m);
//void swap(struct movie* a, struct movie* b);
//int partition(Array *a, int low, int high);
//void quickSort(Array *a, int low, int high);
int exactMatch(char *title, char *search);
int contains(char *title, char *search);
void printMovie(Array *a, int key);
void freeArray(Array *a);


#endif
