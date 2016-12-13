#pragma once
#include <curses.h>
#include "nonplayer.h"

class Triangle : public NonPlayer {
    public:
        Triangle(int ix, int iy, int iw, int ih):
            NonPlayer(ix, iy, iw, ih){hidden = false;};
        void Draw(WINDOW *win);
        void hide();

    private:
        bool hidden;
};
