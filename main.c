#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scanner.h"
#include "array.h"

int main(void) {
	printf("Please give this program a moment to load the database to memory.\n");
	Array a;
	initArray(&a, 4);
	BuildArray(&a);
	char choice = '0';
	printf("Welcome to the IMDB movie database. To select an option, type the number associated with your choice.\n\n");
interface:
	printf("1. Create new catalog\n");
	printf("2. Display existing catalog\n");
	printf("3. Update existing catalog\n");
	printf("4. Exit program\n\n");
	scanf("%c", &choice);
	switch(choice) {
		case '1' :
			printf("\nFIXME Create\n");
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
	fprintf(userFile, "test file writing\n");
	fclose(userFile);
	while ((getchar() != '\n'));
	goto interface;
display:
	printf("FIXME D\n\n");
	goto interface;
update:
	printf("FIXME U\n\n");
	goto interface;
end:
	return 0;
}

