#include <curses.h>
#include <list>

using std::list;



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

class Door : public NonPlayer {
    public:
        Door(int ix, int iy, int iw, int ih):NonPlayer(ix, iy, iw, ih){};
        void Draw(WINDOW *win);
};

class Triangle : public NonPlayer {
    public:
        Triangle(int ix, int iy, int iw, int ih):NonPlayer(ix, iy, iw, ih){};
        void Draw(WINDOW *win);
};

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

void DrawDialog(WINDOW *win);
void gameLoop();
void IncrementDialogState(WINDOW * win);
void DecrementDialogState(WINDOW * win);
void DrawLevel(WINDOW * win, list<NonPlayer*>);
void ChangeLevel(list<NonPlayer*> &objs, int level, Player &player);
int DialogState = 0;
int DialogLength = 4;




NonPlayer::NonPlayer(int ix, int iy, int iw, int ih) {
    x = ix;
    y = ix;
    w = iw;
    h = ih;
}


Player::Player(int ix, int iy) {
    x = ix;
    y = ix;
    w = 3;
    h = 3;
}


void NonPlayer::Draw(WINDOW *win) {
    mvwaddch(win, x, y, 'N');
}

void Player::Draw(WINDOW *win) {
    
    mvwaddch(win, y, x+1, '@');
    mvwaddch(win, y+1, x+1, '|');
    mvwaddch(win, y+1, x, '-');
    mvwaddch(win, y+1, x+2, '-');
    mvwaddch(win, y+2, x+2, '\\');
    mvwaddch(win, y+2, x, '/');
}

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

void Triangle::Draw(WINDOW *win) {
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

int main()
{
    initscr();
    noecho();
    curs_set(0);
    gameLoop();
    return 0;
}

void gameLoop()
{
    int ch;
    Player player(10, 10);
    list<NonPlayer*> NonPlayerObjects;
    NonPlayerObjects.push_back(new Door(30, 10, 6, 6));
    list<NonPlayer*>::iterator NPOIterator = NonPlayerObjects.begin();
    int x = 5;
    int y = 5;
    const int DIALOG_HEIGHT = 3;
    const int WIDTH = 100;
    WINDOW * Dialog = newwin(DIALOG_HEIGHT, WIDTH, 0, 0);
    WINDOW * GameArea = newwin(LINES-DIALOG_HEIGHT, WIDTH, DIALOG_HEIGHT+1, 0);
    nodelay(GameArea, TRUE);
    werase(GameArea);
    int level = 0;
    while (true) {
        DrawDialog(Dialog);
        for (int i = 0; i<WIDTH; ++i) {
            mvwaddch(Dialog, DIALOG_HEIGHT-1, i, '-');
            wnoutrefresh(Dialog);
            doupdate();
        }
        if ((ch = getch()) == ERR) {
            continue;
        } else {
            if (ch == 'q') {
                for (list<NonPlayer*>::iterator n = NonPlayerObjects.begin(); n != NonPlayerObjects.end(); ++n) {
                    delete *n;
                }
                endwin();
                break;
            }
            switch (ch) {
                case 'w':
                    werase(GameArea);
                    player.SetY(player.GetY()-1);
                    NPOIterator = NonPlayerObjects.begin();
                    if (player.HasCollidedWithDoor(static_cast<Door*>(*NPOIterator))) {
                        ++level;
                        ChangeLevel(NonPlayerObjects, level, player);
                    }
                    for (NPOIterator = ++NonPlayerObjects.begin(); NPOIterator != NonPlayerObjects.end(); ++NPOIterator) {
                        if (player.HasCollidedWithTriangle(dynamic_cast<Triangle*>(*NPOIterator))) {
                            NPOIterator = NonPlayerObjects.erase(NPOIterator++);
                        }
                    }
                    player.Draw(GameArea);
                    break;

                case 's':
                    werase(GameArea);
                    player.SetY(player.GetY()+1);
                    NPOIterator = NonPlayerObjects.begin();
                    if (player.HasCollidedWithDoor(static_cast<Door*>(*NPOIterator))) {
                        ++level;
                        ChangeLevel(NonPlayerObjects, level, player);
                    }
                    player.Draw(GameArea);
                    break;

                case 'a':
                    werase(GameArea);
                    player.SetX(player.GetX()-1);
                    NPOIterator = NonPlayerObjects.begin();
                    if (player.HasCollidedWithDoor(static_cast<Door*>(*NPOIterator))) {
                        ++level;
                        ChangeLevel(NonPlayerObjects, level, player);
                    }
                    player.Draw(GameArea);
                    break;

                case 'd':
                    werase(GameArea);
                    player.SetX(player.GetX()+1);
                    NPOIterator = NonPlayerObjects.begin();
                    if (player.HasCollidedWithDoor(static_cast<Door*>(*NPOIterator))) {
                        ++level;
                        ChangeLevel(NonPlayerObjects, level, player);
                    }
                    
                    player.Draw(GameArea);
                    break;
                
                case 'm':
                    IncrementDialogState(Dialog);

                    break;
                case 'n':
                    DecrementDialogState(Dialog);
                    break;
                default:
                    continue;

            }

        DrawLevel(GameArea, NonPlayerObjects);
        wnoutrefresh(GameArea);
        doupdate();
        }
    }
}

void DrawDialog(WINDOW *win) {
    wclear(win);
    switch (DialogState) {
        case 0:
            mvwprintw(win, 0, 0, "Welcome. To move around, you can use WASD. Press m to move dialog forward, and n to move dialog backward");
            break;
        case 1:
            mvwprintw(win, 0, 0, "The triangles want to invade reality. You need to stop it.");
            break;
        case 2:
            mvwprintw(win, 0, 0, "I need you to go into that door over there.");
            break;
        default:
            mvwprintw(win, 0, 0, "Well... the code is messed up");
            break;
    }
    wnoutrefresh(win);
    doupdate();
}

void IncrementDialogState(WINDOW * win) {
    if (DialogState >=0 && DialogState<=DialogLength-2) {
        DialogState += 1;
        DrawDialog(win);
    }
}

void DecrementDialogState(WINDOW * win) {
    if (DialogState >=1 && DialogState<=DialogLength-1) {
        DialogState -= 1;
        DrawDialog(win);
    }
}


void DrawLevel(WINDOW * win, list<NonPlayer*> objs) {
    for (list<NonPlayer*>::iterator n = objs.begin(); n != objs.end(); ++n) {
        (*n)->Draw(win);
    }
}

void ChangeLevel(list<NonPlayer*> &objs, int level, Player &player) {
    switch (level) {
        case 0:
            break;
        case 1:
            objs.push_back(new Triangle(20, 10, 6, 3));
            player.ResetPosition();
    }
}
