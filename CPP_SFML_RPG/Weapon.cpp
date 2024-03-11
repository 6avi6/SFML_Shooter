#include "Weapon.h"

#include <cmath>

#define M_PI 3.14159265358979323846

//initialization of variables
void Weapon::initVariabels(float weaponSpeed, float weaponReload) {
	this->weaponSpeed = weaponSpeed;
	this->weaponReload = weaponReload;
	this->weaponeRange = 1005.f;
	this->weaponFired = false;
	this->scaleOfBulletSprite.x = 4.f;
	this->scaleOfBulletSprite.y = 4.f;
	this->weponReloadCounter = 0;
}

void Weapon::loadTextures()
{
	
	//reading texture
	if (!this->weponTexture.loadFromFile("Assets/Textures/Wepon/Bullet/bulletSample.png"))
	{
		std::cout << "ERROR::WEAPON::loadTextures()::'couldn't load texture of bullet'" << std::endl;
	}
	else {
		//setting sprite skin
		this->bulletSkin.setTexture(weponTexture);
		
		//resizeing bullet
		this->bulletSkin.scale(this->scaleOfBulletSprite.x, this->scaleOfBulletSprite.y);

		//Setting center of bullet 
		this->bulletSkin.setOrigin(this->bulletSkin.getLocalBounds().width / 2, 0.f);
	}
}

//Weapon constructor
Weapon::Weapon(float weaponSpeed,float weaponReload){
	this->initVariabels(weaponSpeed, weaponReload);
	this->loadTextures();
	

}

//default deconstructor
Weapon::~Weapon()
{
	

}


//method adding new bullets
void Weapon::addNewBullet(sf::Vector2f gunHolder, sf::Vector2i globalMousePosition) {
    if(!this->weaponFired)
	{// Creating a line (VertexArray)
		this->weaponFired = true;
		sf::VertexArray bullet(sf::Lines, 2);
		bullet[0].position = sf::Vector2f(gunHolder.x + 16.f, gunHolder.y + 32.f); // Player position
		// Calculating the difference between mouse position and player position
		sf::Vector2f diff = sf::Vector2f(globalMousePosition) - bullet[0].position;

		// Normalizing the difference vector
		float length = std::sqrt(diff.x * diff.x + diff.y * diff.y);//pythagorean theorem x^2 +y^2=z^2
		sf::Vector2f direction = diff / length;

		// Setting the end position of the line to a fixed length of 100 units
		bullet[0].position = bullet[0].position + direction * 15.f;
		bullet[1].position = bullet[0].position + direction * weaponeRange;

		//bullet[0].color = sf::Color::Blue;
		//bullet[1].color = sf::Color::Red;

		// Adding the line to the bullets container
		bullets.push_back(bullet); }
}

//method drawing bullets and deleating old ones
void Weapon::renderBullets(sf::RenderTarget& window) {

	//Checkin if weapon cooldown effect worked
	if(this->weaponFired == true)
	this->weponReloadCounter += (weaponReload / (60*10 ));
	
	if (this->weponReloadCounter >= 1 && this->weaponFired == true) {
		this->weaponFired = false;
		this->weponReloadCounter = 0;
	}

	if(bullets.size()>200)
		bullets.erase(bullets.begin());
	if (!bullets.empty()) {
		for (int i=0; i < bullets.size(); i++) {
			
			this->drawBullet(bullets[i]);
				
			window.draw(bulletSkin);

		}
	}
	
}

//drawing all bullets
void Weapon::drawBullet(sf::VertexArray& bullet){
	// Calculating the difference between mouse position and player position
	sf::Vector2f diff = bullet[1].position - bullet[0].position;

	// Normalizing the difference vector
	float length = std::sqrt(diff.x * diff.x + diff.y * diff.y);//pythagorean theorem x^2 +y^2=z^2
	sf::Vector2f direction = diff / length;

	// Setting the end position of the line
	//there its moving from a player depending of weaponSpeed
	bullet[0].position += direction * this->weaponSpeed;



	
	bulletSkin.setPosition(bullet[0].position);


	
	// Calculate rotation angle in radians
	float rotation = std::atan2(direction.y, direction.x) * 180 / M_PI;

	//setting proper rotation to angle beetwen player and x axis
	bulletSkin.setRotation(rotation + 90.f);

	
}


//getter of bullets
std::vector<sf::VertexArray> & Weapon::getBullets() {
	return bullets;
}

 //getter of reload property higher =faster weapon cooldown
const float Weapon::getWeaponReloadStat() {

	 return this->weaponReload;
 }

 //is used to told if player shot from weapon or not and if it need cooldown
bool Weapon:: getWeaponWasFired() const{

	 return this->weaponFired;
 }
void Weapon::setWeaponWasFired(bool statusOfWeapon) {

	 this->weaponFired = statusOfWeapon;
}