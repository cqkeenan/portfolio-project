#ifndef MOVIE_H
#define MOVIE_H

struct movie
{
	char *title;
	char *year;
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
int exactMatch(char *title, char *search);
int contains(char *title, char *search);
void printMovie(Array *a, int key);
void freeArray(Array *a);


#endif
