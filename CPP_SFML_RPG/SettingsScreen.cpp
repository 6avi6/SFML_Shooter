#include "SettingsScreen.h"


void SettingsScreen::initFont() {
    if (!this->font.loadFromFile("Assets/Fonts/Silkscreen/slkscr.ttf"))
    {
        std::cout << "ERROR::SettingsScreen::initFont()::'couldn't load font slkscr.ttf" << std::endl;
    }
    else {
        //Set Tabp title
        this->TitleOfTab.setFont(font);
        this->TitleOfTab.setString("Settings:");
        this->TitleOfTab.setCharacterSize(30);
        this->TitleOfTab.setFillColor(sf::Color::White);
        this->TitleOfTab.setPosition(30.f, 10.f);

        // Set up apply button
        applyButton.setFont(font);
        applyButton.setString("Apply");
        applyButton.setCharacterSize(24);
        applyButton.setFillColor(sf::Color::Green); // Set color to green
        this->applyButton.setPosition(window->getSize().x - 95.f, window->getSize().y - 40.f);

        // Set up close button
        closeButton.setFont(font);
        closeButton.setString("Close");
        closeButton.setCharacterSize(24);
        closeButton.setFillColor(sf::Color::Red); // Set color to red
        this->closeButton.setPosition(window->getSize().x - 195.f, window->getSize().y - 40.f);
    }


}

SettingsScreen::SettingsScreen(sf::RenderWindow* window, GameSettings* settings)
    : window(window), settings(settings),
    playerSpeedSlider("player Speed", 0, 20, settings->player.speed, sf::Vector2f(100, 100), sf::Vector2f(200, 20)),
    playerReloadSlider("player Reload",0, 60, settings->player.reloadTime, sf::Vector2f(100, 150), sf::Vector2f(200, 20)),
    playerBulletSpeedSlider("player Bullet speed",0, 60, settings->player.bulletSpeed, sf::Vector2f(100, 200), sf::Vector2f(200, 20)),
    enemyReloadSlider("enemy Reload",0, 10, settings->enemy.reloadTime, sf::Vector2f(100, 250), sf::Vector2f(200, 20)),
    enemyBulletSpeedSlider("enemys Bullet speed",0, 60, settings->enemy.bulletSpeed, sf::Vector2f(100, 300), sf::Vector2f(200, 20)),
    numEnemiesSlider("number of Enemies",0, 10, settings->enemy.numEnemies, sf::Vector2f(100, 350), sf::Vector2f(200, 20)),
    isActive(true)
{   
    this->initFont();

}

void SettingsScreen::draw() {
    this->window->clear();
    this->playerSpeedSlider.draw(*(this->window));
    this->playerReloadSlider.draw(*(this->window));
    this->playerBulletSpeedSlider.draw(*(this->window));
    this->enemyReloadSlider.draw(*(this->window));
    this->enemyBulletSpeedSlider.draw(*(this->window));
    this->numEnemiesSlider.draw(*(this->window));
    this->window->draw(this->applyButton);
    this->window->draw(this->closeButton);
    // Draw title
    this->window->draw(this->TitleOfTab);
    this->window->display();
}

void SettingsScreen::handleEvent() {
    
    while (this->window->pollEvent(this->event)) {
        if (event.type == sf::Event::Closed) {
            window->close();
        }
        else if (sf::Event::KeyPressed) {
            if (this->event.key.code == sf::Keyboard::Escape) { //closing after clickin ESC key
                this->isActive = false;
            }
        }
        else if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
                if (applyButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    // Apply button clicked
                    // Save settings and close window
                    // For now, let's just close the window
                    window->close();
                }
                else if (closeButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    // Close button clicked
                    // Close window
                    window->close();
                }
            }
        }
    }
    playerSpeedSlider.update(*window, event);
    playerReloadSlider.update(*window, event);
    playerBulletSpeedSlider.update(*window, event);
    enemyReloadSlider.update(*window, event);
    enemyBulletSpeedSlider.update(*window, event);
    numEnemiesSlider.update(*window, event);

    // Update GameSettings based on slider values
    settings->player.speed = playerSpeedSlider.getValue();
    settings->player.reloadTime = playerReloadSlider.getValue();
    settings->player.bulletSpeed = playerBulletSpeedSlider.getValue();
    settings->enemy.reloadTime = enemyReloadSlider.getValue();
    settings->enemy.bulletSpeed = enemyBulletSpeedSlider.getValue();
    settings->enemy.numEnemies = static_cast<int>(numEnemiesSlider.getValue());
}

bool SettingsScreen::running() const {
    return isActive;
}