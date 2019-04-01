#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "scanner.h"
#include "movie.h"

int main(void) {
	printf("Please give this program a moment to load the database to memory. This will take roughly 30-40 seconds.\n");
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
	char choice = '0';
interface:
	printf("Welcome to the IMDB movie database. To select an option, type the number associated with your choice.\n\n");
	printf("1. Create new catalog\n");
	printf("2. Display existing catalog\n");
	printf("3. Update existing catalog\n");
	printf("4. Exit program\n\n");
	choice = readChar(stdin);
	while(getchar() != '\n');
	switch(choice) {
		case '1' :
			goto create;
		case '2' :
			goto display;
		case '3' :
			goto update;
		case '4' :
			printf("\nThank you for using this program.\n");
			goto end;
		default :
			printf("\nInvalid input, please try again.\n\n");
			goto interface;
	}
create: ;
	char *filename;
	printf("Enter a name for your catalog file using the format {yourfilename}.log.\n\n");
	filename = readToken(stdin);
	printf("Creating your catalog with filename %s.\n\n", filename);
	while(getchar() != '\n');
	FILE *userFile;
	userFile = fopen(filename, "w");
addMovie: ;
	char *search;
	int matches = 0;
	int matchFound = 0;
	printf("Search for a movie: ");
	search = readLine(stdin);
	for(int val = 0; val < i; val++) {
		matchFound = contains(a.array[val].primaryTitle, search);
		if(matchFound == 1) {
			if(matches == 0) printf("#\tTitle\t\tYear\tRunning Time\tGenre(s)\n\n");
			printMovie(&a, val);
			++matches;
		}
		if(matches == 50) {
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
	if(movieNum == 0) {
		fclose(userFile);
		goto updateMenu;
	}
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
        filename = readToken(stdin);
        printf("Opening %s.\n", filename);
        userFile = fopen(filename, "r");
        if(userFile == 0) {
                printf("Error: File \"%s\" could not be found. Returning to main menu.\n\n", filename);
                goto interface;
        }
displayMovies: ;
	printf("\n\n");
	char c = fgetc(userFile);
	while (c != EOF) {
		printf("%c", c);
		c = fgetc(userFile);
	}
	fclose(userFile);
	goto updateMenu;
update:
	printf("Enter the name of your log file (format is {yourfilenamehere}.log): ");	
	filename = readLine(stdin);
	printf("Opening %s.\n", filename);
	userFile = fopen(filename, "r");
	if(userFile == 0) {
		printf("Error: File \"%s\" could not be found. Returning to main menu.\n\n", filename);
		goto interface;
	}
	fclose(userFile);
updateMenu:
	printf("\n\nWhat would you like to do?\n\n");
	printf("1. Add a movie\n2. Delete a movie\n3. Update existing movie\n4. Display current catalog\n5. Return to main menu\n\n");
	choice = readChar(stdin);
	while(getchar() != '\n');
	switch(choice) {
		case '1' :
			userFile = fopen(filename, "a");
			goto addMovie;
		case '2' :
			userFile = fopen(filename, "r");
			goto deleteMovie;
		case '3' :
			userFile = fopen(filename, "r");
			goto updateMovie;
		case '4' :
			userFile = fopen(filename, "r");
			goto displayMovies;
		case '5' :
			fclose(userFile);
			goto interface;
		default :
			printf("Invalid choice, please try again.\n\n");
			goto updateMenu;
	}
deleteMovie:
	printf("\n\n");
        c = fgetc(userFile);
        while (c != EOF) {
                printf("%c", c);
                c = fgetc(userFile);
        }
        fclose(userFile);
	printf("\n\nWhich movie would you like to delete? Type the line number of the movie you wish to delete.\n");
	scanf("%d", &movieNum);
	while(getchar() != '\n');
	userFile = fopen(filename, "r");
	FILE *newFile;
	newFile = fopen("newFile.log", "w");
	int lineNum = 1;
	char *tempLine;
	while(1) {
		tempLine = readLine(userFile);
		if(feof(userFile)) break;
		if(lineNum == movieNum) {
			lineNum++;
		}
		else {
			fputs(tempLine, newFile);
			fprintf(newFile, "\n");
			lineNum++;
			}
	}
	fclose(userFile);
	fclose(newFile);
	remove(filename);
	rename("newFile.log", filename);
	printf("Movie deleted.\n\n");
	goto updateMenu;
updateMovie:
	printf("\n\n");
        c = fgetc(userFile);
        while (c != EOF) {
                printf("%c", c);
                c = fgetc(userFile);
        }
        fclose(userFile);
        printf("\n\nWhich movie would you like to update? Type the line number of the movie you wish to update.\n\n");
        scanf("%d", &movieNum);
        while(getchar() != '\n');
updateChoice:
	printf("Which field would you like to update?\n\n");
	printf("1. Media type\n2. Date acquired\n\n");
	choice = readChar(stdin);
	while(getchar() != '\n');
	if(choice == '1') {
updateMedia:
		printf("Which media type do you own?\n\n");
		printf("1. DVD\n2. Bluray\n3. Digital\n\n");
		choice = readChar(stdin);
		while(getchar() != '\n');
		if(choice > '3' || choice < '1') {
			printf("Error: Invalid choice. Please try again.\n\n");
			goto updateMedia;
		}
		userFile = fopen(filename, "r");
		newFile = fopen("newFile.log", "w");
		lineNum = 1;
		while(1) {
                tempLine = readLine(userFile);
                if(feof(userFile)) break;
                if(lineNum == movieNum) {
                        fprintf(newFile, "%s\t", strtok(tempLine, "\t"));
			fprintf(newFile, "%s\t", strtok(NULL, "\t"));
			fprintf(newFile, "%s\t", strtok(NULL, "\t"));
			fprintf(newFile, "%s\t", strtok(NULL, "\t"));
			strtok(NULL, "\t");
			if(choice == '1') fprintf(newFile, "DVD\t");
			else if(choice == '2') fprintf(newFile, "Bluray\t");
			else fprintf(newFile, "Digital\t");
			fprintf(newFile, "%s", strtok(NULL, "\n"));	
			fprintf(newFile, "\n");
			lineNum++;
                }
                else {
                        fputs(tempLine, newFile);
                        fprintf(newFile, "\n");
                        lineNum++;
                        }
        }
        fclose(userFile);
        fclose(newFile);
        remove(filename);
        rename("newFile.log", filename);
        printf("Media type updated.\n\n");

	}
	else if(choice == '2') {
		int newMonth, newDay, newYear;
		printf("Enter the number representing the month you acquired the movie.\n");
                newMonth = readInt(stdin);
                printf("Enter the day you acquired the movie.\n");
                newDay = readInt(stdin);
                printf("Enter the year you acquired the movie.\n");
                newYear = readInt(stdin);
		userFile = fopen(filename, "r");
                newFile = fopen("newFile.log", "w");
		lineNum = 1;
		while(1) {
                tempLine = readLine(userFile);
                if(feof(userFile)) break;
                if(lineNum == movieNum) {
                        fprintf(newFile, "%s\t", strtok(tempLine, "\t"));
                        fprintf(newFile, "%s\t", strtok(NULL, "\t"));
                        fprintf(newFile, "%s\t", strtok(NULL, "\t"));
                        fprintf(newFile, "%s\t", strtok(NULL, "\t"));
                        fprintf(newFile, "%s\t", strtok(NULL, "\t"));
			fprintf(newFile, "%02d/%02d/%d\n", newMonth, newDay, newYear); 
			lineNum++;
                }
                else {
                        fputs(tempLine, newFile);
                        fprintf(newFile, "\n");
                        lineNum++;
                        }
        }
        fclose(userFile);
        fclose(newFile);
        remove(filename);
        rename("newFile.log", filename);
        printf("Date updated.\n\n");

	}
	else {
		printf("Error: Not a valid choice. Please try again.\n\n");
		goto updateChoice;
	}


	goto updateMenu;
end:
	freeArray(&a);
	return 0;
}

