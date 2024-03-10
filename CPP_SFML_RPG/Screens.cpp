#include "Screens.h"


void Screens::initWindow() {
	this->window = nullptr;
	//window size
	this->windowSize.x = 1000.f;
	this->windowSize.y = 800.f;
	this->videoMode.height = windowSize.y;
	this->videoMode.width = windowSize.x;

	
	//displayed quality higher = better
	this->settings.antialiasingLevel = 8;
	this->window = new sf::RenderWindow(videoMode, "Game Window", sf::Style::Titlebar | sf::Style::Close, settings);
	this->window->setFramerateLimit(60);
}



void Screens::initTitleScreen()
{	
	 this->titleScreen = new TitleScreen(window);
}

void Screens::openTitleScreen()
{
	this->titleScreen->drawScreen();
}



Screens::Screens() {
	this->initWindow();
	
	this->initTitleScreen();
}

void Screens::Start() {
    //this->openGame();
	this->openTitleScreen();
}