#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scanner.h"
#include "movie.h"

int main(void) {
	printf("Please give this program a moment to load the database to memory.\n");
	Array a;
	initArray(&a, 4);
	int i = 0;
	FILE *dataFile;
	dataFile = fopen("movie_records", "r");
	while(1) {
		struct movie newMovie;
		char *line;
		line = readLine(dataFile);
		if (feof(dataFile)) break;
		newMovie.identifier = strtok(line, "\t");
		newMovie.type = strtok(NULL, "\t");
		newMovie.primaryTitle = strtok(NULL, "\t");
		newMovie.originalTitle = strtok(NULL, "\t");
		newMovie.isAdult = strtok(NULL, "\t");
		newMovie.startYear = strtok(NULL, "\t");
		newMovie.endYear = strtok(NULL, "\t");
		newMovie.runtimeMinutes = strtok(NULL, "\t");
		newMovie.genres = strtok(NULL, "\t");
		insertArray(&a, newMovie);
		++i;
	}
	fclose(dataFile);
	//quickSort(&a, 0, i);
	char choice = '0';
interface:
	printf("Welcome to the IMDB movie database. To select an option, type the number associated with your choice.\n\n");
	printf("1. Create new catalog\n");
	printf("2. Display existing catalog\n");
	printf("3. Update existing catalog\n");
	printf("4. Exit program\n\n");
	scanf("%c", &choice);
	switch(choice) {
		case '1' :
			goto create;
		case '2' :
			printf("\nFIXME Display\n");
			goto display;
		case '3' :
			printf("\nFIXME Update/delete\n");
			goto update;
		case '4' :
			printf("\nThank you for using this program.\n");
			goto end;
		default :
			printf("\nInvalid input, please try again.\n\n");
			while ((getchar() != '\n'));
			goto interface;
	}
create: ;
	char *name;
	char extension[4] = ".log";
	printf("Enter a name for your catalog.\n\n");
	name = readToken(stdin);
	printf("Creating your catalog with filename %s.log.\n\n", name);
	char *filename = strcat(name, extension);
	FILE *userFile;
	userFile = fopen(filename, "w");
addMovie:
	char *search;
	int matches = 0;
	int matchFound = 0;
	printf("Search for a movie: ");
	while((getchar() != '\n'));
	search = readLine(stdin);
	for(int val = 0; val < i; val++) {
		matchFound = contains(a.array[val].primaryTitle, search);
		if(matchFound == 1) {
			printMovie(&a, val);
			++matches;
		}
		if(matches == 25) {
			printf("First %d matches displayed. If you do not see your movie, please enter a more specific search.\n", matches);
			break;
		}
	}
	fclose(userFile);
	goto interface;
display:
	printf("FIXME D\n\n");
	goto interface;
update:
	printf("Enter the name of your log file (format is {yourfilenamehere}.log): ");	
	name = readToken(stdin);
	printf("Opening %s.\n", name);
	userFile = fopen(name, "rw");
	if(userFile == NULL) {
		printf("Error: File \"%s\" could not be found. Returning to main menu.\n\n", name);
		goto interface;
	}
end:
	freeArray(&a);
	return 0;
}

