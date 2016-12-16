#pragma once
#include "curses.h"
#include "door.h"
#include "triangle.h"

class Player {
    public:
        Player(int ix, int iy);
        void Draw(WINDOW *win);
        bool HasCollidedWithDoor(Door * door);
        bool HasCollidedWithTriangle(Triangle * tri);
        void ResetPosition();
        int GetX() const { return x; };
        void SetX(int ix) {x = ix;};
        int GetY() const { return y; };
        void SetY(int iy) {y = iy;};
        int GetW() const { return w; };
        int GetH() const { return h; };
        
    private:
        int x, y, w, h;
};
