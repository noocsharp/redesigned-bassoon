#include <curses.h>
#include <list>
#include "door.h"
#include "triangle.h"
#include "player.h"
#include "nonplayer.h"

using std::list;

class Game {
    public:
        Game();
        ~Game();
        int getLevel() { return level; };
        void setLevel(int ilevel) { level = ilevel; };
        int getDialogState() { return dialogState; };
        void setDialogState(int idialogState) { dialogState = idialogState; };
        list<NonPlayer*>* getNonPlayerObjects() { return &nonPlayerObjects; };
        WINDOW* getDialog() { return dialog; };
        WINDOW* getGameArea() { return gameArea; };
        Player* getPlayer() { return &player; };
        void gameLoop();
        void drawDialog();
        void incrementDialogState();
        void decrementDialogState();
        void drawLevel();
        void changeLevel();
        static const int DIALOG_HEIGHT = 3;
        static const int WIDTH = 100;
        static const int DIALOG_LENGTH = 5;

    private:
        int dialogState;
        int level;
        void movePlayerRoutine();
        WINDOW * dialog = 0;
        WINDOW * gameArea = 0;
        Player player;
        list<NonPlayer*> nonPlayerObjects;
        list<NonPlayer*>::iterator NPOIterator;
};


