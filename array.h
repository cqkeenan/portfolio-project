#ifndef ARRAY_H
#define ARRAY_H

struct movie
{
	char *identifier;
	char *type;
	char *primaryTitle;
	char *originalTitle;
	char *isAdult;
	char *year;
	char *genres;
};

typedef struct {
	struct movie *array;
	size_t used;
	size_t size;
} Array;

void initArray(Array *a, size_t initialSize);;
void BuildArray(Array *a);
void freeArray(Array *a);

#endif
