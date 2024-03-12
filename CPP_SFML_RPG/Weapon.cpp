#include "Weapon.h"

#include <cmath>

#define M_PI 3.14159265358979323846

//initialization of variables
void Weapon::initVariabels() {
	this->weaponeRange = 1005.f;
	this->weaponFired = false;
	this->scaleOfBulletSprite.x = 4.f;
	this->scaleOfBulletSprite.y = 4.f;
	this->weponReloadCounter = 0;
}

void Weapon::loadTextures()
{
	
	//reading texture
	if (!this->bulletTexture.loadFromFile("Assets/Textures/Wepon/Bullet/bulletSample.png"))
	{
		std::cout << "ERROR::WEAPON::loadTextures()::'couldn't load texture of bullet'" << std::endl;
	}
	else {
		//setting sprite skin
		this->bulletSkin.setTexture(bulletTexture);
		
		//resizeing bullet
		this->bulletSkin.scale(this->scaleOfBulletSprite.x, this->scaleOfBulletSprite.y);

		//Setting center of bullet 
		this->bulletSkin.setOrigin(this->bulletSkin.getLocalBounds().width / 2, 0.f);
	}
	//reading texture
	if (!this->weponTexture.loadFromFile("Assets/Textures/Wepon/Weapon/weponTexture.png"))
	{
		std::cout << "ERROR::WEAPON::loadTextures()::'couldn't load texture of weapon'" << std::endl;
	}
	else {
		//setting sprite skin
		this->weponSkin.setTexture(weponTexture);

		//resizeing bullet
		this->weponSkin.scale(1.f, 1.5f);
		this->weponSkin.setOrigin(16.f, 8.f );

		//Setting center of bullet 
		
	}
}

//Weapon constructor
Weapon::Weapon(float weaponSpeed,float weaponReload, float weaponDamage):
	weaponDamage(weaponDamage), weaponSpeed(weaponSpeed), weaponReload(weaponReload)
{
	this->initVariabels();
	this->loadTextures();
	

}

//default deconstructor
Weapon::~Weapon()
{
	

}
void Weapon::aimGun(sf::Vector2f gunHolder, sf::Vector2i globalMousePosition) {
// Calculate angle between player and mouse
float angle = atan2(globalMousePosition.y - gunHolder.y-32.f , globalMousePosition.x - gunHolder.x-16.f );
angle *= 180.f / static_cast<float>(M_PI); // Convert radians to degrees

// Rotate gun sprite to face mouse direction
this->weponSkin.setRotation(angle);

// Set gun position to player position
this->weponSkin.setPosition(gunHolder.x+16.f, gunHolder.y+ 32.f);

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
		bullet[0].position = bullet[0].position + direction * 64.f;
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

void Weapon::renderWeapon(sf::RenderTarget& window)
{
	window.draw(this->weponSkin);
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

const float Weapon::getWeaponDamage()
{
	return this->weaponDamage;
}
