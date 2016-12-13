#include "triangle.h"

void Triangle::hide() {
    hidden = true;
}

void Triangle::Draw(WINDOW *win) {
    if (!hidden) {
    
        for (int i = 0; i<w; ++i) {
            mvwaddch(win, y+h, x+i, '_');
        } 

        if (x%2==0) {
            for (int j = 0; j<h; ++j) {
                mvwaddch(win, y+j+1, x+(w/2)-1-j, '/');
                mvwaddch(win, y+j+1, x+(w/2)+1+j, '\\');
            }
        } else {
            for (int j = 0; j<h; ++j) {
                mvwaddch(win, y+j+1, x+(w/2)-1-j, '/');
                mvwaddch(win, y+j+1, x+(w/2)+1+j, '\\');
            }
            mvwaddch(win, y, x, '_');
        }
    }
}
