#pragma once
#include <curses.h>

class NonPlayer {
    
    public:
        NonPlayer(int ix, int iy, int iw, int ih);
        virtual void Draw(WINDOW *win);
        int GetX() const { return x; };
        void SetX(int ix) {x = ix;};
        int GetY() const { return y; };
        void SetY(int iy) {y = iy;};
        int GetW() const { return w; };
        void SetW(int iw) {w = iw;};
        int GetH() const { return h; };
        void SetH(int ih) {h = ih;};

    protected:
        int x, y, w, h;
};
