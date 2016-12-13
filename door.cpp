#include "door.h"
void Door::Draw(WINDOW *win) {
    

    for (int j = 0; j<h; ++j) {
    
        mvwaddch(win, y+j, x, '|');
        mvwaddch(win, y+j, x+w-1, '|');
    }

    for (int i = 0; i<w; ++i) {
        
        mvwaddch(win, y, x+i, '-');
        mvwaddch(win, y+h-1, x+i, '-');
    }
}
