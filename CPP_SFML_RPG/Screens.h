#ifndef SCREENS_H
#define SCREENS_H

#include <SFML/Graphics.hpp>

#include "TitleScreen.h"


class Screens {
private:

	sf::Vector2i windowSize;	//window size 
	sf::RenderWindow* window;	//window object wherein will be game
	sf::VideoMode videoMode;	//setting of window display like fullscreen/not or size of screen
	sf::Event event;	//event listener for input of user
	sf::ContextSettings settings;//use for changing quality of image

	
	

	TitleScreen* titleScreen;
	void initWindow();
	
	void initTitleScreen();
	void openTitleScreen();
	
public:
	Screens();

	void Start();
	
	
};


#endif // !define SCREENS_H

