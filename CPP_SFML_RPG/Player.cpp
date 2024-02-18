#include "Player.h"
#include <iostream>

void Player::initValues(sf::Vector2i windowSize=sf::Vector2i(0.f, 0.f))
{
	//player sizes
	height = 2.f;
	width = 2.f;

	//position on map default center
	 positonOfPlayer.x= windowSize.x / 2;
	 positonOfPlayer.y = windowSize.y / 2;

	//reading texture
	if (!skinOfPlayer.loadFromFile("Assets/Textures/playerTexture.png"))
	{
		std::cout << "ERROR::PLAYER::initValues()::'loading texture of player'" << std::endl;
	}
	else{
		this->playerEntity.setTexture(this->skinOfPlayer);
		
		//resizeing player
		this->playerEntity.scale(width, height);

	}
	
	//attrbiutes
	this->speed = 7;

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
void Player::changePosition(const float increasePositonX,const float increasePositonY, sf::Vector2i windowSize)
{
	positonOfPlayer.x += increasePositonX * this->speed;
	positonOfPlayer.y += increasePositonY * this->speed;

	if (positonOfPlayer.x > windowSize.x)
		positonOfPlayer.x = 0.f;
	if (positonOfPlayer.y > windowSize.y)
		positonOfPlayer.y = 0.f;
	if (positonOfPlayer.x <0.f)
		positonOfPlayer.x = windowSize.x;
	if (positonOfPlayer.y <0.f)
		positonOfPlayer.y = windowSize.y;

		this->playerEntity.setPosition(positonOfPlayer.x, positonOfPlayer.y);
	
		
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