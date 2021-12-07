#include "tetris.h"

extern Point currentPosition;

int main() {
	int i = 0;
	int key;
	int changed = FALSE;
	init();
	setplayGround(TRUE);
	showGround();

	while (1) {
		if(timeCheck(1000) == TRUE){
			changed = TRUE;
			key = KEY_DOWN;
			changed = TRUE;
		}
		if (_kbhit()) {
			key = getKey();
			changed = TRUE;
		}
		if (changed == TRUE) {
			changeBlockInform(key);
			if (checkChange() == TRUE) {
				setplayGround(TRUE); //���߰��ؾߵǴϱ� TRUE
				showGround();
				changed = FALSE;
			}
			else {
				if (key == KEY_DOWN) {
					addBlockOnBase();  // copy baseGround
					removeLines();
					generateNewBlock();
					if (TRUE == checkFinish() ) {
						break;
					}//���ο� ���� ����� �� ���� display �Ҽ� �ִ��� ������
					setplayGround(TRUE);
					showGround();
					changed = FALSE;
				}
			}
			
		}
	}
	return 0;
} 