#pragma once
#include <ncurses.h>
#include "nonplayer.h"

class Door : public NonPlayer {
    public:
        Door(int ix, int iy, int iw, int ih):NonPlayer(ix, iy, iw, ih){};
        void Draw(WINDOW *win);
};
