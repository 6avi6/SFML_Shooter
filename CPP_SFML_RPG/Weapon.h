#ifndef WEAPON_H
#define WEAPON_H

#include <SFML/Graphics.hpp>
#include <vector>

#include <iostream>

class Weapon {
private:
	//weapon stats//
	
	float weaponeRange;//how far from player weapon can deal damege
	float weaponSpeed;//e.g how fast nullet should be 
	float weaponReload;//lvl of how fast weapon can be used again
	bool weaponFired;//if weapon is cooling down or not/if is reloaded or empyt chamber 
	

	//bullet looks//
	
	sf::Vector2f scaleOfBulletSprite;//how big it is
	sf::Texture weponTexture;//weapon skins
	sf::Sprite bulletSkin;//drwable object of bullet


	std::vector<sf::VertexArray> bullets;//vector having all bullets


	//initialization of Variabels
	void initVariabels(float weaponSpeed, float weaponReload);

	//loading texture of bulets
	void loadTextures();

public:
	
	//default constructor 
	Weapon(float weaponSpeed, float weaponReload);

	//default deconstructor 
	~Weapon();


	 //adding new bullet
	 void addNewBullet(sf::Vector2f gunHolder, sf::Vector2i target);
	
	 void drawBullet(sf::VertexArray& bullet);

	 //drawing all bullets
	 void renderBullets(sf::RenderTarget& window);

	 //getter of bullets
	 std::vector<sf::VertexArray>& getBullets();

	 //getter of reload property higher =faster weapon cooldown
	 const float getWeaponReloadStat();

	 //is used to told if player shot from weapon or not and if it need cooldown
	 bool getWeaponWasFired()const ;
	 void setWeaponWasFired(bool statusOfWeapon);
};

#endif // !WEAPON_H
