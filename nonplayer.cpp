#include "nonplayer.h"

NonPlayer::NonPlayer(int ix, int iy, int iw, int ih) {
    x = ix;
    y = ix;
    w = iw;
    h = ih;
}

void NonPlayer::Draw(WINDOW *win) {
    mvwaddch(win, x, y, 'N');
}
