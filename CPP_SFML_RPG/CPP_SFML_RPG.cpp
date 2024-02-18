#include <iostream>

#include "Game.h"

#include "vector"

int main()
{
    std::vector <int> vec = { 1,2,3 };
    vec.erase(vec.begin());
    
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