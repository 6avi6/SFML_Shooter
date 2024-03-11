#ifndef PLAYERSETTINGS_H
#define PLAYERSETTINGS_H

struct PlayerSettings {
    float speed;
    float reloadTime;
    float bulletSpeed;
    float weaponDamage;
    float playerHealth;

    // Copy operator
    PlayerSettings& operator=(const PlayerSettings& other) {
        if (this != &other) { // Check for self-assignment
            this->speed = other.speed;
            this->reloadTime = other.reloadTime;
            this->bulletSpeed = other.bulletSpeed;
            this->weaponDamage = other.weaponDamage;
            this->playerHealth = other.playerHealth;
        }
        return *this;
    }
};


#endif // PLAYERSETTINGS_H
