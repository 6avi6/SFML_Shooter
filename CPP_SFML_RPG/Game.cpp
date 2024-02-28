#include "Game.h"




void Game::initVariables() 
{
	this -> window = nullptr;
	//window size
	this->windowSize.x = 800.f;
	this->windowSize.y = 600.f;
	this->videoMode.height = windowSize.y;
	this->videoMode.width = windowSize.x;
	
	//displayed quality higher = better
	this->settings.antialiasingLevel = 8;
	
	this->counter = 0;
}

//setting window attribs
void Game::initWindow()
{
	
	
	//settings of window
	this->window = new sf::RenderWindow(videoMode, "Game Window",sf::Style::Titlebar | sf::Style::Close,settings);

	//frame rate per second limitation
	this->window->setFramerateLimit(60);
}


//loading font and init default text communicats
void Game::initFonts(){
	
	if (!this->fontSlkscr.loadFromFile("Assets/Fonts/Silkscreen/slkscr.ttf"))
	{
		std::cout<<"ERROR::GAME::initFonts()::'couldn't load font slkscr.ttf" << std::endl;
	}
	else {
		//setting default score value
		score = 0;
		//setting font of text with scores
		this->scorePoints.setFont(this->fontSlkscr);
		//setting defualt text communicat with scores
		this->scorePoints.setString("Score: "+ std::to_string(this->score));
		//setting positon of score points
		this->scorePoints.setPosition(10.f, 0.f);
	}

}


//Non argument Constructor
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initPlayer();
	this->initWeapon();
	this->loadMap();
	this->initFonts();
	
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
		this->player->changePosition(0.f, -1.f, this->windowSize,this->currentMap->getWallObject());

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->player->changePosition(0.f, 1.f, this->windowSize, this->currentMap->getWallObject());

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->player->changePosition(-1.f, 0.f, this->windowSize, this->currentMap->getWallObject());

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->player->changePosition(1.f, 0.f,this->windowSize, this->currentMap->getWallObject());
	
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		// left mouse button is pressed: shoot
		if (!this->weapon->weaponFired )
		{
			this->weapon->addNewBullet(this->player->getPlayerPostion(), this->globalMousePosition);
			this->weapon->weaponFired = true;
		}
		
		//logs how with player score
		//std::cout <<"How many enemies hitted: "<< this->score << std::endl;
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
	this->weapon = new Weapon();
}

//void Game
void Game::loadMap(int mapNumber) {
	this->currentMap =new Map(mapNumber);
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

	this->globalMousePosition = sf::Mouse::getPosition(*window);

	//if postion of mouse if beyond of window setting postion of mouse to the postion of border
	if (this->globalMousePosition.x > this->windowSize.x) {
		this->globalMousePosition.x = this->windowSize.x;
	}
	else if (this->globalMousePosition.x <= 0.f) {
		this->globalMousePosition.x = 0.f;
	}
	if (this->globalMousePosition.y > this->windowSize.y) {
		this->globalMousePosition.y = this->windowSize.y;
	}
	else if (this->globalMousePosition.y <= 0.f) {
		this->globalMousePosition.y = 0.f;
	}

}


//Rendering new frame of window
void Game::render() 
{	
	
	if(this->weapon->weaponFired )
		this->counter++;
		
	if (counter == 60 - this->weapon->weaponReload) {
		counter = 0;
		this->weapon->weaponFired = false;
	}
		

	//Clearing old frame
	this->window->clear(sf::Color(0, 0, 0, 255));
	
	//gettin mouse position;
	this->getMousePosition();

	//**Draw game objects**//

	//Draw map & enemies
	this->currentMap->drawMap(*this->window);

	//drawing bullets
	this->weapon->renderBullets(*this->window);

	//player drawning
	this->player->render(*this->window);



	//collison detecion and handling bullet with enemy if enemy was kiled return how many enemies was killed and adding that number to score
	this->score += (this->currentMap->checkIfEnemyHitted((this->weapon->getBullets())));

	this->currentMap->checkIfWallHitted((this->weapon->getBullets()));

	//setting new score
	this->scorePoints.setString("Score: " + std::to_string(this->score));
	//drawing points of player
	this->window->draw(this->scorePoints);



	//displaying finall image
	this->window->display();
}