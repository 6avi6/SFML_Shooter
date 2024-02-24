#include "Game.h"


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
	this->loadMap();
	
}

//Non Argument deconstructor
Game::~Game()
{
	delete this->window;
	delete this->player;
	delete this->weapon;
	delete this->currentMap;
	
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
		this->player->changePosition(0.f, -1.f, windowSize,this->currentMap->getWallObject());

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->player->changePosition(0.f, 1.f, windowSize, this->currentMap->getWallObject());

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->player->changePosition(-1.f, 0.f,windowSize, this->currentMap->getWallObject());

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->player->changePosition(1.f, 0.f,windowSize, this->currentMap->getWallObject());
	
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		// left mouse button is pressed: shoot
		this->weapon->addNewBullet(this->player->getPlayerPostion(), this->globalMousePosition);
		this->currentMap->checkIfEnemyHitted((this->weapon->getBullets()));
		//printing cordinates of the mouse when left button is clicked
		//std::cout << globalMousePosition.x << " : " << globalMousePosition.y << std::endl;
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

//void Game
void Game::loadMap(int mapNumber) {
	currentMap =new Map(mapNumber);
}

/*
void Game::updateCollisonDetection() {
	
	float playerXSize = (this->player->getShape().getSize().x) ;
	float playerYSize = (this->player->getShape().getSize().y) ;
	for (const auto& wall : this->currentMap->getWallObject()) {
		if (this->player->getShape().getGlobalBounds().intersects(wall.getBounds())) {
			//what should happend when you collaide with object


			//right collison git
		 if (((this->player->getPlayerPostion().x) + playerXSize) > wall[0].position.x
			&& ((this->player->getPlayerPostion().x) + playerXSize) > wall[1].position.x) {
			this->player->setPosition((wall[1].position.x), this->player->getPlayerPostion().y);
			std::cout << "right collision" << std::endl;
		}
		 //bottom collison git
		 else if (((this->player->getPlayerPostion().y)) < wall[3].position.y
			 && ((this->player->getPlayerPostion().y)) > wall[0].position.y) {
			 this->player->setPosition(this->player->getPlayerPostion().x, wall[3].position.y);
			 std::cout << "bottom collision" << std::endl;
		 }
		 //top collison raczej git
		 else if (((this->player->getPlayerPostion().y) + playerYSize) > wall[0].position.y
			 && ((this->player->getPlayerPostion().y) + playerYSize) < wall[3].position.y) {
			 this->player->setPosition(this->player->getPlayerPostion().x, wall[0].position.y - playerYSize);
			 std::cout << "top collision" << std::endl;
		 }
		
			
		 //left collision
			else if (((this->player->getPlayerPostion().x) < wall[1].position.x)
				&& ((this->player->getPlayerPostion().x) > wall[0].position.x)) {
			 this->player->setPosition(wall[1].position.x, this->player->getPlayerPostion().y);
			 std::cout << "left collision" << std::endl;
		 }
		
			

		}
			
	}
	

}*/

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

}


//Rendering new frame of window
void Game::render() 
{	
	

	//Clearing old frame
	this->window->clear(sf::Color(0, 0, 0, 255));
	
	//Draw map & enemies
	
	this->currentMap->drawMap(*this->window);

	//Draw game objects
	
	//gettin mouse position;
	getMousePosition();

	

	//drawing bullets
	this->weapon->renderBullets(*this->window);

	//player drawning
	this->player->render(*this->window);

	

	//displaying finall image
	this->window->display();
}