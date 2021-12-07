#ifndef _TETRIS_H
#define _TETRIS_H

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>
#include<conio.h> //kbhit()

#define TRUE	1
#define FALSE	0

#define SIZE_ROW	10
#define SIZE_COLUMN	15

#define NUM_BLOCK_TYPE	3
#define NUM_BLOCK_DIR	4
#define NUM_BLOCK_POINT	4

#define PRINT_EMPTY	0
#define PRINT_WALL	1
#define PRINT_BLOCK	2

#define KEY_NOT		0
#define KEY_UP		72
#define KEY_DOWN    80
#define KEY_LEFT    75
#define KEY_RIGHT   77
#define KEY_SPACE   32

typedef struct _Point {
	int row;
	int column;
}Point;

typedef struct _Block {
	int type;
	int dir;
}Block;

int getKey();
void gotoxy(int row, int column);
int timeCheck(int timeValue);
int waitTime(int timeValue);
void init();
void generateNewBlock();
void showGround();
void changeBlockInform(int key);
int checkChange();
void setplayGround(int addBlockFlag);
void addBlockOnBase();
int checkRemoveOneLine(int column);
int removeOneLine(int column);   
void removeLines();
int checkFinish();
#endif
