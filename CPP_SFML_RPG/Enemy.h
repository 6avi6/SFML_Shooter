#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class Enemy {
private:
	
	//scale of enlargement
	float width;
	float height;

	sf::Texture enemyTexture;
	
	void initEnemy();

public:
	sf::Sprite enemyEntity;
	Enemy();
	Enemy(float x, float y);
	~Enemy();
	void render(sf::RenderTarget& target);
	const sf::Sprite getEnemyShape() ;
	

};

#endif // !ENEMY_H


