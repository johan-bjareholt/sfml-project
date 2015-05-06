#include "graphics.h"
#include "navball.h"

#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>

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

    this->movementPointer.setSize(sf::Vector2f(4,radius+10));
    this->movementPointer.setPosition(pos.x, pos.y);
    this->movementPointer.setOrigin(2,0);
    this->movementPointer.setFillColor(sf::Color::Yellow);

    this->destinationPointer.setSize(sf::Vector2f(4,radius+10));
    this->destinationPointer.setPosition(pos.x, pos.y);
    this->destinationPointer.setOrigin(2,0);

    this->distanceText = sf::Text("",getFont(), 20);
    this->speedText = sf::Text("", getFont(), 20);
    this->distanceText.setPosition(pos.x+radius, pos.y+radius-20);
    this->speedText.setPosition(pos.x-radius-60, pos.y+radius-20);
}

void Navball::draw(sf::RenderWindow& window, CelestialObject* selectedObject){
    float directionAngle = (this->spaceship->getMovementAngle()/3.14)*180+90;
    this->directionPointer.setRotation(directionAngle);

    float movementAngle = std::atan2(this->spaceship->getVelocity().x,
                                     this->spaceship->getVelocity().y);
    this->movementPointer.setRotation((movementAngle/3.14)*180+180);

    if (selectedObject != nullptr){
        float destinationAngle = this->spaceship->getAngle(*selectedObject);
        this->destinationPointer.setRotation((-destinationAngle/3.14)*180+90);
        std::cout << destinationAngle*180+90 << std::endl;
        this->destinationPointer.setFillColor(sf::Color::Blue);
    }
    else {
        this->destinationPointer.setFillColor(sf::Color(125,125,125));
    }


    window.draw(this->frame);
    window.draw(this->directionPointer);
    window.draw(this->movementPointer);
    window.draw(this->destinationPointer);
    window.draw(this->background);

    std::stringstream ss;

    if (selectedObject != nullptr){
        ss  << std::fixed << std::setprecision(1)
            << (selectedObject->getDistance(*this->spaceship)
                -this->spaceship->getRadius() - selectedObject->getRadius());
        this->distanceText.setString(ss.str());
        ss.clear();
        //this->distanceText.setString(std::to_string(selectedObject->getDistance(*this->spaceship)));
    }
    window.draw(this->distanceText);
    float speed = this->spaceship->getSpeed();
    ss << std::fixed << std::setprecision(1) << speed;
    this->speedText.setString(ss.str());
    //this->speedText.setString(std::to_string(speed));
    window.draw(this->speedText);
}
