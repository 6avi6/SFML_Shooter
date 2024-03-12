#include "HealthBar.h"

void HealthBar::initHealthBar()
{	
	this->HealthBarStripe.setSize(sf::Vector2f(75.f, 7.f));
	this->HealthBarStripe.setOrigin(75.f/2, 0.f);
	this->HealthBarStripe.setFillColor(this->colorOfBar);

}

HealthBar::HealthBar(sf::Vector2f* positonOfEntity, float primaryHealthOfEntity, sf::Color colorOfBar):
	positonOfEntity(positonOfEntity), primaryHealthOfEntity(primaryHealthOfEntity), colorOfBar(colorOfBar)
{
	this->initHealthBar();
}

void HealthBar::render(sf::RenderTarget& window,float currentHealth)
{	

	this->HealthBarStripe.setSize(sf::Vector2f(75.f* (currentHealth/(this->primaryHealthOfEntity)), 7.f));
	
	this->HealthBarStripe.setPosition(sf::Vector2f((positonOfEntity->x+16.f), positonOfEntity->y - 25.f));
	window.draw(this->HealthBarStripe);
}
