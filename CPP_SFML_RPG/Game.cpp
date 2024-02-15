#include "Game.h"

#include"Player.h"

#include <iostream>
void Game::initVariables() 
{
	this -> window = nullptr;
	//window size
	videoMode.height = 600;
	videoMode.width = 800;
	
	//displayed quality higher = better
	settings.antialiasingLevel = 8;
}

void Game::initWindow()
{
	
	
	//settings of window
	this->window = new sf::RenderWindow(videoMode, "Game Window",sf::Style::Titlebar | sf::Style::Close,settings);

	//frame rate per second limitation
	this->window->setFramerateLimit(60);
}

//Non argument Constructor
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initPlayer();
}

//Non Argument deconstructor
Game::~Game()
{
	delete this->window;
	delete this->player;
}

//Accessors
const bool Game::running() const
{
	return this->window->isOpen();
}

//Function
void Game::pollEvents()
{
	//Event polling
	while (this->window->pollEvent(this->event))
	{

		switch (this->event.type)
		{
		case sf::Event::Closed : //closing after clickin X
			this->window->close();
			break;
		case sf::Event::KeyPressed :	
		
			if (this->event.key.code == sf::Keyboard::Escape) //closing after clickin ESC key
				this->window->close();

			break;
		}

		
	}
	//move player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->player->changePosition(0.f, -1.f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->player->changePosition(0.f, 1.f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->player->changePosition(-1.f, 0.f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->player->changePosition(1.f, 0.f);
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		std::cout << "dzia³a";

}

//updating event that happenning on screen mouse click etc
void Game::update() 
{
	this->pollEvents();
}

void Game::initPlayer()
{
	player = new Player();
}


//Rendering new frame of window
void Game::render() 
{	

	//Clearing old frame
	this->window->clear(sf::Color(0, 0, 0, 255));
	
	//Draw game objects
	

	//kwadrat o usuniêcia
	sf::RectangleShape rectangle(sf::Vector2f(200, 200)); // width: 200, height: 200
	rectangle.setFillColor(sf::Color(0, 255, 0, 128)); // Green color with 50% transparency
	rectangle.setPosition(300, 200); // Position the rectangle
	this->window->draw(rectangle);
	

	//player drawning
	this->player->render(*this->window);

	//kwadrat do usuniecia
	rectangle.setFillColor(sf::Color(66, 81, 168, 128)); // Green color with 50% transparency
	rectangle.setPosition(125, 200); // Position the rectangle
	this->window->draw(rectangle);
	//displaying finall image
	this->window->display();
}