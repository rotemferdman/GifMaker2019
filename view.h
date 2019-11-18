/*********************************
* Class: MAGSHIMIM Final Project *
* Play function declaration	 	 *
**********************************/

#ifndef VIEWH
#define VIEWH

#include <opencv2\core\core_c.h>
#include <opencv2\highgui\highgui_c.h>
#include <stdio.h>
#include "LinkedList.h"

#define GIF_REPEAT 5

void play(FrameNode *list);
void play_black(FrameNode* list);
void playBlur(FrameNode* list);
#endif
