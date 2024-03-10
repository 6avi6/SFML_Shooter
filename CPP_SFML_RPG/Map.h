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

#include "GameSettings.h"
class Map {
private:

	//description fields of the current map//

	int numberOfMap;//number of map identyfication that will be load
	sf::Vector2f map_size;//sizes of map
	std::vector <sf::VertexArray> wallsObjects;//vector with all non passable by player objects
	std::vector <sf::Sprite> passableObjects;//vector with all passable by player objects


	//method that will be read map from json file !!TO DO!!
	void loadMap();

	//vector saving all enemies
	//it s neccesery to use smart pointers or pointers to add enemie on heap
	//if enemies were stored in:
	//std::vector<Enemy>
	//it will create white squre problem
	
	EnemySettings enemySettings;

	//method to test later on delete
	void createTestMap();
public:
	
	std::vector<std::unique_ptr<Enemy>> enemies;
	//Map construtor where numberOfMap is map that will be read
	Map(int numberOfMap=0);
	Map(int numberOfMap, GameSettings* gameplaySettings);

	//deconstructor of map
	~Map();
	
	//getter of all non passable objects
	std::vector <sf::VertexArray> getWallObject()const;


	//enemy handling//
	//adding new enemy where x and y are spawn cordinates
	void addEnemy(float x, float y);

	//adding new enemy with random cordinates
	void addEnemy();

	//check if bullet hit wall if hit it will delet that bullet
	void checkIfWallHitted(std::vector<sf::VertexArray>& bullets);
	
	int checkIfTargetIsHittedByBullets(sf::Sprite target, std::vector<sf::VertexArray>& bullets);

	//drawing current map
	//firstly it drawing passable objects later on walls that can't player can go through
	void drawMap(sf::RenderTarget& window);
};


#endif // !MAP_H
