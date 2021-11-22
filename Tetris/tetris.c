#include "tetris.h"

extern Point blockPattern[2][4][4];

int baseGround[SIZE_COLUMN][SIZE_ROW];
int playGround[SIZE_COLUMN][SIZE_ROW];
int previousGround[SIZE_COLUMN][SIZE_ROW];

Point currentPosition;
Block currentBlock;

Point tempPosition;
Block tempBlock;

void init() {
	int i, k;
	//baseGround Setting
	for (i = 0; i < SIZE_COLUMN; i++) {
		if (i == 0 || i == SIZE_COLUMN-1) {           
			for (k = 0; k < SIZE_ROW; k++) {
				baseGround[i][k] = PRINT_WALL;
			}
		}
		else {
			baseGround[i][0] = PRINT_WALL;
			baseGround[i][SIZE_ROW - 1] = PRINT_WALL;
			for (k = 1; k < SIZE_ROW-1; k++) baseGround[i][k] = PRINT_EMPTY;
		}
	}
	//baseGround -> displayGround Copy
	for (i = 0; i < SIZE_COLUMN; i++) {
		for (k = 0; k < SIZE_ROW; k++) {
			playGround[i][k] = baseGround[i][k];
		}
	}

	//previousGround setting
	for (i = 0; i < SIZE_COLUMN; i++) {
		for (k = 0; k < SIZE_ROW; k++) {
			previousGround[i][k] = PRINT_EMPTY;
		}
	}

	generateNewBlock();

}

void generateNewBlock() {
	//set block type/dir
	srand(time(NULL));
	currentBlock.type = rand() % NUM_BLOCK_TYPE;
	currentBlock.dir = rand() % NUM_BLOCK_DIR;

	//set block position 
	currentPosition.column = 1; //0이면 벽
	currentPosition.row = SIZE_ROW / 2;   
}

void showGround() {
	int i, k;
	for (i = 0; i < SIZE_COLUMN; i++) {
		for (k = 0; k < SIZE_ROW; k++) {
			if (playGround[i][k] != previousGround[i][k]) {    //개행 왜 빼도 되는지 ..
				gotoxy(i, k * 2); 
				switch (playGround[i][k]) {
				case PRINT_EMPTY:
					printf("  ");
					break;
				case PRINT_WALL:
					printf("□");
					break;
				case PRINT_BLOCK:
					printf("■");
					break;
				default:
					break;
				}
			}
		}
	}
	gotoxy(SIZE_COLUMN + 1, 0);
	printf("\nblock t=%d d=%d p=(%d,%d)\n", currentBlock.type, currentBlock.dir, currentPosition.column, currentPosition.row);
	
	//playGround -> previousGround copy
	for (i = 0; i < SIZE_COLUMN; i++) {
		for (k = 0; k < SIZE_ROW; k++) {
			previousGround[i][k] = playGround[i][k];
		}
	}
}

void changeBlockInform(int key) {
	tempPosition = currentPosition;
	tempBlock = currentBlock;
	switch (key) {
	case KEY_UP:
		if (tempBlock.dir == 3) {
			tempBlock.dir = 0;
		}
		else {
			tempBlock.dir+=1;
		}
		break;
	case KEY_DOWN:
		tempPosition.column += 1;
		break;
	case KEY_RIGHT:
		tempPosition.row += 1;
		break;
	case KEY_LEFT:
		tempPosition.row -= 1;
		break;
	default:
		break;
	}
}
//바뀐애가 이동할 수 있는 공간이 있는지 확인하는 함수
int checkChange() {
	//check!!! 블록이 이동가능한지 가능안한지 어떻게 체크 할 것인가.
	int i;
	int row, column;
	for (i = 0; i < NUM_BLOCK_POINT; i++) {
		row = blockPattern[tempBlock.type][tempBlock.dir][i].row;
		column = blockPattern[tempBlock.type][tempBlock.dir][i].column;

		row += tempPosition.row;
		column += tempPosition.column;

		if (row == 0 || row == 9 || column == 14 ) {
			return FALSE;
		}
	}
	//if it is possible to change
	currentPosition = tempPosition;
	currentBlock = tempBlock;
	return TRUE;
}
//move함수 in ppt
void setplayGround() {
	int i, k;
	int row, column;

	for (i = 0; i < SIZE_COLUMN; i++) {
		for (k = 0; k < SIZE_ROW; k++) {
			playGround[i][k] = baseGround[i][k];
		}
	}
	// 이부분 잘 이해**
	for (i = 0; i < NUM_BLOCK_POINT; i++) {
		row = blockPattern[currentBlock.type][currentBlock.dir][i].row;
		column = blockPattern[currentBlock.type][currentBlock.dir][i].column;

		row += currentPosition.row;
		column += currentPosition.column;

		playGround[column][row] = PRINT_BLOCK;
	}
}

int getKey() {
	int key;
	key = _getch();
	if (key == 224) {
		key = _getch();
	}
	return key;
}