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

//enemy constructor spawns enemy on corrdinates given as attributes x:y
Enemy::Enemy(float x, float y)
{	
	this->initEnemy();
	this->enemyEntity.setPosition(x,y);
}

//defualt deconstructor
Enemy::~Enemy(){
	
}

//method rendering on targetted window
void Enemy::render(sf::RenderTarget& window) {

	window.draw(this->enemyEntity);
}

//getter of enemy shape is used mainly to detect collison with bullet
const sf::Sprite Enemy::getEnemyShape()
{
	return this->enemyEntity;

}








