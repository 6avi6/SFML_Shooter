#include "Map.h"

void Map::loadMap() {
	
	this->map_size = sf::Vector2f(800.f, 600.f);
	this->createTestMap();
	

	//
	//here will be section that will serialaize maps
	//

	//adding objects to passable vector
	



	//Error massage if object didn't load
	if (passableObjects.empty()) {
		std::cout << "ERROR::MAP::drawMap()::'not a single passable object has been loaded error may occur'" << std::endl;
	}
	if (wallsObjects.empty()) {
		std::cout << "ERROR::MAP::drawMap()::'not a single wall object has been loaded error may occur'" << std::endl;
	}
}

//Map construtor
Map::Map(int numberOfMap){
	this->numberOfMap = numberOfMap;
	loadMap();
}


//deconstructor of map
Map::~Map(){
	passableObjects.clear();
}

//drawing current map
//firstly it drawing passable objects later on walls that can't player can go through
void Map::drawMap(sf::RenderTarget& window) {
	
	

	//Drawing passable objects
	if (!passableObjects.empty()) {
		for (const auto& object : this->passableObjects) {
			window.draw(object);
		}
	}
	
	//Drawing walls objects
	if (!wallsObjects.empty()) {
		for (const auto& object : this->wallsObjects) {
			window.draw(object);
		}
	}
	
	//Drawing enemies Sprite
	if (!enemies.empty()) {
		for (int e = 0; e < enemies.size(); e++) {
			window.draw(enemies[e]->enemyEntity);
		}
	}
}

//getter of walls is use to detect collisons
std::vector <sf::VertexArray> Map::getWallObject() {
	return wallsObjects;
}

void Map::addEnemy(float x,float y)
{
	auto newEnemy = std::make_unique<Enemy>(x, y);

	// Addig enemy to vector
	enemies.push_back(std::move(newEnemy));
}

void Map::addEnemy()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	int min = 0;

	//max_x & max_y need to be change to be dynamic
	int max_x = 800-32;//32=width of enemie
	int max_y = 600-64;//64=heigt of enemie
	std::uniform_int_distribution<> disX(min, max_x);
	std::uniform_int_distribution<> disY(min, max_y);
	int randomX = disX(gen);
	int randomY = disY(gen);

	//Creating new instance of enemy
	auto newEnemy = std::make_unique<Enemy>(randomX, randomY);

	// Adding enemy to vector 
	enemies.push_back(std::move(newEnemy));
	
}

void Map::checkIfEnemyHitted(std::vector<sf::VertexArray>& bullets)
{
	//Checkin if enemy was hitted

	std::vector<int> enemiesToDelete;
	std::vector<int> bulletsToDelete;
	bool hitted = false;
	// Check if enemy was hit
	for (int e = 0; e < enemies.size(); e++) {
		for (int b = 0; b < bullets.size(); b++) {
			if (enemies[e]->getEnemyShape().getGlobalBounds().intersects(bullets[b].getBounds())) {
				std::cout << "Hit"<<std::endl;
				
				// Mark enemy and bullet for deletion
				enemiesToDelete.push_back(e);
				bulletsToDelete.push_back(b);
				hitted = true;
			}
		}
	}

	// Erase enemies marked for deletion
	for (int i = enemiesToDelete.size() - 1; i >= 0; i--) {
		enemies.erase(enemies.begin() + enemiesToDelete[i]);
	}

	// Erase bullets marked for deletion
	for (int i = bulletsToDelete.size() - 1; i >= 0; i--) {
		//bullets.erase(bullets.begin() + bulletsToDelete[i]);
		bullets.clear();
		
	}

	//If mob is dead it spawns new
	if(hitted){ this->addEnemy(); }
		
	
}

void Map::createTestMap() {
	//crating new enemie
	this->addEnemy();
	// Define the rectangle's position, size, and color
	sf::Vector2f position(100.f, 100.f);
	sf::Vector2f size(200.f, 100.f);
	sf::Color color = sf::Color::Red;
	sf::VertexArray rectangle(sf::Quads, 4);
	
	rectangle[0].position = position;
	rectangle[1].position = position + sf::Vector2f(size.x, 0.f);
	rectangle[2].position = position + size;
	rectangle[3].position = position + sf::Vector2f(0.f, size.y);
	for (int i = 0; i < 4; ++i) {
		rectangle[i].color = color;
	}
	wallsObjects.push_back(rectangle);

	position = sf::Vector2f(600.f, 100.f);
	size = sf::Vector2f(200.f, 300.f);
	color = sf::Color::Green;

	rectangle[0].position = position;
	rectangle[1].position = position + sf::Vector2f(size.x, 0.f);
	rectangle[2].position = position + size;
	rectangle[3].position = position + sf::Vector2f(0.f, size.y);
	for (int i = 0; i < 4; ++i) {
		rectangle[i].color = color;
	}
	//
	//here will be section that will serialaize maps
	//

	//adding objects to passable vector
	wallsObjects.push_back(rectangle);

	position = sf::Vector2f(200.f, 450.f);
	size = sf::Vector2f(150.f, 150.f);
	color = sf::Color::Blue;

	rectangle[0].position = position;
	rectangle[1].position = position + sf::Vector2f(size.x, 0.f);
	rectangle[2].position = position + size;
	rectangle[3].position = position + sf::Vector2f(0.f, size.y);
	for (int i = 0; i < 4; ++i) {
		rectangle[i].color = color;
	}
	//
	//here will be section that will serialaize maps
	//

	//adding objects to passable vector
	wallsObjects.push_back(rectangle);

	position = sf::Vector2f(250.f, 300.f);
	
	size = sf::Vector2f(150.f, 150.f);
	color = sf::Color(255, 0, 255, 200);

	rectangle[0].position = position;
	rectangle[1].position = position + sf::Vector2f(size.x, 0.f);
	size = sf::Vector2f(100.f, 100.f);
	rectangle[2].position = position + size;
	rectangle[3].position = position + sf::Vector2f(0.f, size.y);
	for (int i = 0; i < 4; ++i) {
		rectangle[i].color = color;
	}
	
	//
	//here will be section that will serialaize maps
	//

	//adding objects to passable vector
	wallsObjects.push_back(rectangle);
}