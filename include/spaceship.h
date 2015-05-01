#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <string>

#include "celestialobject.h"

class Spaceship : public CelestialObject {
private:
    float angle;
    float lastAngle;
    sf::Texture texture;
    sf::Sprite sprite;
public:
    Spaceship(std::string name);
    void draw(sf::RenderWindow&);
    void rotate(float);
    void throttle(float);
    float getMovementAngle();
};

#endif
