//Nicholas DiPinto
//Robert Velarde
//CS 332 Translation Project

#define MAX_CHAR 80

#include <stdio.h>
#include <string.h>
//const char *pronouns[MAX_CHAR][MAX_CHAR] = {"I, he, she, we, they, you"};
//const char *verbs[MAX_CHAR][MAX_CHAR] = {"run, jump, am, is"};
int main()
{
	FILE *sf;  //spanish file
	char input[MAX_CHAR];
	char english_line[MAX_CHAR];
	char spanish_line[MAX_CHAR];
	char words[MAX_CHAR][MAX_CHAR];
	int index = 0;
	int row_index = 0;
	int col_index = 0;

	printf("Enter an english sentence: ");
	scanf("%s", input);
	printf("Translated to spanish is: ");
	sf = fopen("spanish.txt", "r");
	
	while(index < strlen(input))
	{
		while(input[index] != ' ')
		{
			words[row_index][col_index] = input[index];
			col_index++;
			index++;
		}
		while(fgets(english_line, sizeof(english_line), sf) )
		{
			fgets(spanish_line, sizeof(spanish_line), sf);
			english_line[strlen(english_line)-1] = '\0';
			spanish_line[strlen(spanish_line)-1] = '\0';
			if(strcmp(words[row_index], english_line) == 0)
				printf("%s ", spanish_line);
		}
		row_index++;
		fseek(sf, 0, SEEK_SET);
	}
	printf("\n");
	fclose(sf);
	//TODO: create const array of typically used pronouns and verbs
	//TODO: examine string to find tense of sentence
	//TODO: divide spanish words into separate text files based on tense
	//TODO: map english words to spanish translations in each type of text file
}
