#include "game.h"

Game::Game():player(0, 0) {
    dialogState = 0;
    level = 0;
    initscr();
    noecho();
    curs_set(0);
    dialog = newwin(DIALOG_HEIGHT, WIDTH, 0, 0);
    gameArea = newwin(LINES-DIALOG_HEIGHT, WIDTH, DIALOG_HEIGHT+1, 0);
    nonPlayerObjects.push_back(new Door(30, 10, 6, 6));
    NPOIterator = nonPlayerObjects.begin();
    nodelay(gameArea, TRUE);
    werase(gameArea);
}

Game::~Game() {
    for (list<NonPlayer*>::iterator n = nonPlayerObjects.begin(); n != nonPlayerObjects.end(); ++n) {
        delete *n;
    }
}

void Game::drawDialog() {
    // TODO try removing wclear(dialog) and see how it affects rendering
    wclear(dialog);
    switch (dialogState) {
        case 0:
            mvwprintw(dialog, 0, 0, "Welcome. To move around, you can use WASD. Press m to move dialog forward, and n to move dialog backward");
            break;
        case 1:
            mvwprintw(dialog, 0, 0, "The triangles want to invade reality. You need to stop it.");
            break;
        case 2:
            mvwprintw(dialog, 0, 0, "I need you to imagine that rectangle is a door. Now go in it");
            break;
        case 3:
            mvwprintw(dialog, 0, 0, "Now go kill the representation of a triangle!");
            break;
        case 4:
            mvwprintw(dialog, 0, 0, "Congrats! You win! Press q to get out of this piece of trash disguised as a game!");
            break;
        default:
            mvwprintw(dialog, 0, 0, "Well... the code is messed up");
            break;
    }
    for (int i = 0; i<WIDTH; ++i) {
        mvwaddch(dialog, Game::DIALOG_HEIGHT-1, i, '-');
    }
}

void Game::incrementDialogState() {
    if (dialogState >=0 && dialogState<=DIALOG_LENGTH-2) {
        dialogState += 1;
    }
}

void Game::decrementDialogState() {
    if (dialogState >=1 && dialogState<=DIALOG_LENGTH-1) {
        dialogState -= 1;
    }
}

void Game::drawLevel() {
    for (list<NonPlayer*>::iterator n = nonPlayerObjects.begin(); n != nonPlayerObjects.end(); ++n) {
        (*n)->Draw(gameArea);
    }
}

void Game::changeLevel() {
    switch (level) {
        case 0:
            break;
        case 1:
            nonPlayerObjects.push_back(new Triangle(20, 10, 6, 3));
            player.ResetPosition();
    }
}

void Game::movePlayerRoutine() {
    werase(gameArea);
    NPOIterator = nonPlayerObjects.begin();
    if (player.HasCollidedWithDoor(static_cast<Door*>(*NPOIterator)) && nonPlayerObjects.size() == 1) {
        ++level;
        changeLevel();
    }
    for (NPOIterator = ++nonPlayerObjects.begin(); NPOIterator != nonPlayerObjects.end(); ++NPOIterator) {
        if (player.HasCollidedWithTriangle(dynamic_cast<Triangle*>(*NPOIterator))) {
            (static_cast<Triangle*>(*NPOIterator))->hide();
        }
    }
    player.Draw(gameArea);
}

void Game::gameLoop() {

    int ch;
    drawDialog();
    while (true) {
        if ((ch = wgetch(gameArea)) == ERR) {
            continue;
        } else { if (ch == 'q') {
                endwin();
                break;
            }
            switch (ch) {
                case 'w':
                    player.SetY(player.GetY()-1);
                    movePlayerRoutine();
                    break;

                case 's':
                    player.SetY(player.GetY()+1);
                    movePlayerRoutine();
                    break;

                case 'a':
                    player.SetX(player.GetX()-1);
                    movePlayerRoutine();
                    break;

                case 'd':
                    player.SetX(player.GetX()+1);
                    movePlayerRoutine();
                    break;
                
                case 'm':
                    incrementDialogState();
                    drawDialog();
                    break;
                case 'n':
                    decrementDialogState();
                    drawDialog();
                    break;
                default:
                    continue;

            }
        drawLevel();
        wnoutrefresh(gameArea);
        wnoutrefresh(dialog);
        doupdate();
        }
    }
}
