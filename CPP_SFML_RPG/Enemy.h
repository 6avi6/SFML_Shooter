#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include "Weapon.h"


class Enemy {
private:
	
	//scale of enlargement
	float width;
	float height;

	//texture of the enemy 
	sf::Texture enemyTexture;

	//object of enemy with texture
	sf::Sprite enemyEntity;

	//initialization of variables
	void initEnemy();

public:
	
	//weapon//
	Weapon* weapon;//wepon
	//initializer weapon
	void initWeapon();


	//default enemy constructor spawns enemy on 0;0 corrdinates
	Enemy();
	//enemy constructor spawns enemy on corrdinates given as attributes x:y
	Enemy(float x, float y);

	//defualt deconstructor
	~Enemy();

	//method rendering on targetted window
	void render(sf::RenderTarget& window);

	//getter of enemy shape is used mainly to detect collison with bullet
	const sf::Sprite getEnemyShape() ;
	

};

#endif // !ENEMY_H


