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

//used for cout and endl
#include <iostream>

//this lib is used for conversion int => string
#include <string>

class Game {
private:

	//game variables
	//window size 
	sf::Vector2i windowSize;
	//window object wherein will be game
	sf::RenderWindow* window;
	//setting of window display like fullscreen/not or size of screen
	sf::VideoMode videoMode;
	//event listener for input of user
	sf::Event event;
	//use for changing quality of image
	sf::ContextSettings settings;

	int counter;
	//vector with mouse x & y corrdinates
	sf::Vector2i globalMousePosition;
	//Player Variabels
	Player* player;

	//init player
	void initPlayer();

	//Init weapon
	Weapon* weapon;
	void initWeapon();

	//Private functions
	void initVariables();
	void initWindow();
	void pollEvents();
	
	//method that return positon of mouse max position is VideoMode.height and width and the lowest are 0
	void getMousePosition();

	Map* currentMap;
	void loadMap(int mapNumber=0);
	
	//fonts 

	//init fonts read from file
	void initFonts();

	//font named:SlKscr
	sf::Font fontSlkscr;

	//Text with number of score that will be displayed in game
	sf::Text scorePoints;
	
	//how many enemies was killed
	int score;


public:

	//Non argument Construstor;
	Game();
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
