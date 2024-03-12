#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include <SFML/Graphics.hpp>

class HealthBar {
private:

	sf::RectangleShape HealthBarStripe;
	sf::Vector2f *positonOfEntity;
	float primaryHealthOfEntity;
	sf::Color colorOfBar;
	void initHealthBar();
public:
	HealthBar(sf::Vector2f* positonOfEntity, float primaryHealthOfEntity, sf::Color colorOfBar);

	void render(sf::RenderTarget& window, float currentHealth);
};

#endif // !HEALTHBAR_H
