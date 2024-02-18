#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Player.h"
#include "Weapon.h"

class Game {
private:

	//game variables
	sf::Vector2i windowSize;
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event event;
	sf::ContextSettings settings;


	
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
