#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H

#include "PlayerSettings.h"
#include "EnemySettings.h"

struct GameSettings {
    PlayerSettings player;
    EnemySettings enemy;

    // Copy operator
    GameSettings& operator=(const GameSettings& other) {
        if (this != &other) { // Check for self-assignment
            this->player = other.player;
            this->enemy = other.enemy;
        }
        return *this;
    }
};

#endif // GAMESETTINGS_H
