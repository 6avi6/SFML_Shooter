#include "Player.h"
#include <iostream>

void Player::initValues()
{
	//player sizes
	height = 2.f;
	width = 2.f;

	//position on map default center
	positonX = 800 / 2;
	positonY = 600 / 2;

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

Player::Player() {
	this->initValues();

}

Player::~Player() 
{

}

//method changing players positon on map
void Player::changePosition(const float increasePositonX,const float increasePositonY)
{
	positonX += increasePositonX * this->speed;
	positonY += increasePositonY * this->speed;
		this->playerEntity.setPosition(positonX,positonY);
	
		
}

//method rendering player entity in targeted window
void Player::render(sf::RenderTarget& target)
{
	this->playerEntity.setPosition(positonX, positonY);
	target.draw(this->playerEntity);
}