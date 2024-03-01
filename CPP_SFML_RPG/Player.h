#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Player {
private:
	//player look//
	
	
	sf::Texture skinOfPlayer;//image of primary looks of player
	sf::Sprite playerEntity;//drawable object/shape of player
	sf::Vector2f scaleOfPlayer;//scale of enlargement

	
	sf::Vector2f positonOfPlayer;//position on map


	//attributes//
	int speed;//spedd of the player


	//inicialization all of values
	void initValues(const sf::Vector2i windowSize);

public:

	//default spawns player at 0,0
	Player();

	//for attribute it need window size to spawn player on center of map
	Player(sf::Vector2i windowSize);

	//defualt deconstructor
	~Player();

	//method changing players positon on map//

	//TO DO: 
	//collison handling if player spawns in objects
	//collison object other than rectangles

	//change player postion in some direction
	//detecion collison & handling player with walls 
	void changePosition(const float increasePositonX,const float increasePositonY, sf::Vector2i windowSize, const std::vector<sf::VertexArray> currentMap);

	//get player postion
	const sf::Vector2f getPlayerPostion() const;

	//get shape of player to detect collison
	const sf::Sprite& getShape() const;

	//setting player postion on some point in map
	void setPosition(float xCoordinate, float yCoordinate);

	//rendering player on map//

	//method rendering player entity in targeted window
	void render(sf::RenderTarget& window);

};

#endif // !PLAYER_H
