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
				setplayGround(TRUE); //블럭추가해야되니까 TRUE
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
					}//새로운 블럭을 만들고 그 블럭을 display 할수 있느냐 없느냔
					setplayGround(TRUE);
					showGround();
					changed = FALSE;
				}
			}
			
		}
	}
	return 0;
} 