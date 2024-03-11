#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
//#include <SFML/System.hpp>
//#include <SFML/Window.hpp>
//#include <SFML/Audio.hpp>
//#include <SFML/Network.hpp>

//player class
#include "Player.h"

//weapon class
#include "Weapon.h"

//map class
#include "Map.h"

#include "GameSettings.h"
//used for cout and endl
#include <iostream>

//this lib is used for conversion int => string
#include <string>


class Game {
private:
	bool gamePlayed;
	//window fields//
	sf::Vector2i windowSize;	//window size 
	sf::RenderWindow* window;	//window object wherein will be game
	sf::VideoMode videoMode;	//setting of window display like fullscreen/not or size of screen
	sf::Event event;	//event listener for input of user
	sf::ContextSettings settings;//use for changing quality of image

	//init variables
	void initVariables(); 
	//lisiner listener of user inputs
	void pollEvents();
	
	//vector with mouse x & y corrdinates
	sf::Vector2i globalMousePosition;
	//method that return positon of mouse max position is VideoMode.height and width and the lowest are 0
	void getMousePosition();

	//Gameplay settings//
	GameSettings* gameplaySettings;

	//Player Variabels
	Player* player;//player
	
	//init player
	void initPlayer();
	void initPlayer(int playerSpeed, float weaponSpeed, float weaponReload);

	

	//map//
	Map* currentMap;//current map of game
	//map initializer
	void loadMap(int mapNumber=0);


	//fonts//
	sf::Font fontSlkscr;//storing font named:SlKscr
	sf::Text scorePoints;//Text with number of score that will be displayed in game
	//init fonts read from file
	void initFonts();

	
	//how many enemies was killed
	int score;

public:

	//Non argument Construstor;
	Game(sf::RenderWindow* window);
	Game(sf::RenderWindow* window, GameSettings* gameplaySettings);
	//Non argument deconstructor
	virtual ~Game();

	//Accessors
	const bool running() const;

	//Updating values
	void update();

	//Rendering new frame
	void render();


};



#endif // !GAME_H
