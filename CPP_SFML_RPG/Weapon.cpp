#include "Weapon.h"

//initialization of variables
void Weapon::initVariabels() {
	weaponSpeed = 5;
	
}

//Weapon constructor
Weapon::Weapon(){
	initVariabels();

}

//method adding new bullets
void Weapon::addNewBullet(sf::Vector2i positonOfPlayer, sf::Vector2i globalMousePosition) {
	sf::VertexArray bullet(sf::Lines, 2);
	bullet[0].position = sf::Vector2f(positonOfPlayer.x+16.f, positonOfPlayer.y+32.f);//git
	bullet[1].position = sf::Vector2f(globalMousePosition.x, globalMousePosition.y);
	bullet[0].color = sf::Color::Blue;
	bullet[1].color = sf::Color::Red;
	bullets.push_back(bullet);

}

//method drawing bullets and deleating old ones
void Weapon::renderBullets(sf::RenderTarget& window) {
	if(bullets.size()>40)
		bullets.erase(bullets.begin());
	if (!bullets.empty()) {
		for (const auto& line : bullets) {
			window.draw(line);
		}
	}
}

//getter of bullets
std::vector<sf::VertexArray> Weapon::getBullets() {
	return bullets;
}
