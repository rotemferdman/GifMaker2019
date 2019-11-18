#ifndef LINKEDLISTH
#define LINKEDLISTH

#define FALSE 0
#define TRUE !FALSE
#define MAX 100

// Frame struct
typedef struct Frame
{
	char name[MAX];
	unsigned int duration;
	char path[MAX];
} Frame;


// Link (node) struct
typedef struct FrameNode
{
	Frame* frame;
	struct FrameNode* next;
} FrameNode;

void addFrame(FrameNode* start);
void removeFrame(FrameNode* start);
void changeTime(FrameNode* start);
void changeAllTime(FrameNode* start);
void printList(FrameNode* start);
void placeChange(FrameNode* start);
#endif
