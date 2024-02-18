#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>



class Player {
private:
	//image of primary looks of player
	sf::Texture skinOfPlayer;

	//drawable object/shape of player
	sf::Sprite playerEntity;
	
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

	void changePosition(const float increasePositonX,const float increasePositonY, sf::Vector2i windowSize);
	void render(sf::RenderTarget& target);
	sf::Vector2i getPlayerPostion();

};

#endif // !PLAYER_H
