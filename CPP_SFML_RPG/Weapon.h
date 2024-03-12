#ifndef WEAPON_H
#define WEAPON_H

#include <SFML/Graphics.hpp>
#include <vector>

#include <iostream>

class Weapon {
private:
	//weapon stats//
	float weaponDamage;
	float weaponeRange;//how far from player weapon can deal damege
	float weaponSpeed;//e.g how fast nullet should be 
	float weaponReload;//lvl of how fast weapon can be used again
	float weponReloadCounter;
	bool weaponFired;//if weapon is cooling down or not/if is reloaded or empyt chamber 
	

	//bullet looks//
	
	sf::Vector2f scaleOfBulletSprite;//how big it is
	sf::Texture bulletTexture;//bullet skin
	sf::Sprite bulletSkin;//drwable object of bullet
	sf::Texture weponTexture;//weapon skin
	sf::Sprite weponSkin;

	std::vector<sf::VertexArray> bullets;//vector having all bullets


	//initialization of Variabels
	void initVariabels();

	//loading texture of bulets
	void loadTextures();

public:
	
	//default constructor 
	Weapon(float weaponSpeed, float weaponReload, float weaponDamage);

	//default deconstructor 
	~Weapon();

	void aimGun(sf::Vector2f gunHolder, sf::Vector2i globalMousePosition);

	 //adding new bullet
	 void addNewBullet(sf::Vector2f gunHolder, sf::Vector2i target);
	
	 void drawBullet(sf::VertexArray& bullet);

	 //drawing all bullets
	 void renderBullets(sf::RenderTarget& window);
	 void renderWeapon(sf::RenderTarget& window);
	 //getter of bullets
	 std::vector<sf::VertexArray>& getBullets();

	 //getter of reload property higher =faster weapon cooldown
	 const float getWeaponReloadStat();

	 //is used to told if player shot from weapon or not and if it need cooldown
	 bool getWeaponWasFired()const ;
	 void setWeaponWasFired(bool statusOfWeapon);

	 const float getWeaponDamage();
};

#endif // !WEAPON_H
