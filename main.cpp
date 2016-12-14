#include <curses.h>
#include <list>
#include <typeinfo>
#include "nonplayer.h"
#include "door.h"
#include "triangle.h"
#include "player.h"

using std::list;



void DrawDialog(WINDOW *win);
void gameLoop();
void IncrementDialogState(WINDOW * win);
void DecrementDialogState(WINDOW * win);
void DrawLevel(WINDOW * win, list<NonPlayer*>);
void ChangeLevel(WINDOW * win, list<NonPlayer*> &objs, int level, Player &player);
int DialogState = 0;
int DialogLength = 5;

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
        } else { if (ch == 'q') {
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
                    if (player.HasCollidedWithDoor(static_cast<Door*>(*NPOIterator)) && NonPlayerObjects.size() == 1) {
                        ++level;
                        ChangeLevel(GameArea, NonPlayerObjects, level, player);
                    }
                    for (NPOIterator = ++NonPlayerObjects.begin(); NPOIterator != NonPlayerObjects.end(); ++NPOIterator) {
                        if (player.HasCollidedWithTriangle(dynamic_cast<Triangle*>(*NPOIterator))) {
                            (static_cast<Triangle*>(*NPOIterator))->hide();
                        }
                    }
                    player.Draw(GameArea);
                    break;

                case 's':
                    werase(GameArea);
                    player.SetY(player.GetY()+1);
                    NPOIterator = NonPlayerObjects.begin();
                    if (player.HasCollidedWithDoor(static_cast<Door*>(*NPOIterator)) && NonPlayerObjects.size() == 1) {
                        ++level;
                        ChangeLevel(GameArea, NonPlayerObjects, level, player);
                    }
                    for (NPOIterator = ++NonPlayerObjects.begin(); NPOIterator != NonPlayerObjects.end(); ++NPOIterator) {
                        if (player.HasCollidedWithTriangle(dynamic_cast<Triangle*>(*NPOIterator))) {
                            (static_cast<Triangle*>(*NPOIterator))->hide();
                        }
                    }
                    player.Draw(GameArea);
                    break;

                case 'a':
                    werase(GameArea);
                    player.SetX(player.GetX()-1);
                    NPOIterator = NonPlayerObjects.begin();
                    if (player.HasCollidedWithDoor(static_cast<Door*>(*NPOIterator)) && NonPlayerObjects.size() == 1) {
                        ++level;
                        ChangeLevel(GameArea, NonPlayerObjects, level, player);
                    }
                    for (NPOIterator = ++NonPlayerObjects.begin(); NPOIterator != NonPlayerObjects.end(); ++NPOIterator) {
                        if (player.HasCollidedWithTriangle(dynamic_cast<Triangle*>(*NPOIterator))) {
                            (static_cast<Triangle*>(*NPOIterator))->hide();
                        }
                    }
                    player.Draw(GameArea);
                    break;

                case 'd':
                    werase(GameArea);
                    player.SetX(player.GetX()+1);
                    NPOIterator = NonPlayerObjects.begin();
                    if (player.HasCollidedWithDoor(static_cast<Door*>(*NPOIterator)) && NonPlayerObjects.size() == 1) {
                        ++level;
                        ChangeLevel(GameArea, NonPlayerObjects, level, player);
                    }
                    for (NPOIterator = ++NonPlayerObjects.begin(); NPOIterator != NonPlayerObjects.end(); ++NPOIterator) {
                        if (player.HasCollidedWithTriangle(dynamic_cast<Triangle*>(*NPOIterator))) {
                            (static_cast<Triangle*>(*NPOIterator))->hide();
                        }
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
            mvwprintw(win, 0, 0, "I need you to imagine that rectangle is a door. Now go in it");
            break;
        case 3:
            mvwprintw(win, 0, 0, "Now go kill the representation of a triangle!");
            break;
        case 4:
            mvwprintw(win, 0, 0, "Congrats! You win! Press q to get out of this piece of trash disguised as a game!");
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

void ChangeLevel(WINDOW * win, list<NonPlayer*> &objs, int level, Player &player) {
    switch (level) {
        case 0:
            break;
        case 1:
            objs.push_back(new Triangle(20, 10, 6, 3));
            player.ResetPosition();
        case 2:
            mvwprintw(win, 0, 0, "You Win!");
    }
}
