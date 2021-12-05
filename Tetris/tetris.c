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
	currentPosition.column = 1; //0�̸� ��
	currentPosition.row = SIZE_ROW / 2;   
}

void showGround() {
	int i, k;
	for (i = 0; i < SIZE_COLUMN; i++) {
		for (k = 0; k < SIZE_ROW; k++) {
			if (playGround[i][k] != previousGround[i][k]) {    //���� �� ���� �Ǵ��� ..
				gotoxy(i, k * 2); 
				switch (playGround[i][k]) {
				case PRINT_EMPTY:
					printf("  ");
					break;
				case PRINT_WALL:
					printf("��");
					break;
				case PRINT_BLOCK:
					printf("��");
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
//�ٲ�ְ� �̵��� �� �ִ� ������ �ִ��� Ȯ���ϴ� �Լ�
int checkChange() {
	//check!!! ����� �̵��������� ���ɾ����� ��� üũ �� ���ΰ�.
	int i;
	int row, column;
	int changed = TRUE;
	for (i = 0; i < NUM_BLOCK_POINT; i++) {
		row = blockPattern[tempBlock.type][tempBlock.dir][i].row;
		column = blockPattern[tempBlock.type][tempBlock.dir][i].column;

		row += tempPosition.row;
		column += tempPosition.column;

		if (baseGround[column][row] != PRINT_EMPTY) {
			changed = FALSE;
			break;
		}
	}
	//if it is possible to change
	if (changed == TRUE) {
		currentPosition = tempPosition;
		currentBlock = tempBlock;
	}
	return changed;
}
//move�Լ� in ppt
void setplayGround() {
	int i, k;
	int row, column;

	for (i = 0; i < SIZE_COLUMN; i++) {
		for (k = 0; k < SIZE_ROW; k++) {
			playGround[i][k] = baseGround[i][k];
		}
	}
	// �̺κ� �� ����**
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

void addBlockOnBase() {
	int i, row, column;
	for (i = 0; i < NUM_BLOCK_POINT; i++) {
		row = blockPattern[currentBlock.type][currentBlock.dir][i].row;
		column = blockPattern[currentBlock.type][currentBlock.dir][i].column;

		row += currentPosition.row;
		column += currentPosition.column;
		
		baseGround[column][row] = PRINT_BLOCK;
	}
}

int checkRemoveOneLine(int column) {                  // int column �޾ƿ��� ���� : ���� �ϼ��Ǵ� ���ΰ� �� �� ������ �ƴ� ������ ����� �ֱ� ����.
	int i;
	for (i = 0; i < SIZE_ROW-1; i++) {
		if (baseGround[column][i] == PRINT_EMPTY) {
			return FALSE;
		}	
	}
	return TRUE;
}

int removeOneLine(int column) {   //int Ÿ�Ը�����
	int i, k;
	if (checkRemoveOneLine(column)) {
		for (i = column; i > 1; i--) {
			for (k = 1; k < SIZE_ROW - 1; k++) {
				baseGround[i][k] = baseGround[i - 1][k];
			}
		}
		return TRUE;
	}
	return FALSE;
}

