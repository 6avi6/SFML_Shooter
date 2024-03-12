#include "Map.h"

void Map::loadMap() {
	
	this->map_size = sf::Vector2f(1000.f, 800.f);
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

//Map construtor where numberOfMap is map that will be read
Map::Map(int numberOfMap){
	this->numberOfMap = numberOfMap;
	loadMap();
}

Map::Map(int numberOfMap, GameSettings* gameplaySettings)
{
	this->numberOfMap = numberOfMap;
	this->enemySettings = (gameplaySettings->enemy);
	loadMap();
	
}


//deconstructor of map
Map::~Map(){
	passableObjects.clear();
}

//getter of walls is use to detect collisons
std::vector <sf::VertexArray> Map::getWallObject()const {
	return wallsObjects;
}

void Map::addEnemy(float x,float y)
{
	auto newEnemy = std::make_unique<Enemy>(x, y,this->enemySettings.bulletSpeed, this->enemySettings.reloadTime, this->enemySettings.weaponDamage,this->enemySettings.enemyHealth);

	// Addig enemy to vector
	enemies.push_back(std::move(newEnemy));
}

void Map::addEnemy()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> disX(0, 800 - 32); // Adjust range according to the size of your window and enemy
	std::uniform_int_distribution<> disY(0, 600 - 64);

	bool enemyInWall;
	float randomX = 0.f;
	float randomY = 0.f;

	do {
		enemyInWall = false;
		randomX = disX(gen);
		randomY = disY(gen);
		Enemy newEnemy(randomX, randomY);
		// Check if the generated position is within any wall objects
		for (const auto& wall : wallsObjects) {
			if (wall.getBounds().intersects(newEnemy.getEnemyShape().getGlobalBounds())) {
				enemyInWall = true;
				break;
			}
		}
	} while (enemyInWall);

	// Creating a new instance of an enemy
	enemies.push_back(std::make_unique<Enemy>(randomX, randomY,this->enemySettings.bulletSpeed, this->enemySettings.reloadTime, this->enemySettings.weaponDamage, this->enemySettings.enemyHealth));			///do zmiany ¿ycie i dmg na dnyamiczne
	
}

//check if bullet hit wall if hit it will delete that bullet
void Map::checkIfWallHitted(std::vector<sf::VertexArray>& bullets)
{
	
	std::vector<int> bulletsToDelete;
	
	// Check if enemy was hit
	for (int w = 0; w < wallsObjects.size(); w++) {
		
		for (int b = 0; b < bullets.size(); b++) {
			

			//it check collison of the tip of bullet with enemy
			if (wallsObjects[w].getBounds().contains(bullets[b][0].position) ){

				// Mark enemy and bullet for deletion

				bulletsToDelete.push_back(b);
				
			}
		}
		
	}
		// Check if bullet hitted wall
		
	for (int b = 0; b < bullets.size(); b++) {


		//it check collison of the tip of bullet with enemy
		if (bullets[b][0].position.x > this->map_size.x || bullets[b][0].position.x < 0.f || bullets[b][0].position.y>this->map_size.y || bullets[b][0].position.y < 0.f) {
					
		// Mark enemy and bullet for deletion

		bulletsToDelete.push_back(b);

		}
	}

		
	// Erase bullets marked for deletion
	
	for (int i = bulletsToDelete.size() - 1; i >= 0; i--) {
		int index = bulletsToDelete[i];
		if (index < bullets.size()&& !bullets.empty()) {
			bullets.erase(bullets.begin() + index);
		}
	}
	

}


//returning 1 if target was hitted by bullets and return 0 if wasn't hitted
int Map::checkIfTargetIsHittedByBullets(sf::Sprite target, std::vector<sf::VertexArray>& bulletsShootedToTarget) {
	int howManyTimesPlayerHitted = 0;

	for (int e = 0; e < enemies.size(); e++) {
		
		std::vector<int> bulletsToDelete;

		for (int i = 0; i < bulletsShootedToTarget.size(); i++) {
			if (target.getGlobalBounds().contains(bulletsShootedToTarget[i][0].position)) {
				bulletsToDelete.push_back(i);
				howManyTimesPlayerHitted++;
			}
		}

		// Erase bullets marked for deletion (backward iteration)
		for (int i = bulletsToDelete.size() - 1; i >= 0; i--) {
			int index = bulletsToDelete[i];
			bulletsShootedToTarget.erase(bulletsShootedToTarget.begin() + index);
		}

		//checking if enemies bullet is outside of map if yes then delete that bullet
		this->checkIfWallHitted(bulletsShootedToTarget);
	}

	return howManyTimesPlayerHitted;
	
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
			enemies[e]->render(window);
			enemies[e]->weapon->renderBullets(window);
			enemies[e]->weapon->renderWeapon(window);
		}
	}
}





//method to test later on delete
void Map::createTestMap() {
	
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



	//crating new enemie
	for (int i = 0; i < this->enemySettings.numEnemies; i++) {
		this->addEnemy();
	}

	
	///
	
	position = sf::Vector2f(700.f, 500.f);

	size = sf::Vector2f(150.f, 150.f);
	

	rectangle[0].position = position;
	rectangle[1].position = position + sf::Vector2f(size.x, 0.f);

	rectangle[2].position = position + size;
	rectangle[3].position = position + sf::Vector2f(0.f, size.y);
	for (int i = 0; i < 4; ++i) {
		rectangle[i].color = color;
	}


	// Set the color with alpha value
	sf::Color blueWithAlpha(50, 0, 200, 200);
	for (int i = 0; i < 4; ++i) {
		rectangle[i].color = blueWithAlpha;
	}

	this->passableObjects.push_back(rectangle);
}
