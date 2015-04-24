#ifndef CELESTIALOBJECT_H
#define CELESTIALOBJECT_H

#include <SFML/Graphics.hpp>
#include <string>

class CelestialObject : public sf::CircleShape {
private:
	std::string name;
	sf::Vector2f speed;
	float mass;
public:
	CelestialObject(float radius, float mass=0, std::string name="Unnamed");

	void accelerate(float,float);
	void setAcceleration(float,float);
	sf::Vector2f& getSpeed();

	std::string getName();
	float getMass();
	void setMass(float);

	sf::Vector2f getDistanceVector(const sf::Vector2f& point); // DistanceVector for points
	sf::Vector2f getDistanceVector(sf::CircleShape&); // DistanceVector for CircleShapes
	float getDistance(const sf::Vector2f& point); // Distance for points
	float getDistance(sf::CircleShape&); // Distance for CircleShapes
	bool getCollision(sf::Vector2f& point); // Collision check for points
	bool getCollision(sf::CircleShape&); // Collision check for CircleShape
	void onCollision(CelestialObject& other);
	float getAngle(sf::CircleShape&);
};

#endif
