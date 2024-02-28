#ifndef WEAPON_H
#define WEAPON_H

#include <SFML/Graphics.hpp>
#include <vector>

#include <iostream>

class Weapon {
private:
	//weapon stats
	
	float weaponeRange;
	
	//weapon skins
	sf::Texture weponTexture;
	
	
	//initialization of Variabels
	void initVariabels();

	//loading texture of bulets
	void loadTextures();
public:
	//vector having all bullets
	std::vector<sf::VertexArray> bullets;

	sf::Sprite bulletSkin;

	bool weaponFired;
	float weaponSpeed;
	float weaponReload;
	void drawBullet(sf::VertexArray& bullet);

	//adding new bullet
	void addNewBullet(sf::Vector2i positonOfPlayer, sf::Vector2i globalMousePosition);
	
	//drawing bullets
	void renderBullets(sf::RenderTarget& window);

	//geter of bullets
	std::vector<sf::VertexArray>& getBullets();
	Weapon();

};

#endif // !WEAPON_H
