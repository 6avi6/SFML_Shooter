#include "TitleScreen.h"

void TitleScreen::initTitleScreen() {
    int scale = 2;
    sf::Vector2f playButtonSize(200*scale, 50 * scale);
    sf::Vector2f settingsButtonSize(95 * scale, 50 * scale);
    sf::Vector2f quitButtonSize(95 * scale, 50 * scale);

   this->playButton.setSize(playButtonSize);
   this->playButton.setFillColor(sf::Color(78,133,181));

   this->quitButton.setSize(quitButtonSize);
   this->quitButton.setFillColor(sf::Color(150,5,30));

   this->settingsButton.setSize(settingsButtonSize);
   this->settingsButton.setFillColor(sf::Color(80,80,85));

   float screenWidth = static_cast<float>(window->getSize().x);
   float screenHeight = static_cast<float>(window->getSize().y);

   sf::Vector2f playButtonPosition((screenWidth - playButtonSize.x) / 2, screenHeight / 2 - playButtonSize.y);
   sf::Vector2f settingsButtonPosition(playButtonPosition.x , playButtonPosition.y + playButtonSize.y + 10*scale);
   sf::Vector2f quitButtonPosition(playButtonPosition.x + settingsButtonSize.x + 10*scale, playButtonPosition.y + playButtonSize.y + 10*scale);
   playButton.setPosition(playButtonPosition);
   settingsButton.setPosition(settingsButtonPosition);
   quitButton.setPosition(quitButtonPosition);

   this->initFonts();
   this->loadWallpaper();
   this->settingFilename = "Data/gameSettings.txt";
   this->readSettingsFromFile();
}

TitleScreen::TitleScreen(sf::RenderWindow* window)
{
    this->window = window;
    this ->initTitleScreen();
    
}

void TitleScreen::drawScreen()
{
    while (this->window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(*window);

                    if (playButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        this->initGame();
                        this->openGame();

                    }
                    else if (quitButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        // Handle Quit button click
                        window->close();
                    }
                    else if (settingsButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        // Handle Settings button click
                        this->initSettingScreen();
                        this->openSettingScreen();
                        delete this->settingsScreen;
                    }
                }
            }
        }

        this->window->clear();
        //drawing here title sreen with main menu//
        for(int x=0;x<window->getSize().x;x+=this->wallpaperTexture.getSize().x)
            for (int y = 0; y < window->getSize().y; y += this->wallpaperTexture.getSize().y-2.f)
            {   
                this->wallpaperPicture.setPosition(x, y);
                this->window->draw(this->wallpaperPicture);
            }

        this->window->draw(this->playButton);
        this->window->draw(this->playButtonText);

        this->window->draw(this->quitButton);
        this->window->draw(this->quitButtonText);
       
        this->window->draw(this->settingsButton);
        this->window->draw(this->settingsButtonText);
        this->window->display();
    }
}


//Game//
void TitleScreen::initGame() {
    //if some game already existed deleting that game and starting new
    if (this->game != nullptr)
        delete this->game;

    this->game = new Game(window,gameplaySettings);


}

void TitleScreen::openGame() {


    //Main Game loop
    while (this->game->running()) {

        //Read input information keyboard mouse etc
        this->game->update();

        //Render new frame
        this->game->render();
    }



}


void TitleScreen::readSettingsFromFile() {
    std::ifstream inputFile(this->settingFilename);
    
    if (!inputFile.is_open()) {
        // Handle file opening failure
        std::cerr << "ERROR::TitleScreen::readSettingsFromFile()::'Failed to open file:' " << this->settingFilename << std::endl;
        return;
    }
    this->gameplaySettings = new GameSettings();
    // Read player settings
    inputFile >> gameplaySettings->player.speed;
    inputFile >> gameplaySettings->player.bulletSpeed;
    inputFile >> gameplaySettings->player.reloadTime;
    inputFile >> gameplaySettings->player.playerHealth;
    inputFile >> gameplaySettings->player.weaponDamage;

    // Read enemy settings
    inputFile >> gameplaySettings->enemy.bulletSpeed;
    inputFile >> gameplaySettings->enemy.reloadTime;
    inputFile >> gameplaySettings->enemy.numEnemies;
    inputFile >> gameplaySettings->enemy.enemyHealth;
    inputFile >> gameplaySettings->enemy.weaponDamage;

    inputFile.close();

}


void TitleScreen::initSettingScreen() {
    this->settingsScreen = new SettingsScreen(this->window, this->gameplaySettings,this->settingFilename);
}
void TitleScreen::openSettingScreen() {
    //Main Game loop
    while (this->settingsScreen->running()) {

        //Read input information keyboard mouse etc
        this->settingsScreen->handleEvent();
        this->settingsScreen->draw();

       
    }
}

void TitleScreen::loadWallpaper()
{
    //reading texture
    if (!this->wallpaperTexture.loadFromFile("Assets/Textures/wallpaperTexture.png"))
    {
        std::cout << "ERROR::TITLESCREENS::loadWallpaper()::'loading title screen wallpaper failuer'" << std::endl;
    }
    else {
        this->wallpaperPicture.setTexture(this->wallpaperTexture);

        //resizeing player
       
        //this->wallpaperPicture.scale(50.f,50.f);

    }

}

void TitleScreen::initFonts()
{
    if (!this->titleScreenFont.loadFromFile("Assets/Fonts/Silkscreen/slkscr.ttf"))
    {
        std::cout << "ERROR::GAME::initFonts()::'couldn't load font slkscr.ttf" << std::endl;
    }
    else {
        //setting button text and style of each one

        //play button
        this->playButtonText.setFont(this->titleScreenFont);
        this->playButtonText.setString("Play");
        this->playButtonText.setOrigin(sf::Vector2f(this->playButtonText.getLocalBounds().getSize().x / 2, this->playButtonText.getLocalBounds().getSize().y / 2));
        this->playButtonText.setPosition(this->playButton.getPosition().x + this->playButton.getLocalBounds().getSize().x / 2, this->playButton.getPosition().y + this->playButton.getLocalBounds().getSize().y / 2);
        this->playButtonText.setFillColor(sf::Color::White);
        //settings button
        this->settingsButtonText.setFont(this->titleScreenFont);
        this->settingsButtonText.setString("Settings");
        this->settingsButtonText.setOrigin(sf::Vector2f(this->settingsButtonText.getLocalBounds().getSize().x / 2, this->settingsButtonText.getLocalBounds().getSize().y / 2));
        this->settingsButtonText.setPosition(this->settingsButton.getPosition().x + this->settingsButton.getLocalBounds().getSize().x / 2, this->settingsButton.getPosition().y + this->settingsButton.getLocalBounds().getSize().y / 2);
        this->settingsButtonText.setFillColor(sf::Color::White);
        //quit button
        this->quitButtonText.setFont(this->titleScreenFont);
        this->quitButtonText.setString("Quit");
        this->quitButtonText.setOrigin(sf::Vector2f(this->quitButtonText.getLocalBounds().getSize().x/2, this->quitButtonText.getLocalBounds().getSize().y / 2));
        this->quitButtonText.setPosition(this->quitButton.getPosition().x + this->quitButton.getLocalBounds().getSize().x / 2, this->quitButton.getPosition().y + this->quitButton.getLocalBounds().getSize().y / 2);
        this->quitButtonText.setFillColor(sf::Color::White);
    }

}
