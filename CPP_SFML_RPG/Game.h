#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include"Player.h"

class Game {
private:

	//game variables
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event event;
	sf::ContextSettings settings;

	//Player Variabels
	Player* player;

	//init player
	void initPlayer();

	//Private functions
	void initVariables();
	void initWindow();
	void pollEvents();
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
