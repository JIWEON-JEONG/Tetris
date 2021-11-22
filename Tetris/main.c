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
			}
			else {

			}
			changed = FALSE;
		}
	}
	return 0;
} 