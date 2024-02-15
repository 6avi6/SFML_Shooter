#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>


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
	float positonX;
	float positonY;
	
	//attributes
	int speed;
	//inicialization all of values
	void initValues();
public:


	Player();
	~Player();

	void changePosition(const float increasePositonX,const float increasePositonY);
	void render(sf::RenderTarget& target);


};

#endif // !PLAYER_H
