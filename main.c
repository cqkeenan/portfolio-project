#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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
	choice = readChar(stdin);
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
addMovie: ;
	char *search;
	int matches = 0;
	int matchFound = 0;
	printf("Search for a movie: ");
	while ((getchar() != '\n'));
	search = readLine(stdin);
	for(int val = 0; val < i; val++) {
		matchFound = contains(a.array[val].primaryTitle, search);
		if(matchFound == 1) {
			printMovie(&a, val);
			++matches;
		}
		if(matches == 25) {
			printf("\nFirst %d matches displayed. If you do not see your movie, please enter a more specific search.\n\n", matches);
			break;
		}
	}
	if(matches == 0) {
		printf("No matches found. please try another search.\n\n");
		goto addMovie;
	}
enterNum: ;
	int movieNum = 0;
	printf("To add a movie to your log file, type the number associated with the movie you wish to add. If you do not wish to add any of the movies listed, type \"0\" to see more options.\n\n");
	printf("WARNING: Selecting a number not listed above could either add a random movie to your log.\n\n");
	movieNum = readInt(stdin);
	if(movieNum == 0) goto interface;
	else if(movieNum >= i) {
		printf("The number you entered is outside the bounds of the database. please enter a valid number.\n\n");
		goto enterNum;
	}
	else {
		printf("Adding the following movie:\n\n");
		printMovie(&a, movieNum-1);
		char *mediaType;
media:
		printf("\nWhat is the media type for your movie? (Type the number of your choice.)\n");
		printf("1. DVD\n2. Bluray\n3. Digital\n");
		choice = readChar(stdin);
		if(choice < '1' || choice > '3') {
			printf("Invalid choice, please enter a valid choice.\n\n");
			goto media;
		}
		if(choice == '1') mediaType = "DVD";
		else if(choice == '2') mediaType = "Bluray";
		else mediaType = "Digital";
		int month, day, year;
dateEntry:
		printf("Did you acquire this movie today? (Type \"Y\" for yes, \"N\" for no.)\n");
		choice = readChar(stdin);
		if(choice == 'Y') {
			time_t now;
			time(&now);
			struct tm *local = localtime(&now);
			month = local->tm_mon + 1;
			day = local->tm_mday;
			year = local->tm_year + 1900;
		}
		else if(choice == 'N') {
			printf("Enter the number representing the month you acquired the movie.\n");
			month = readInt(stdin);
			printf("Enter the day you acquired the movie.\n");
			day = readInt(stdin);
			printf("Enter the year you acquired the movie.\n");
			year = readInt(stdin);
		}
		else {
			printf("Invalid choice, please either enter \"Y\" or \"N\".\n\n");
			goto dateEntry;
		}
		fprintf(userFile, "%s\t%s\t%s\t%s\t%s\t%02d/%02d/%d\n", a.array[movieNum-1].primaryTitle, a.array[movieNum-1].genres, a.array[movieNum-1].runtimeMinutes, a.array[movieNum-1].startYear, mediaType, month, day, year);
	}
	printf("Movie added to log file successfully.\n\n");
	fclose(userFile);
	goto updateMenu;
display:
	printf("Enter the name of your log file (format is {yourfilenamehere}.log): ");
        name = readToken(stdin);
        printf("Opening %s.\n", name);
        userFile = fopen(name, "r");
        if(userFile == 0) {
                printf("Error: File \"%s\" could not be found. Returning to main menu.\n\n", name);
                goto interface;
        }
displayMovies:
	char c = fgetc(userFile);
	while (c != EOF) {
		printf("%c", c);
		c = fgetc(userFile);
	}
	fclose(userFile);
	goto updateMenu;
update:
	printf("Enter the name of your log file (format is {yourfilenamehere}.log): ");	
	name = readToken(stdin);
	printf("Opening %s.\n", name);
	userFile = fopen(name, "r");
	if(userFile == 0) {
		printf("Error: File \"%s\" could not be found. Returning to main menu.\n\n", name);
		goto interface;
	}
	fclose(userFile);
updateMenu:
	printf("What would you like to do?\n\n");
	printf("1. Add a movie\n2. Delete a movie\n3. Update existing movie\n4. Display current catalog\n5. Return to main menu\n\n");
	choice = readChar(stdin);
	switch(choice) {
		case '1' :
			userFile = fopen(name, "a");
			goto addMovie;
		case '2' :
			userFile = fopen(name, "rw");
			goto deleteMovie;
		case '3' :
			userFile = fopen(name, "rw");
			goto updateMovie;
		case '4' :
			userFile = fopen(name, "r");
			goto displayMovies;
		case '5' :
			fclose(userFile);
			goto interface;
		default :
			printf("Invalid choice, please try again.\n\n");
			goto updateMenu;
	}
deleteMovie:
	printf("FIX DELETE\n");
	goto updateMenu;
updateMovie:
	printf("FIX DELETE\n");
	goto updateMenu;
end:
	freeArray(&a);
	return 0;
}

