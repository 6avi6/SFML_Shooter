#ifndef SETTINGSSCREEN_H
#define SETTINGSSCREEN_H

#include "Slider.h"
#include "GameSettings.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class SettingsScreen {
private:
    sf::RenderWindow* window;
    GameSettings* settings;
    Slider playerSpeedSlider;
    Slider playerReloadSlider;
    Slider playerBulletSpeedSlider;
    Slider enemyReloadSlider;
    Slider enemyBulletSpeedSlider;
    Slider numEnemiesSlider;
   

    // Text
    sf::Font font;
    sf::Text applyButton;
    sf::Text closeButton; // Added button to close window
    sf::Text TitleOfTab;
    void initFont();

    sf::Event event;
    bool isActive;
public:
    SettingsScreen(sf::RenderWindow* window, GameSettings* settings);

    void draw();
    void handleEvent();
    bool running() const; // Method to check if screen is active
};

#endif // SETTINGSSCREEN_H


