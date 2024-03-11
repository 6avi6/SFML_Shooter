#include "Game.h"

void Game::initVariables() 
{
	
	//this -> window = nullptr;
	//window size
	this->windowSize.x = 1000.f;
	this->windowSize.y = 800.f;
	this->videoMode.height = windowSize.y;
	this->videoMode.width = windowSize.x;
	
	//displayed quality higher = better
	//this->settings.antialiasingLevel = 8;
	
	
	this->gamePlayed = true;
}



//lisiner listener of user inputs
void Game::pollEvents()
{


	//Event polling
	while (this->window->pollEvent(this->event))
	{

		switch (this->event.type)
		{
		case sf::Event::Closed: //closing after clickin X
			this->window->close();
			break;
		case sf::Event::KeyPressed:

			if (this->event.key.code == sf::Keyboard::Escape) //closing after clickin ESC key
				this->gamePlayed = false;

			break;
		}


	}
	//move player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->player->changePosition(0.f, -1.f, this->windowSize, this->currentMap->getWallObject());

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->player->changePosition(0.f, 1.f, this->windowSize, this->currentMap->getWallObject());

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->player->changePosition(-1.f, 0.f, this->windowSize, this->currentMap->getWallObject());

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->player->changePosition(1.f, 0.f, this->windowSize, this->currentMap->getWallObject());

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		
		
		
			this->player->weapon->addNewBullet(this->player->getPlayerPostion(), this->globalMousePosition);
		

		//logs how with player score
		//std::cout <<"How many enemies hitted: "<< this->score << std::endl;
		//printing cordinates of the mouse when left button is clicked
		//std::cout << globalMousePosition.x << " : " << globalMousePosition.y << std::endl;
	}
}

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


//creating new player
void Game::initPlayer()
{
	player = new Player(this->windowSize, this->gameplaySettings->player.speed, this->gameplaySettings->player.bulletSpeed,  this->gameplaySettings->player.reloadTime,  this->gameplaySettings->player.playerHealth, this->gameplaySettings->player.weaponDamage);
}


//void Game
void Game::loadMap(int mapNumber) {
	this->currentMap = new Map(mapNumber,this->gameplaySettings);
}

//loading font and init default text communicats
void Game::initFonts() {

	if (!this->fontSlkscr.loadFromFile("Assets/Fonts/Silkscreen/slkscr.ttf"))
	{
		std::cout << "ERROR::GAME::initFonts()::'couldn't load font slkscr.ttf" << std::endl;
	}
	else {
		//setting default score value
		score = 0;
		//setting font of text with scores
		this->scorePoints.setFont(this->fontSlkscr);
		//setting defualt text communicat with scores
		this->scorePoints.setString("Score: " + std::to_string(this->score));
		//setting positon of score points
		this->scorePoints.setPosition(10.f, 0.f);
	}

}


//Non argument Constructor
Game::Game(sf::RenderWindow* window)
{	
	this->window = window;
	this->initVariables();
	this->initPlayer();
	this->loadMap();
	this->initFonts();

}
Game::Game(sf::RenderWindow* window, GameSettings* gameplaySettings)
{
	this->window = window;
	this->gameplaySettings = gameplaySettings;
	this->initVariables();
	this->initPlayer();
	this->loadMap();
	this->initFonts();
	
}
//Non Argument deconstructor
Game::~Game()
{
	//delete this->window;
	delete this->player;
	delete this->currentMap;
	
}

//Accessors
const bool Game::running() const
{	
	
	if (this->window->isOpen() && this->gamePlayed)
		return true;
	else
		return false;
}





//updating event that happenning on screen mouse click etc
void Game::update()
{
	this->pollEvents();

}


//Rendering new frame of window
void Game::render()
{

	


	//enemie fighting back
	if (!this->currentMap->enemies.empty())
		for (int e = 0; e < this->currentMap->enemies.size(); e++) {

			{
				this->currentMap->enemies[e]->weapon->addNewBullet(this->currentMap->enemies[e]->getEnemyShape().getPosition(), sf::Vector2i(this->player->getPlayerPostion().x, this->player->getPlayerPostion().y));

			}
		}


	
	for (int e = 0; e < this->currentMap->enemies.size(); e++) {

		//player hitted by 'e'
		this->player->playerReactionToDamge(this->currentMap->checkIfTargetIsHittedByBullets(this->player->getShape(), this->currentMap->enemies[e]->weapon->getBullets())* this->currentMap->enemies[e]->weapon->getWeaponDamage());
		
		//enemie hitted

		int enemieHittedByPlayerCounter = this->currentMap->checkIfTargetIsHittedByBullets(this->currentMap->enemies[e]->getEnemyShape(), this->player->weapon->getBullets());
		if (enemieHittedByPlayerCounter>0){
			this->currentMap->enemies[e]->enemyReactionToDamage(this->player->weapon->getWeaponDamage()*enemieHittedByPlayerCounter);
			//if enemy is killed by player
			if (this->currentMap->enemies[e]->getEnemyHealth() <= 0) {
				this->currentMap->enemies.erase(this->currentMap->enemies.begin() + e);
				this->currentMap->addEnemy();
				score++;
			}
		}


	}
	
	//if player win or loses will be send to main menu
	if (score > 25) {

		std::cout << "You win ;)" << std::endl;
		this->gamePlayed = false;
	}
	if (this->player->getPlayerHealth()<=0 ) {

		std::cout << "You Lose :(" << std::endl;
		this->gamePlayed = false;
	}



	//Clearing old frame
	this->window->clear(sf::Color(0, 0, 0, 255));
	
	//gettin mouse position;
	this->getMousePosition();

	//**Draw game objects**//

	//Draw map & enemies
	this->currentMap->drawMap(*this->window);

	
	//drawing bullets
	this->player->weapon->renderBullets(*this->window);

	//player drawning
	this->player->render(*this->window);




	//setting new score
	this->scorePoints.setString("Score: " + std::to_string(this->score));
	//drawing points of player
	this->window->draw(this->scorePoints);



	//displaying finall image
	this->window->display();
}