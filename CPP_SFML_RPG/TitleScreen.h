#ifndef TITLESCREEN_H
#define TITLESCREEN_H

#include <SFML/Graphics.hpp>

#include "Game.h"
#include <iostream>
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
	sf::Text settingsButtonText;
	void initFonts();


	void initTitleScreen();
	void initGame();
	void openGame();
	
	Game* game;
public:
	TitleScreen(sf::RenderWindow* window);
	void drawScreen();

};

#endif // !TITLESCREEN_H
