#ifndef CELESTIALOBJECT_H
#define CELESTIALOBJECT_H

#include <SFML/Graphics.hpp>

class CelestialObject : public sf::CircleShape {
private:
	sf::Vector2f acceleration;
	double mass;
public:
	CelestialObject(float radius, float mass=0);

	void accelerate(float,float);
	void setAcceleration(float,float);
	sf::Vector2f& getAcceleration();

	double getMass();
	void setMass(double);

	sf::Vector2f getDistance(sf::CircleShape&);
	float getAngle(sf::CircleShape&);
};

#endif