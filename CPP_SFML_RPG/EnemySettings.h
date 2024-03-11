#ifndef ENEMYSETTINGS_H
#define ENEMYSETTINGS_H

struct EnemySettings {
    float reloadTime;
    float bulletSpeed;
    float weaponDamage;
    int numEnemies;
    float enemyHealth;

    // Copy operator
    EnemySettings& operator=(const EnemySettings& other) {
        if (this != &other) { // Check for self-assignment
            this->reloadTime = other.reloadTime;
            this->bulletSpeed = other.bulletSpeed;
            this->weaponDamage = other.weaponDamage;
            this->numEnemies = other.numEnemies;
            this->enemyHealth = other.enemyHealth;
        }
        return *this;
    }
};

#endif // ENEMYSETTINGS_H
