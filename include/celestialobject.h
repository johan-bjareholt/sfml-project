#ifndef CELESTIALOBJECT_H
#define CELESTIALOBJECT_H

#include <SFML/Graphics.hpp>

class CelestialObject : public sf::CircleShape {
private:
	sf::Vector2f acceleration;
public:
	CelestialObject(float radius, unsigned int pointCount=30);
	void accelerate(float,float);
	void setAcceleration(float,float);
	sf::Vector2f& getAcceleration();

	sf::Vector2f getDistance(sf::CircleShape&);
	float getAngle(sf::CircleShape&);
};

#endif