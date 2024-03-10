#ifndef ENEMYSETTINGS_H
#define ENEMYSETTINGS_H

struct EnemySettings {
    float reloadTime;
    float bulletSpeed;
    int numEnemies;

    // Copy operator
    EnemySettings& operator=(const EnemySettings& other) {
        if (this != &other) { // Check for self-assignment
            this->reloadTime = other.reloadTime;
            this->bulletSpeed = other.bulletSpeed;
            this->numEnemies = other.numEnemies;
        }
        return *this;
    }
};

#endif // ENEMYSETTINGS_H
