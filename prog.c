#include <stdio.h>
#include <string.h>
#include <opencv2\highgui\highgui_c.h>
#include "view.h"
#include "linkedList.h"


void save_project(FrameNode* start);
void load_project(FrameNode* start);
void addFrameNode(FrameNode* start, char* name, int duration, char* path);

#define REMOVE 2
#define CHANGE 3
#define TIME_ONE 4
#define TIME_ALL 5
#define PRINT 6
#define PLAY 7
#define SAVE 8
#define N 10
#define MAX 100
#define MAX2 1000

int main(void)
{

	system("w.mp3");
	int choice3 = 0;
	int choice2 = 0;
	int choice = 0;
	int h = 0;
	FrameNode* start = (FrameNode*)malloc(sizeof(FrameNode));
	FrameNode* p = start;
	FrameNode* g = start;
	start->next = NULL;
	printf("What would you like to do today?\n[1] Load Project\n[2]new project");
	scanf_s("%d", &choice3);
	if (choice3 == 1)
	{
		load_project(start);
	}
	
	do
	{ //UI printing
		printf("Welcome! What would you like to do today?\n[0] Exit\n[1] Add Frame\n[2] remove Frame\n[3] chenge place of frame\n[4] change time of one frame\n[5] change time of all frames\n[6] show frame table\n[7] Play!\n[8] save project as...\n");

		scanf_s("%d", &choice);
		getchar();

		switch (choice) //choices to functions
		{
		case 0:
			while (p != NULL)
			{
				g = p;
				p = p->next;
				free(g);
			}
			getchar();
			return 0;

		case 1:
			addFrame(start);
			break;

		case REMOVE:
			removeFrame(start);
			break;


		case CHANGE:
			placeChange(start);
			break;

		case TIME_ONE:
			changeTime(start);
			break;

		case TIME_ALL:
			changeAllTime(start);
			break;

		case PRINT:
			printList(start);
			break;

		case PLAY: //what format to play
			printf("who to play?\n[1] normal[2] black and white [3] Blur image\n");
			scanf("%d", &choice2);
			getchar();
			if (choice2 == 1)
			{
				play(start->next);
			}
			else if (choice2 == REMOVE)
			{
				play_black(start->next);
			}
			else if(choice2 == CHANGE)
			{
				playBlur(start->next);
			}
			choice2 = 0;
			break;

		case SAVE:
			save_project(start->next);
			break;

		default:
			printf("A wrong number. please try again\n");
			break;
		}
	} while (choice != 0);
	getchar();
	return 0;
}

void save_project(FrameNode * start)
{
	/*
	the function saving the current project in the path that the user wanted.
	input: start
	output: none.
	*/
	int i = 0;
	int lengh = 0;
	FrameNode* p = start;
	char path[MAX] = { 0 };

	printf("please enter a path to save your project\n");
	fgets(path, MAX, stdin); //getting the path.
	path[strlen(path) - 1] = NULL;
	FILE* file = fopen(path, "w");
	while (p->next != NULL) //getting the lengh
	{
		p = p->next;
		lengh++;
	}


	p = start;
	while (p != NULL) //writing to file
	{
		if (i == 0)
		{
			fprintf(file, "%u\n", lengh + 1);
		}
		fprintf(file, "%s\n", p->frame->name);
		fprintf(file, "%u\n", p->frame->duration);
		fprintf(file, "%s\n", p->frame->path);
		p = p->next;
		i++;
	}
}




void load_project(FrameNode * start)
{
	/*
	the function load the project in the file the user wanted
	input: start
	output: none.
	*/
	FrameNode* p = start;
	Frame* frame = (Frame*)malloc(sizeof(Frame));
	int i = 0;
	int j = 0;
	int k = 0;
	int y = 0;
	int lengh = 0;
	int u = 0;
	int check = 0;
	char letter = ' ';
	char path[MAX] = { 0 };
	char data[MAX] = { 0 };
	printf("please enter a path\n"); //getting the path
	fgets(path, MAX, stdin);
	fgets(path, MAX, stdin);
	path[strlen(path) - 1] = NULL;
	p->frame = frame;

	FILE* file = fopen(path, "r");

	i = fgetc(file);
	letter = (char)i;
	lengh = (int)letter;
	lengh = lengh - 48;
	i = fgetc(file); //the \n

	while (letter != EOF)
	{
		i = fgetc(file);
		letter = (char)i;

		if (letter == N)
		{
			j++;

			if (j == 1) //name
			{
				strcpy(p->frame->name, data);
			}
			else if (j == REMOVE)
			{
				p->frame->duration = atoi(data);
			}
			else if (j == CHANGE)
			{
				strcpy(p->frame->path, data);
				addFrameNode(start, p->frame->name, p->frame->duration, p->frame->path); //adding the frame to the liked list
				
				p = start;
				j = 0;
			}


			y = 0;
			while (data[y] != NULL)
			{
				data[y] = NULL;
				y++;
			}
			k = 0;
		}
		else
		{
			data[k] = letter;
			k++;

		}
	}

}

void addFrameNode(FrameNode * start, char * name1, int duration1, char * path1)
{
	/*
	the function adding a frame by the input params.
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

	strcpy(name, name1);

	dur = duration1;


	strcpy(path, path1);
	
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
