#include "graphics.h"
#include "navball.h"

Navball::Navball(Spaceship* spaceship) {
    this->spaceship = spaceship;
    sf::RenderWindow* window = getWindow();

    sf::Vector2u pos = window->getSize();
    int radius = pos.x/20;
    pos.x /= 2;
    pos.y -= radius+10;

    this->background = sf::CircleShape(radius, 50);
    this->background.setOrigin(radius, radius);
    this->background.setPosition(pos.x, pos.y);
    this->background.setFillColor(sf::Color::Blue);

    this->frame = sf::CircleShape(radius, 50);
    this->frame.setOrigin(radius, radius);
    this->frame.setPosition(pos.x, pos.y);
    this->frame.setFillColor(sf::Color(0,0,0,0));
    this->frame.setOutlineThickness(10.f);
    this->frame.setOutlineColor(sf::Color(125,125,125));

    this->directionPointer.setSize(sf::Vector2f(4,radius+10));
    this->directionPointer.setPosition(pos.x, pos.y);
    this->directionPointer.setOrigin(2,0);

    this->distanceText = sf::Text("",getFont(), 30);
    this->speedText = sf::Text("", getFont(), 30);
    this->distanceText.setPosition(pos.x+radius, pos.y);
    this->speedText.setPosition(pos.x-radius-60, pos.y);
}

void Navball::draw(sf::RenderWindow& window, CelestialObject* selectedObject){
    this->directionPointer.setRotation((this->spaceship->getAngle()/3.14)*180+90);

    window.draw(this->frame);
    window.draw(this->directionPointer);
    window.draw(this->background);

    if (selectedObject != nullptr){
        this->distanceText.setString(std::to_string(selectedObject->getDistance(*this->spaceship)));
    }
    float speed = sqrt(pow(this->spaceship->getSpeed().x,2)+pow(this->spaceship->getSpeed().y,2));
    this->speedText.setString(std::to_string(speed));
}
