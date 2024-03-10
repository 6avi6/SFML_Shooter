#include "Slider.h"
#include <iostream>

void Slider::initFont()
{
    if (!this->font.loadFromFile("Assets/Fonts/Silkscreen/slkscr.ttf"))
    {
        std::cout << "ERROR::Slider::initFont()::'couldn't load font slkscr.ttf" << std::endl;
    }
    else {
        
        //setting font of text with scores
        this->nameTagWithValue.setFont(this->font);
        //setting defualt text communicat with scores
        
        this->nameTagWithValue.setString(nameOfSlider+": " + std::to_string(this->getValue()));
        //setting positon of score points
        this->nameTagWithValue.setPosition(track.getPosition().x, track.getPosition().y - 30.f);
        this->nameTagWithValue.setScale(0.5f, 0.5f);
    }
}

Slider::Slider(std::string nameOfSlider,float minValue, float maxValue, float initialValue, sf::Vector2f position, sf::Vector2f size) :
    nameOfSlider(nameOfSlider), minValue(minValue), maxValue(maxValue), value(initialValue), isDragging(false) {
    // Track setup
    this->track.setSize(size);
    this->track.setPosition(position);
    this->track.setFillColor(sf::Color::White);

    // Handle setup
    this->handle.setSize(sf::Vector2f(20, size.y));
    this->handle.setOrigin(this->handle.getSize().x / 2, this->handle.getSize().y / 2);
    this->handle.setPosition(position.x + (this->value - minValue) / (maxValue - minValue) * size.x, position.y);
    this->handle.setFillColor(sf::Color::Blue);
    this->initFont();
}

void Slider::draw(sf::RenderWindow& window) {
    window.draw(this->track);
    window.draw(this->handle);
    window.draw(this->nameTagWithValue);
}

void Slider::update(sf::RenderWindow& window, sf::Event event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

;        if (handle.getGlobalBounds().contains(mousePos)) {
            isDragging = true;
        }
    }
    else if (event.type == sf::Event::MouseButtonReleased) {
        isDragging = false;

    }
    else if (event.type == sf::Event::MouseMoved && isDragging) {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
        float newX = std::min(std::max(mousePos.x, track.getPosition().x), track.getPosition().x + track.getSize().x);
        handle.setPosition(newX, handle.getPosition().y);
        value = minValue + (maxValue - minValue) * ((newX - track.getPosition().x) / track.getSize().x);
        this->nameTagWithValue.setString(nameOfSlider + ": " + std::to_string(this->getValue()));
    }
}

float Slider::getValue() const {
    return value;
}
