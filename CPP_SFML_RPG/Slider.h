#ifndef SLIDER_H
#define	SLIDER_H

#include <SFML/Graphics.hpp>

class Slider {
private:
    sf::RectangleShape track;
    sf::RectangleShape handle;

    std::string nameOfSlider;
    sf::Font font;
    sf::Text nameTagWithValue;
    void initFont();
    float minValue;
    float maxValue;
    float value;
    bool isDragging;
   
public:
    Slider(std::string nameOfSlider,float minValue, float maxValue, float initialValue, sf::Vector2f position, sf::Vector2f size);

    void draw(sf::RenderWindow& window);
    void update(sf::RenderWindow& window, sf::Event event);
    float getValue() const;
};


#endif // !
