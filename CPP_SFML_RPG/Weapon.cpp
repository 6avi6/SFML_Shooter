#include "Weapon.h"

#include <cmath>

#define M_PI 3.14159265358979323846

//initialization of variables
void Weapon::initVariabels() {
	weaponSpeed = 5;
	weaponReload = 45;
	weaponeRange = 1005.f;
	this->weaponFired = false;
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
		this->bulletSkin.scale(4.f, 4.f);
		this->bulletSkin.setOrigin(this->bulletSkin.getLocalBounds().width / 2, 0.f);
	}
}

//Weapon constructor
Weapon::Weapon(){
	this->loadTextures();
	this->initVariabels();

}

//method adding new bullets
void Weapon::addNewBullet(sf::Vector2i positonOfPlayer, sf::Vector2i globalMousePosition) {
    // Creating a line (VertexArray)
    sf::VertexArray bullet(sf::Lines, 2);
    bullet[0].position = sf::Vector2f(positonOfPlayer.x + 16.f, positonOfPlayer.y + 32.f); // Player position

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
    bullets.push_back(bullet);
}

//method drawing bullets and deleating old ones
void Weapon::renderBullets(sf::RenderTarget& window) {



	if(bullets.size()>200)
		bullets.erase(bullets.begin());
	if (!bullets.empty()) {
		for (int i=0; i < bullets.size(); i++) {
			
			this->drawBullet(bullets[i]);
			if (!(bullets[i][0].position.x > 800.f || bullets[i][0].position.x < 0.f || bullets[i][0].position.y>600.f || bullets[i][0].position.y < 0.f)) {

			window.draw(bulletSkin);
			//window.draw(bullets[i]);
			}
			else {
			bullets.erase(bullets.begin() + i);
			i--;
		}
			
		}
	}
	//window.draw(bulletSkin);
}

void Weapon::drawBullet(sf::VertexArray& bullet){
	// Calculating the difference between mouse position and player position
	sf::Vector2f diff = bullet[1].position - bullet[0].position;

	// Normalizing the difference vector
	float length = std::sqrt(diff.x * diff.x + diff.y * diff.y);//pythagorean theorem x^2 +y^2=z^2
	sf::Vector2f direction = diff / length;

	// Setting the end position of the line to a fixed length of 100 units
	bullet[0].position += direction * this->weaponSpeed;




	bulletSkin.setPosition(bullet[0].position);


	//sf::Vector2f direction = bullet[1].position - bulletSkin.getPosition();
	// Calculate rotation angle in radians
	float rotation = std::atan2(direction.y, direction.x) * 180 / M_PI;

	bulletSkin.setRotation(rotation + 90.f);

}


//getter of bullets
std::vector<sf::VertexArray> & Weapon::getBullets() {
	return bullets;
}
