#ifndef WEAPON_H
#define WEAPON_H

#include <SFML/Graphics.hpp>
#include <vector>

class Weapon {
private:
	//weapon stats
	int weaponSpeed;
	
	

public:
	//vector having all bullets
	std::vector<sf::VertexArray> bullets;

	//initialization of Variabels
	void initVariabels();

	//adding new bullet
	void addNewBullet(sf::Vector2i positonOfPlayer, sf::Vector2i globalMousePosition);
	
	//drawing bullets
	void renderBullets(sf::RenderTarget& window);

	//geter of bullets
	std::vector<sf::VertexArray>& getBullets();
	Weapon();

};

#endif // !WEAPON_H
