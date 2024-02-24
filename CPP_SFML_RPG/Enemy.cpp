#include "Enemy.h"

#include <iostream>
 
void Enemy::initEnemy() {

	//enemy scalars
	this->height = 2.f;
	this->width = 2.f;

	if (!enemyTexture.loadFromFile("Assets/Textures/enemyTexture.png"))
	{
		std::cout << "ERROR::PLAYER::initEnemy()::'loading texture of enemy'" << std::endl;
	}
	else {
		this->enemyEntity.setTexture(this->enemyTexture);

		//resizeing player
		this->enemyEntity.scale(width, height);

	}
	


}

//default constructor
Enemy::Enemy(){
	this->initEnemy();
}



Enemy::Enemy(float x, float y)
{	
	this->initEnemy();
	this->enemyEntity.setPosition(x,y);
}

Enemy::~Enemy(){
	
}

void Enemy::render(sf::RenderTarget& target) {

	target.draw(this->enemyEntity);
}

const sf::Sprite Enemy::getEnemyShape()
{
	return this->enemyEntity;

}








