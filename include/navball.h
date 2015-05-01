#ifndef NAVBALL_H
#define NAVBALL_H

#include "spaceship.h"

class Navball {
private:
    Spaceship* spaceship;
    sf::CircleShape background;
    sf::CircleShape frame;
    sf::RectangleShape directionPointer;
    sf::RectangleShape movementPointer;
    sf::RectangleShape destinationPointer;
    sf::Text distanceText;
    sf::Text speedText;
public:
    Navball(Spaceship* spaceship);
    void draw(sf::RenderWindow&, CelestialObject*);
};

#endif
