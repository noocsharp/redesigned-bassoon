#include "player.h"
Player::Player(int ix, int iy) {
    x = ix;
    y = ix;
    w = 3;
    h = 3;
}

void Player::Draw(WINDOW *win) {
    
    mvwaddch(win, y, x+1, '@');
    mvwaddch(win, y+1, x+1, '|');
    mvwaddch(win, y+1, x, '-');
    mvwaddch(win, y+1, x+2, '-');
    mvwaddch(win, y+2, x+2, '\\');
    mvwaddch(win, y+2, x, '/');
}
bool Player::HasCollidedWithDoor(Door * door) {

    if ((x+w-1>=door->GetX() && x+w-1<=door->GetX()+door->GetW()-1 && y+h-1>=door->GetY() && y+h-1<=door->GetY()+door->GetH()-1) ||
        (x>=door->GetX() && x<=door->GetX()+door->GetW()-1 && y+h-1>=door->GetY() && y+h-1<=door->GetY()+door->GetH()-1) ||
        (x>=door->GetX() && x<=door->GetX()+door->GetW()-1 && y>=door->GetY() && y<=door->GetY()+door->GetH()-1) ||
        (x+w-1>=door->GetX() && x+w-1<=door->GetX()+door->GetW()-1 && y>=door->GetY() && y<=door->GetY()+door->GetH()-1)) {
        return true;
    }
    return false;
}

bool Player::HasCollidedWithTriangle(Triangle * tri) {
    if ((x+w-1>=tri->GetX() && x+w-1<=tri->GetX()+tri->GetW()-1 && y+h-1>=tri->GetY() && y+h-1<=tri->GetY()+tri->GetH()-1) ||
        (x>=tri->GetX() && x<=tri->GetX()+tri->GetW()-1 && y+h-1>=tri->GetY() && y+h-1<=tri->GetY()+tri->GetH()-1) ||
        (x>=tri->GetX() && x<=tri->GetX()+tri->GetW()-1 && y>=tri->GetY() && y<=tri->GetY()+tri->GetH()-1) ||
        (x+w-1>=tri->GetX() && x+w-1<=tri->GetX()+tri->GetW()-1 && y>=tri->GetY() && y<=tri->GetY()+tri->GetH()-1)) {
        return true;
    }
    return false;
}

void Player::ResetPosition() {
    x = 0;
    y = 0;
}
