#include "Game.h"

#include"Player.h"

#include <iostream>
void Game::initVariables() 
{
	this -> window = nullptr;
	//window size
	windowSize.x = 800.f;
	windowSize.y = 600.f;
	videoMode.height = windowSize.y;
	videoMode.width = windowSize.x;
	
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
	this->initWeapon();
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

//Reading input from player
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
		this->player->changePosition(0.f, -1.f, windowSize);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->player->changePosition(0.f, 1.f, windowSize);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->player->changePosition(-1.f, 0.f,windowSize);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->player->changePosition(1.f, 0.f,windowSize);
	
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		// left mouse button is pressed: shoot
		weapon->addNewBullet(this->player->getPlayerPostion(), this->globalMousePosition);
		std::cout << globalMousePosition.x << " : " << globalMousePosition.y << std::endl;
	}
}

//updating event that happenning on screen mouse click etc
void Game::update() 
{
	this->pollEvents();
}

//creating new player
void Game::initPlayer()
{
	player = new Player(this->windowSize);
}

//creating new weapon
void Game::initWeapon() {
	weapon = new Weapon();
}

//method that get positon game window 
//mouse max position is VideoMode.height and width and the lowest are 0a
void Game::getMousePosition()
{

	globalMousePosition = sf::Mouse::getPosition(*window);
	if (globalMousePosition.x > windowSize.x) {
		globalMousePosition.x = windowSize.x;
	}
	else if (globalMousePosition.x <= 0.f) {
		globalMousePosition.x = 0.f;
	}
	if (globalMousePosition.y > windowSize.y) {
		globalMousePosition.y = windowSize.y;
	}
	else if (globalMousePosition.y <= 0.f) {
		globalMousePosition.y = 0.f;
	}
	//std::cout << globalMousePosition.x << " : " << globalMousePosition.y << std::endl;

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
	rectangle.setFillColor(sf::Color(66, 81, 168, 128)); // Green color with 50% transparency
	rectangle.setPosition(125, 200); // Position the rectangle
	this->window->draw(rectangle);



	
	
	//gettin mouse position;
	getMousePosition();

	//drawing bullets
	this->weapon->renderBullets(*this->window);

	//player drawning
	this->player->render(*this->window);

	

	//displaying finall image
	this->window->display();
}