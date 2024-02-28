#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>

//enemies
#include "Enemy.h"

//audio will be added later
//#include <SFML/Audio.hpp>

#include <vector>


//random number generator
#include <random>

#include<iostream>

class Map {
private:
	//sizes of map
	sf::Vector2f map_size;

	//vector with all non passable by player objects
	std::vector <sf::VertexArray> wallsObjects;

	//vector with all passable by player objects
	std::vector <sf::Sprite> passableObjects;

	//number of map identyfication that will be load
	int numberOfMap;

	//method that will be read map from json file
	void loadMap();

	//method to test later on delete
	void createTestMap();

	//vector saving all enemies
	//it s neccesery to use smart pointers or pointers to add enemie on heap
	//if enemies were stored in:
	//std::vector<Enemy>
	//it will create white squre problem
	


public:
	std::vector<std::unique_ptr<Enemy>> enemies;

	Map(int numberOfMap=0);
	~Map();
	
	//method drawing a map on screeon where window is a window were it will be generated
	void drawMap(sf::RenderTarget& window);

	//getter of all non passable objects
	std::vector <sf::VertexArray> getWallObject();

	//adding new enemy where x and y are spawn cordinates
	void addEnemy(float x, float y);

	//adding new enemy with random cordinates
	void addEnemy();
	int checkIfEnemyHitted(std::vector<sf::VertexArray>& bullets);
	void checkIfWallHitted(std::vector<sf::VertexArray>& bullets);
};


#endif // !MAP_H
