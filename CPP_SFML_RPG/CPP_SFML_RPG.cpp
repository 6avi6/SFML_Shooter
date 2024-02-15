#include <iostream>

#include "Game.h"

int main()
{
    Game game;

    //Main Game loop
    while (game.running()) {

       //Read input information keyboard mouse etc
        game.update();

        //Render new frame
        game.render();
    }

    return 0;
}