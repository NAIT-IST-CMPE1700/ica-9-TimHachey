#include <stdlib.h>
#include <stdio.h>

char names[10][20] = { "donk", "dork", "derk", "dumb", "dumber", "ace", "stig", "sting", "stank", "dank" };
int ids[10] = { 6,3,4,67,9,5,3,12,43,7 };
int marks[10] = { };

typedef struct Person  
{
	char* name;
	int id;
	int mark;
	struct Person* next;
}Person;

typedef struct Person* ListPointer;

void Menu() 
{
	int menuSelection;

	//display the menu to the user
	printf("1: Display list by ID number\n");
	printf("2: Display list by marks\n");
	printf("3: Display person based on Id\n");
	printf("4: Display names above grade threshold\n");
	printf("5: Exit\n");

	//take the users input
	do
	{
		scanf_s("%d", &menuSelection, sizeof(int));

		printf("\n");

		if (menuSelection != 1 && menuSelection != 2 && menuSelection != 3 && menuSelection != 4 && menuSelection != 5)
			printf("Please enter a valid selection from 1-5!\n\n");
	} while (menuSelection != 1 && menuSelection != 2 && menuSelection != 3 && menuSelection != 4 && menuSelection != 5);

	//check the user selection
	switch (menuSelection)
	{
	case 1:

	case 2:

	case 3:

	case 4:

	case 5:
		exit(EXIT_SUCCESS);
	}
}

int main(int argc, char** argv)
{



	//build linked list here!!
	ListPointer listPointer = (Person*)malloc(sizeof(Person) * 10);





	Menu();





	



}