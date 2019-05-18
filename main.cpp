#include "game.h"


int main()
{
    while (true) {
        game newGame;
        newGame.intro();
        if (newGame.closed) return 0;
    }

}
