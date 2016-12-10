#include <curses.h>

void DrawDialog(WINDOW *win);
void gameLoop();
void IncrementDialogState(WINDOW * win);
void DecrementDialogState(WINDOW * win);
int DialogState = 0;
int DialogLength = 4;
int segment = 0;

class Door {
    public:
        Door(int ix, int iy, int iw, int ih);
        void Draw(WINDOW *win);
        int GetX() const { return x; };
        void SetX(int ix) {x = ix;};
        int GetY() const { return y; };
        void SetY(int iy) {y = iy;};
        int GetW() const { return w; };
        void SetW(int iw) {w = iw;};
        int GetH() const { return h; };
        void SetH(int ih) {h = ih;};
        
    private:
        int x, y, w, h;
};

class Player {
    public:
        Player(int ix, int iy);
        void Draw(WINDOW *win);
        bool HasCollidedWithDoor(Door * door);
        int GetX() const { return x; };
        void SetX(int ix) {x = ix;};
        int GetY() const { return y; };
        void SetY(int iy) {y = iy;};
        int GetW() const { return w; };
        int GetH() const { return h; };
        
    private:
        int x, y, w, h;
};

Player::Player(int ix, int iy) {
    x = ix;
    y = ix;
    w = 3;
    h = 3;
}

Door::Door(int ix, int iy, int iw, int ih) {
    x = ix;
    y = ix;
    w = iw;
    h = ih;
}

void Player::Draw(WINDOW *win) {
    
    mvwaddch(win, y, x, '@');
    mvwaddch(win, y+1, x, '|');
    mvwaddch(win, y+1, x-1, '-');
    mvwaddch(win, y+1, x+1, '-');
    mvwaddch(win, y+2, x+1, '\\');
    mvwaddch(win, y+2, x-1, '/');
}

void Door::Draw(WINDOW *win) {
    

    for (int j = 0; j<h; j++) {
    
        mvwaddch(win, y+j, x, '|');
        mvwaddch(win, y+j, x+w-1, '|');
    }

    for (int i = 0; i<w; i++) {
        
        mvwaddch(win, y, x+i, '-');
        mvwaddch(win, y+h-1, x+i, '-');
    }
}

bool Player::HasCollidedWithDoor(Door * door) {
    if ((x+w>=door->GetX() && x+w<=door->GetX()+door->GetW() && y+h>=door->GetY() && y+h<=door->GetY()+door->GetH()) ||
        (x>=door->GetX() && x<=door->GetX()+door->GetW() && y+h>=door->GetY() && y+h<=door->GetY()+door->GetH()) ||
        (x>=door->GetX() && x<=door->GetX()+door->GetW() && y>=door->GetY() && y<=door->GetY()+door->GetH()) ||
        (x+w>=door->GetX() && x+w<=door->GetX()+door->GetW() && y>=door->GetY() && y<=door->GetY()+door->GetH())) {
        return true;
    }
    return false;
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
    Player player = Player(10, 10);
    Door door = Door(30, 10, 5, 6);
    int x = 5;
    int y = 5;
    const int DIALOG_HEIGHT = 3;
    const int WIDTH = 100;
    WINDOW * Dialog = newwin(DIALOG_HEIGHT, WIDTH, 0, 0);
    WINDOW * GameArea = newwin(LINES-DIALOG_HEIGHT, WIDTH, DIALOG_HEIGHT+1, 0);
    nodelay(GameArea, TRUE);
    werase(GameArea);
    while (true) {
        DrawDialog(Dialog);
        for (int i = 0; i<WIDTH; i++) {
            mvwaddch(Dialog, DIALOG_HEIGHT-1, i, '-');
            wnoutrefresh(Dialog);
            doupdate();
        }
        if ((ch = getch()) == ERR) {
            continue;
        } else {
            if (ch == 'q') {
                endwin();
                break;
            }
            switch (ch) {
                case 'w':
                    werase(GameArea);
                    player.SetY(player.GetY()-1);
                    if (player.HasCollidedWithDoor(&door)) {
                        IncrementDialogState(Dialog);
                    }
                    player.Draw(GameArea);
                    break;

                case 's':
                    werase(GameArea);
                    player.SetY(player.GetY()+1);
                    player.Draw(GameArea);
                    break;

                case 'a':
                    werase(GameArea);
                    player.SetX(player.GetX()-1);
                    player.Draw(GameArea);
                    break;

                case 'd':
                    werase(GameArea);
                    player.SetX(player.GetX()+1);
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

        door.Draw(GameArea);
        wnoutrefresh(GameArea);
        doupdate();
        }
    }
}

void DrawDialog(WINDOW *win) {
    wclear(win);
    switch (DialogState) {
        case 0:
            mvwprintw(win, 0, 0, "Welcome, to move around, you can use WASD. Press m to continue");
            break;
        case 1:
            mvwprintw(win, 0, 0, "I need your help. The Triangles are coming for me. I need you to fight the triangles, and help me bring back order to the Platonic Reality.");
            break;
        case 2:
            mvwprintw(win, 0, 0, "I need you to go into that door over there.");
            break;
        case 3:
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
