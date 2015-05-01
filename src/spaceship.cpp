#include "spaceship.h"
#include "graphics.h"


Spaceship::Spaceship(std::string name) : CelestialObject(10.0f, 0, name){
    this->setFillColor(sf::Color(0,0,0,0));
    //this->setFillColor(sf::Color::Yellow);

    this->sprite = sf::Sprite();
    this->texture.loadFromFile("./assets/png/spaceship.png");

    sprite.setTexture(texture);
    sprite.scale(sf::Vector2f(0.2f,0.2f));
    sprite.setOrigin(50,50);

    this->angle = 0;
    this->lastAngle = angle;
}

void Spaceship::draw(sf::RenderWindow& window){
    if (this->angle != this->lastAngle){
        this->sprite.setRotation(-(angle/3.14)*180+270);
        this->lastAngle = angle;
    }
    this->sprite.setPosition(this->getPosition());
    window.draw(this->sprite);
}

void Spaceship::rotate(float amount){
    this->angle += amount;
}

void Spaceship::throttle(float amount){
    this->accelerate(-std::cos(angle)*amount,
                     std::sin(angle)*amount);
}

float Spaceship::getMovementAngle(){
    return this->angle;
}
