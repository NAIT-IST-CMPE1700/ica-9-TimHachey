#include <stdlib.h>
#include <stdio.h>

char names[10][20] = { "donk", "dork", "derk", "dumb", "dumber", "ace", "stig", "sting", "stank", "dank" };
int ids[10] = { 61,34,46,67,94,58,10,12,43,75 };
int grades[10] = { 12,5,48,78,67,59,36,45,9,45 };

typedef struct Person //stores a person info including name, ID, grade and a link to the next list node
{
	char* name;
	int id;
	int grade;
	struct Person* next;
}Person;

typedef Person* Pntr;

//creates a new node to add to the list, taking all data as arguments, then returning the new node as a pointer
Pntr CreateNode(char* name, int id, int grade)
{
	//create a new node and check that is was allocated properly
	Pntr newNode = (Pntr)malloc(sizeof(Person));
	if (!newNode)
		exit(EXIT_FAILURE);

	//assign the new node the proper data
	newNode->name = name;
	newNode->id = id;
	newNode->grade = grade;

	return newNode;
}

//prints the list contents to the console
void PrintList(Pntr list)
{
	while (list != NULL)
	{
		printf("Name: %s, ID: %d, Mark: %d", list->name, list->id, list->grade);
		printf("\n");
		list = list->next;
	}
	printf("\n");
}

//prints a single persons details after taking an ID number as an input
void PrintPerson(Pntr list)
{
	Pntr temp; //create a temp pointer for iterating through the list
	int idNumber; //the id number input by the user

	do
	{	//prompt user for an ID number 
		printf("Enter the ID of the person to display: ");
		scanf_s("%d", &idNumber);

		temp = list;

		//find the node in the list that has a matching ID number		
		for (int c = 0; c < 10; c++)
			if (temp->id != idNumber)
				temp = temp->next;
		
		//tell user if ID was not found in the list
		if (temp == NULL)
			printf("\nID not found!\n\n");
		
		//print the details of the person that was found
		else
			printf("\nName: %s, ID: %d, Mark: %d\n\n", temp->name, temp->id, temp->grade);
	
	}//rerun loop if ID was not found
	while (temp == NULL);
}

//displays all persons with a grade above the user entered grade threshold
void PrintAboveGrade(Pntr list)
{	
	int gradeThreshold; //the grade input by the user to use as a threshold

	//prompt and take user input
	printf("Enter the threshold grade: ");
	scanf_s("%d", &gradeThreshold);

	//print all grades above the threshold
	while (list->grade > gradeThreshold)
	{
		printf("\nName: %s, ID: %d, Mark: %d", list->name, list->id, list->grade);
		list = list->next;
	}
	printf("\n\n");
}

//displays the menu, takes user input, and executes the apropriate functions
int Menu(Pntr idList, Pntr gradeList)
{
	int menuSelection;

	//display the menu to the user
	printf("1: Display list by ID number\n");
	printf("2: Display list by grade\n");
	printf("3: Display person based on ID\n");
	printf("4: Display names above grade threshold\n");
	printf("5: Exit\n");
	printf("Your Selection: ");

	//take the users input
	do
	{
		scanf_s("%d", &menuSelection);
		printf("\n");

		if (menuSelection < 1 || menuSelection > 5)
			printf("Please enter a valid selection from 1-5!\n\n");
	} while (menuSelection < 1 || menuSelection > 5);

	//check the user selection
	switch (menuSelection)
	{
	case 1:
		PrintList(idList);
		return 1;		

	case 2:
		PrintList(gradeList);
		return 1;

	case 3:
		PrintPerson(idList);
		return 1;

	case 4:
		PrintAboveGrade(gradeList);
		return 1;

	case 5:
		return 0;		
	}
}

//interts a node at the head of the linked list
Pntr InsertAtHead(Pntr listHead, Pntr newNode)
{
	newNode->next = listHead;
	return newNode;
}

//interts a node at the tail of the linked list
void InsertAtTail(Pntr listTail, Pntr newNode)
{
	newNode->next = NULL;
	listTail->next = newNode;
}

//interts a node just after the specified location in the linked list
void InsertAtLocation(Pntr listLocation, Pntr newNode)
{
	newNode->next = listLocation->next;
	listLocation->next = newNode;	
}

int main(int argc, char** argv)
{
	Pntr idListHead = NULL;    //this is the start of the list ordered by id
	Pntr gradeListHead = NULL; //this is the start of the list ordered by grade
	Pntr newNode;			   //this will be used for adding nodes to the list
	Pntr lastNode;			   //this pointer will be to the location of the last node in the list

	//create a list ordered by ID number//
	for (int c = 0; c < 10; c++)
	{
		//create a new node and store the data from the arrays into it
		newNode = CreateNode(names[c], ids[c], grades[c]);

		//add the first node to the start of the list
		if (c == 0)
			idListHead = newNode;
		
		//after creating the first node
		else if (c > 0)
		{
			//get a pointer to the last node in the list
			lastNode = idListHead;
			for (int i = 0; i < c - 1; i++)
				lastNode = lastNode->next;

			//add the new node to the start of the list if the id is smaller than the first nodes id
			if (newNode->id < idListHead->id)
				idListHead = InsertAtHead(idListHead, newNode);

			//add the new node to the tail of the list if its ID is greater than the current tails ID
			else if (newNode->id > lastNode->id)
				InsertAtTail(lastNode, newNode);
			
			//otherwise add the new node in between 2 nodes
			else if (newNode->id > idListHead->id && newNode->id < lastNode->id)
			{
				//create a temp pointer to iterate through the list
				Pntr temp = idListHead;

				while (temp != NULL)
				{
					//if the new nodes ID is between the temps ID and the next one
					if (newNode->id > temp->id && newNode->id < temp->next->id)
					{
						//insert it after the location of the temp
						InsertAtLocation(temp, newNode);
						break;
					}
					//otherwise check the next node in the list
					else
						temp = temp->next;
				}
			}
		}
	}

	//create a list ordered by grades//
	for (int c = 0; c < 10; c++)
	{
		newNode = CreateNode(names[c], ids[c], grades[c]);

		//add the first node to the start of the list
		if (c == 0)
			gradeListHead = newNode;

		//after creating the first node
		else if (c > 0)
		{
			//get a pointer to the last node in the list
			lastNode = gradeListHead;
			for (int i = 0; i < c - 1; i++)
				lastNode = lastNode->next;

			//add the new node to the start of the list if the grade is greater than the first nodes grade
			if (newNode->grade > gradeListHead->grade)
				gradeListHead = InsertAtHead(gradeListHead, newNode);

			//add the new node to the tail of the list if its grade is less than the current tails grade
			else if (newNode->grade < lastNode->grade)
				InsertAtTail(lastNode, newNode);

			//otherwise add the new node in between 2 nodes
			else if (newNode->grade < gradeListHead->grade && newNode->grade > lastNode->grade)
			{
				//create a temp pointer to iterate through the list
				Pntr temp = gradeListHead;

				while (temp != NULL)
				{
					//if the new nodes grade is between the temps grade and the next one
					if (newNode->grade < temp->grade && newNode->grade > temp->next->grade)
					{
						//insert it after the location of the temp
						InsertAtLocation(temp, newNode);
						break;
					}
					//otherwise check the next node in the list
					else
						temp = temp->next;
				}
			}
		}
	}

	while (Menu(idListHead, gradeListHead));

	exit(EXIT_SUCCESS);
}