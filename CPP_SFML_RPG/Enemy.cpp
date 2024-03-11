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

//creating new weapon
void Enemy::initWeapon(float weaponSpeed, float weaponReload, float weaponDamage) {
	
	this->weapon = new Weapon(weaponSpeed, weaponReload, weaponDamage);
}

//default constructor
Enemy::Enemy(){
	this->initEnemy();
}

//enemy constructor spawns enemy on corrdinates given as attributes x:y
Enemy::Enemy(float x, float y)
{	
	this->initEnemy();
	this->initWeapon();
	this->enemyEntity.setPosition(x,y);
}

Enemy::Enemy(float x, float y, float weaponSpeed, float weaponReload, float weaponDamage, float enemyHealth):
	enemyHealth(enemyHealth)
{
	this->initEnemy();
	this->enemyEntity.setPosition(x, y);
	this->initWeapon(weaponSpeed, weaponReload, weaponDamage);
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

void Enemy::enemyReactionToDamage(float playerWeaponDamage)
{
	this->enemyHealth -=playerWeaponDamage;
}

const float Enemy::getEnemyHealth()
{
	return this->enemyHealth;
}








