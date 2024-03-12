#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include "Weapon.h"

#include "HealthBar.h"

class Enemy {
private:
	
	//scale of enlargement
	float width;
	float height;
	float enemyHealth;
	//texture of the enemy 
	sf::Texture enemyTexture;

	//object of enemy with texture
	sf::Sprite enemyEntity;
	sf::Vector2f enemyPosition;
	//initialization of variables
	void initEnemy();

public:
	
	//weapon//
	Weapon* weapon;//wepon
	//initializer weapon
	void initWeapon(float weaponSpeed=4.f, float weaponReload=20.f, float weaponDamage=5.f);

	HealthBar* enemyHealthBar;

	//default enemy constructor spawns enemy on 0;0 corrdinates
	Enemy();
	//enemy constructor spawns enemy on corrdinates given as attributes x:y
	Enemy(float x, float y);
	Enemy(float x, float y,float weweaponSpeed, float weaponReload,float weaponDamage, float enemyHealth );

	//defualt deconstructor
	~Enemy();

	//method rendering on targetted window
	void render(sf::RenderTarget& window);

	//getter of enemy shape is used mainly to detect collison with bullet
	const sf::Sprite getEnemyShape() ;
	
	void enemyReactionToDamage(float playerWeaponDamage);
	const float getEnemyHealth();
};

#endif // !ENEMY_H


