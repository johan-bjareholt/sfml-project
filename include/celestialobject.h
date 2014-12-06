#ifndef CELESTIALOBJECT_H
#define CELESTIALOBJECT_H

#include <SFML/Graphics.hpp>

class CelestialObject : public sf::CircleShape {
private:
	sf::Vector2<float> acceleration;
public:
	CelestialObject(float radius, unsigned int pointCount=30);
	void accelerate(float,float);
	void setAcceleration(float,float);
	sf::Vector2<float>& getAcceleration();
};

#endif