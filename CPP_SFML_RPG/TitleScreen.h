#ifndef TITLESCREEN_H
#define TITLESCREEN_H

#include <SFML/Graphics.hpp>

#include "Game.h"
#include "SettingsScreen.h"
#include <iostream>
#include <fstream>

class TitleScreen {
private:

	sf::RenderWindow *window;
	//game wallpaper//
	sf::Texture wallpaperTexture;
	sf::Sprite wallpaperPicture;
	void loadWallpaper();

	//menu??
	sf::Font titleScreenFont;

	sf::RectangleShape playButton;
	sf::Text playButtonText;
	
	sf::RectangleShape quitButton;
	sf::Text quitButtonText;
	
	sf::RectangleShape settingsButton;
	std::string settingFilename;
	sf::Text settingsButtonText;
	void initFonts();


	void initTitleScreen();
	
	
	Game* game;
	GameSettings *gameplaySettings;
	void readSettingsFromFile();
	
	void initGame();
	void openGame();


	SettingsScreen* settingsScreen;
	void initSettingScreen();
	void openSettingScreen();

public:
	
	TitleScreen(sf::RenderWindow* window);
	void drawScreen();

};

#endif // !TITLESCREEN_H
