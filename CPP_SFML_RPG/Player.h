#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <iostream>

class Player {
private:
	//image of primary looks of player
	sf::Texture skinOfPlayer;

	//drawable object/shape of player
	sf::Sprite playerEntity;
	
	sf::RectangleShape shape;
	//scale of enlargement
	float width;
	float height;

	//position on map
	
	sf::Vector2i positonOfPlayer;
	//attributes
	int speed;
	//inicialization all of values
	void initValues(const sf::Vector2i windowSize);
public:


	
	//constructors of player

	//default spawns player at 0,0
	Player();
	//for attribute it need window size to spawn player on center of map
	Player(sf::Vector2i windowSize);

	//deconstructor
	~Player();

	void changePosition(const float increasePositonX,const float increasePositonY, sf::Vector2i windowSize, std::vector<sf::VertexArray> currentMap);
	void setPosition(float x,float y);
	void render(sf::RenderTarget& target);
	sf::Vector2i getPlayerPostion();

	const sf::RectangleShape& getShape() const;
	const bool checkCollision();

	void collisonDetection(const  sf::RenderTarget* window);

};

#endif // !PLAYER_H
