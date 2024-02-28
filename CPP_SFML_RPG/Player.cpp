#include "Player.h"


void Player::initValues(sf::Vector2i windowSize=sf::Vector2i(0.f, 0.f))
{
	//player sizes
	this->height = 2.f;
	this->width = 2.f;

	//position on map default center
	 this->positonOfPlayer.x= windowSize.x / 2;
	 this->positonOfPlayer.y = windowSize.y / 2;

	//reading texture
	if (!this->skinOfPlayer.loadFromFile("Assets/Textures/playerTexture.png"))
	{
		std::cout << "ERROR::PLAYER::initValues()::'loading texture of player'" << std::endl;
	}
	else{
		this->playerEntity.setTexture(this->skinOfPlayer);
		
		//resizeing player
		this->playerEntity.scale(this->width, this->height);

	}
	
	//attrbiutes
	this->speed = 7;

	this->shape.setSize(sf::Vector2f(this->skinOfPlayer.getSize().x*2.f, this->skinOfPlayer.getSize().y*2.f));
	
	
}

Player::Player(const sf::Vector2i windowSize) {
	this->initValues(windowSize);

}

Player::Player() {
	this->initValues();

}
Player::~Player() 
{

}

//method changing players positon on map

//TO DO: 
//'Reduce number of variable'
//collison handling if player spawns in objects
//collison object other than rectangles
void Player::changePosition(const float increasePositonX,const float increasePositonY, sf::Vector2i windowSize,std::vector<sf::VertexArray> currentMap)
{
	
//checking collision with map wallsObjects
	
	//setting position to new
	shape.setPosition(positonOfPlayer.x += (increasePositonX * this->speed), positonOfPlayer.y += (increasePositonY * this->speed));
	for (const auto& wall : currentMap) {
		
		//making correction of position if objects includes in another objects
		while (this->getShape().getGlobalBounds().intersects(wall.getBounds())) {
			shape.setPosition(positonOfPlayer.x -= (increasePositonX ), positonOfPlayer.y -= (increasePositonY));
		}
		

	}
	
	//Collison handling with window
	if (positonOfPlayer.x > windowSize.x)
		positonOfPlayer.x = 0.f;
	if (positonOfPlayer.y > windowSize.y)
		positonOfPlayer.y = 0.f;
	if (positonOfPlayer.x < 0.f)
		positonOfPlayer.x = windowSize.x;
	if (positonOfPlayer.y < 0.f)
		positonOfPlayer.y = windowSize.y;
		
}

//method rendering player entity in targeted window
void Player::render(sf::RenderTarget& target)
{
	this->playerEntity.setPosition(positonOfPlayer.x, positonOfPlayer.y);
	target.draw(this->playerEntity);
}

sf::Vector2i Player::getPlayerPostion() {
	return positonOfPlayer;
}



const sf::RectangleShape& Player::getShape()const
{	
	
	return this->shape;
}

void Player::collisonDetection(const  sf::RenderTarget *window) {
	
}

void Player::setPosition(float x, float y) {
	this->shape.setPosition(x, y);
	this->positonOfPlayer= sf::Vector2i(x, y);
}



//what should happend when you collaide with object

			/*
			//right collison git
			if (((this->getPlayerPostion().x) + playerXSize) > wall[0].position.x
				&& ((this->getPlayerPostion().x) + playerXSize) > wall[1].position.x) {
				this->setPosition((wall[1].position.x), this->getPlayerPostion().y);
				std::cout << "right collision" << std::endl;
			}
			//bottom collison git
			else if (((this->getPlayerPostion().y)) < wall[3].position.y
				&& ((this->getPlayerPostion().y)) > wall[0].position.y) {
				this->setPosition(this->getPlayerPostion().x, wall[3].position.y);
				std::cout << "bottom collision" << std::endl;
			}
			//top collison raczej git
			else if (((this->getPlayerPostion().y) + playerYSize) > wall[0].position.y
				&& ((this->getPlayerPostion().y) + playerYSize) < wall[3].position.y) {
				this->setPosition(this->getPlayerPostion().x, wall[0].position.y - playerYSize);
				std::cout << "top collision" << std::endl;
			}

			//left collision
			else if (((this->getPlayerPostion().x) + playerXSize) > wall[0].position.x
				&& ((this->getPlayerPostion().x) + playerXSize) < wall[1].position.x) {
				this->setPosition(wall[0].position.x-playerXSize, this->getPlayerPostion().y);
				std::cout << "left collision" << std::endl;
			}
			*/