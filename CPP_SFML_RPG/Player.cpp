#include "Player.h"

//initialization of player fields
void Player::initValues(sf::Vector2i windowSize=sf::Vector2i(0.f, 0.f))
{
	//player sizes
	this->scaleOfPlayer.x = 2.f;
	this->scaleOfPlayer.y = 2.f;

	//position on map default center
	 this->positonOfPlayer.x= windowSize.x / 2;
	 this->positonOfPlayer.y = windowSize.y / 2;

	//reading texture
	if (!this->skinOfPlayer.loadFromFile("Assets/Textures/playerTexture.png"))
	{
		std::cout << "ERROR::PLAYER::initValues()::'loading texture of player'" << std::endl;
	}
	else{
		this->playerEntity.setTexture(this->skinOfPlayer);
		
		//resizeing player
		this->playerEntity.scale(this->scaleOfPlayer.x, this->scaleOfPlayer.y);

	}
	
	//attrbiutes
	this->speed = 7;
	this->playerHealthBar = new HealthBar(&(this->positonOfPlayer), this->playerHealth, sf::Color(7, 173, 10));
	
	
}

//default constructor that spawns player on 0;0
Player::Player() 
{
	this->initValues();
}
//creating new weapon
void Player::initWeapon(float weaponSpeed = 10.f, float weaponReload = 45.f,float weaponDamage=25.f) {
	this->weapon = new Weapon(weaponSpeed, weaponReload, weaponDamage);
}

const float Player::getPlayerHealth()
{
	return this->playerHealth;
}

void Player::playerReactionToDamge(float enemyWeaponDamage)
{
	this->playerHealth -= enemyWeaponDamage;
}

Player::Player(const sf::Vector2i windowSize,int playerSpeed, float weaponSpeed, float weaponReload, float weaponDamage, float playerHealth):
 playerHealth(playerHealth)
{
	this->initValues();
	this->initWeapon(weaponSpeed, weaponReload, weaponDamage);
	this->speed=playerSpeed;
	
	
}


//constructor that spawns player on center of screen
Player::Player(const sf::Vector2i windowSize) {
	this->initValues(windowSize);
	this->initWeapon();
}

//default deconstructor
Player::~Player() 
{

}



//change player postion in some direction
	//detecion collison & handling player with walls 
void Player::changePosition(const float increasePositonX,const float increasePositonY, sf::Vector2i windowSize,const std::vector<sf::VertexArray> currentMap)
{
	
//checking collision with map wallsObjects
	
	//setting position to new
	this->playerEntity.setPosition(this->positonOfPlayer.x += (increasePositonX * this->speed), this->positonOfPlayer.y += (increasePositonY * this->speed));
	for (const auto& wall : currentMap) {
		
		//making correction of position if objects includes in another objects
		while (this->getShape().getGlobalBounds().intersects(wall.getBounds())) {
			this->playerEntity.setPosition(this->positonOfPlayer.x -= (increasePositonX ), this->positonOfPlayer.y -= (increasePositonY));
		}
		

	}
	
	//Collison handling with window
	if (this->positonOfPlayer.x > windowSize.x)
		this->positonOfPlayer.x = 0.f;
	if (this->positonOfPlayer.y > windowSize.y)
		this->positonOfPlayer.y = 0.f;
	if (this->positonOfPlayer.x < 0.f)
		this->positonOfPlayer.x = windowSize.x;
	if (this->positonOfPlayer.y < 0.f)
		this->positonOfPlayer.y = windowSize.y;
		
}


//get player postion
const sf::Vector2f Player::getPlayerPostion()const {
	return this->positonOfPlayer;
}


//get shape of player to detect collison
const sf::Sprite& Player::getShape()const
{	
	return this->playerEntity;
}

//setting player postion on some point in map
void Player::setPosition(float xCoordinate, float yCoordinate) {
	
	this->positonOfPlayer= sf::Vector2f(xCoordinate, yCoordinate);
}

//method rendering player entity in targeted window
void Player::render(sf::RenderTarget& window)
{
	this->playerEntity.setPosition(this->positonOfPlayer.x, this->positonOfPlayer.y);
	playerHealthBar->render(window,this->playerHealth);
	window.draw(this->playerEntity);
}


