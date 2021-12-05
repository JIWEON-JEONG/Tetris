#include "tetris.h"

extern Point currentPosition;

int main() {
	int i = 0;
	int key;
	int changed = FALSE;
	init();
	setplayGround();
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
				setplayGround();
				showGround();
				changed = FALSE;
			}
			else {
				if (key == KEY_DOWN) {
					addBlockOnBase();  // copy baseGround
					generateNewBlock();
					setplayGround();
					showGround();
					changed = FALSE;
				}
			}
			
		}
	}
	return 0;
} 