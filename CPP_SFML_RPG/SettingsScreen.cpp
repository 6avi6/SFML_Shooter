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
        this->applyButtonRectangle.setPosition(window->getSize().x - 95.f, window->getSize().y - 40.f);
        this->applyButtonRectangle.setFillColor(sf::Color(25, 25, 25));
        this->applyButtonRectangle.setSize(sf::Vector2f(this->applyButton.getLocalBounds().getSize().x*1.03, this->applyButton.getLocalBounds().getSize().y * 2));

        // Set up close button
        closeButton.setFont(font);
        closeButton.setString("Close");
        closeButton.setCharacterSize(24);
        closeButton.setFillColor(sf::Color::Red); // Set color to red
        this->closeButton.setPosition(window->getSize().x - 195.f, window->getSize().y - 40.f);
        this->backButtonRectangle.setPosition(window->getSize().x - 195.f, window->getSize().y - 40.f);
        this->backButtonRectangle.setFillColor(sf::Color(25, 25, 25));
        this->backButtonRectangle.setSize(sf::Vector2f(this->closeButton.getLocalBounds().getSize().x*1.03, this->closeButton.getLocalBounds().getSize().y*2));
    }


}
void SettingsScreen::saveSettingsToFile() {
    std::ofstream outputFile(this->settingFilename);
    if (!outputFile.is_open()) {
        // Handle file opening failure
        std::cerr << "Failed to open file: " << this->settingFilename << std::endl;
        return;
    }

    // Write player settings
    outputFile << settings->player.speed << " ";
    outputFile << settings->player.bulletSpeed << " ";
    outputFile << settings->player.reloadTime << std::endl;

    // Write enemy settings
    outputFile << settings->enemy.bulletSpeed << " ";
    outputFile << settings->enemy.reloadTime << " ";
    outputFile << settings->enemy.numEnemies << std::endl;

    outputFile.close();
}

SettingsScreen::SettingsScreen(sf::RenderWindow* window, GameSettings* settings,std::string flieToSave)
    : window(window), settings(settings),settingFilename(flieToSave),
    playerSpeedSlider("player Speed", 0, 100, settings->player.speed, sf::Vector2f(100, 100), sf::Vector2f(200, 20)),
    playerReloadSlider("player Reload",0, 600, settings->player.reloadTime, sf::Vector2f(100, 150), sf::Vector2f(200, 20)),
    playerBulletSpeedSlider("player Bullet speed",0, 20, settings->player.bulletSpeed, sf::Vector2f(100, 200), sf::Vector2f(200, 20)),
    enemyReloadSlider("enemy Reload",0, 600, settings->enemy.reloadTime, sf::Vector2f(100, 250), sf::Vector2f(200, 20)),
    enemyBulletSpeedSlider("enemys Bullet speed",0, 20, settings->enemy.bulletSpeed, sf::Vector2f(100, 300), sf::Vector2f(200, 20)),
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


    this->window->draw(this->applyButtonRectangle);
    this->window->draw(this->backButtonRectangle);
    this->window->draw(this->applyButton);
    this->window->draw(this->closeButton);
    // Draw title
    this->window->draw(this->TitleOfTab);
    this->window->display();
}

void SettingsScreen::handleEvent() {
    

    while (this->window->pollEvent(this->event)) {
        switch (event.type) {
        case sf::Event::Closed:
            window->close();
            break;
        case sf::Event::KeyPressed:
            if (this->event.key.code == sf::Keyboard::Escape) {
                this->isActive = false; // Close window when ESC key is pressed
            }
            break;
        case sf::Event::MouseButtonPressed:
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
                

                // Check if the mouse click is inside the apply button
                if (applyButtonRectangle.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    this->saveSettingsToFile();
                    this->isActive = false; // Close settings screen after applying settings
                }
                else if (backButtonRectangle.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    // Close settings screen when back button is clicked
                    this->isActive = false;
                }
            }
            break;
        default:
            break;
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