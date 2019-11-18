#include "linkedList.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100
void addFrame(FrameNode* start)
{
	/*
	the function adding a frame by the selected parameters.
	input: start
	output: none.
	*/

	int i = 0;
	int check = 0;
	char name[MAX] = { 0 };
	char path[MAX] = { 0 };
	int dur = 0;
	int x = 0;
	FrameNode * p = start;
	FrameNode * g = start;
	Frame* u = (Frame*)malloc(sizeof(Frame));
	FrameNode * new_node = (FrameNode*)malloc(sizeof(FrameNode));

	printf("Please enter the name\n");
	fgets(name, MAX, stdin);
	name[strlen(name) - 1] = NULL; //fron \n to null.

	printf("Please enter the duration: \n");
	while (dur <= 0)
	{
		scanf("%d", &dur);
		getchar();
	}

	printf("Please enter the path\n"); //getting the params into the struct
	fgets(path, MAX, stdin);
	path[strlen(path) - 1] = NULL;
	new_node->frame = u;
	strcpy(new_node->frame->name, name);
	strcpy(u->path, path);
	new_node->frame->duration = dur;
	p = start;
	FILE* file = fopen(path, "r");

	if (!file) //checking if the file is exist
	{
		check = 1;
		printf("file doesnt exist..\n");
	}

	while (p->next != NULL) //checking the name not taken already
	{
		p = p->next;
		x = strcmp(p->frame->name, name); 
		if (x == 0)//if it is
		{
			printf("Name taken\nplease enter another name: \n");
			fgets(name, MAX, stdin);
			name[strlen(name) - 1] = NULL;
			strcpy(new_node->frame->name, name);
			p = start;
		}
	}
	if (check != 1) //if everything is allright getting the struct in the linked list
	{
		if (start->next == NULL) //if its the first node
		{
			start->next = new_node;
			new_node->next = NULL;
		}
		else
		{
			while (p->next != NULL)
			{
				p = p->next;
			}
			p->next = new_node;
			new_node->next = NULL;
		}
	}
}

void removeFrame(FrameNode * start)
{
	/*
	the function removing node from the list.
	input: start
	output: none.
	*/
	FrameNode* p = start;
	FrameNode* g = start;
	char nameD[MAX] = { 0 };
	int x = 0;
	printf("please enter the name of the frame: \n");
	fgets(nameD, MAX, stdin);
	nameD[strlen(nameD) - 1] = NULL;

	while (p->next != NULL) //checking if the name exist' if it is removing the node.
	{
		g = p;
		p = p->next;
		if (strcmp(p->frame->name, nameD) == 0)
		{
			g->next = p->next;
			printf("removed succefully!\n");
			x = 1;
			free(p);
		}
		

	}
	if (x != 1) //if theres no name that found in the list
	{
		printf("no frame found...\n");
	}

}

void changeTime(FrameNode * start)
{
	/*
	the function changes the duration of one of the nodes in the list
	input: start
	output: none.
	*/
	FrameNode* p = start;
	int new_dur = 0;
	char name[MAX] = { 0 };
	int check = 0;

	while (new_dur <= 0) //getting the params
	{
		printf("please enter the new duration\n");
		scanf("%d", &new_dur);
		getchar();
	}
	printf("please enter the name: \n");
	fgets(name, MAX, stdin);
	name[strlen(name) - 1] = NULL;



	while (p->next != NULL) //if the name is found, doing the function. else, printing error msg.
	{
		p = p->next;

		if (strcmp(p->frame->name, name) == 0)
		{
			p->frame->duration = new_dur;
			printf("switched succesfully!\n");
			check = 1;
		}
	}
	if (check != 1)
	{
		printf("No name Found\n");
	}
}

void changeAllTime(FrameNode * start)
{
	/*
	the function chaging all the durations in the list.
	input: start
	output: none.
	*/
	FrameNode* p = start;
	int new_dur = 0;

	while (new_dur <= 0) //getting params
	{
		printf("please enter the new duration\n");
		scanf("%d", &new_dur);
		getchar();
	}



	while (p->next != NULL) //changing
	{
		p = p->next;

		p->frame->duration = new_dur;
		
			
		
	}
	printf("switched succesfully!\n");
}

void printList(FrameNode * start)
{
	/*
	the function printing the list(in a nice pretty way)
	input: start
	output: none.
	*/
	FrameNode* p = start;
	printf("name  Duration  Path\n");
	while (p->next != NULL) //printing in a loop
	{
		p = p->next;
		printf("%s  %d  %s  \n", p->frame->name, p->frame->duration, p->frame->path);

	}
}

void placeChange(FrameNode * start)
{
	/*
	the function changing the place of one of the nodes
	input: start
	output: none.
	*/
	int i = 0;
	int place = 0;
	int check = 0;
	int check2 = 0;
	int j = 0;
	FrameNode* p = start;
	FrameNode* g = 0;
	FrameNode* t = start;
	char name[MAX] = { 0 };

	printf("please enter the name: \n"); //getting the param and checking for unexpected states.
	fgets(name, MAX, stdin);
	name[strlen(name) - 1] = NULL;


	while (place <= 0)
	{
		printf("please enter the place: \n");
		scanf("%d", &place);
		getchar();
	}

	while (p->next != NULL) //checking the name
	{
		p = p->next;
		check++;
		if (strcmp(p->frame->name, name) == 0)
		{
			check2 = 1;
		}
	}
	if (check2 != 1)
	{
		printf("no name found.\n");
		j = 1;
	}

	else if (place > check)
	{
		printf("the place you chose is bigger then your frame list\n");
		j = 1;
	}


	p = start;
	if (j != 1) //if everything is all right with the parameters.
	{
		while (p->next != NULL) //getting the old place
		{
			t = p;
			p = p->next;

			if (strcmp(p->frame->name, name) == 0)
			{
				g = p; //copying detalils
				t->next = p->next; //removing the frame
			}
		}
		p = start;
		t = start;

		while (p != NULL)
		{
			t = p;
			p = p->next;
			i++;

			if (i == place) //if its the right place to get the new struct on the list
			{
				t->next = g;
				g->next = p;
			}
		}
	}
}
	

