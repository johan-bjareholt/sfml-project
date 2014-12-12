#include <cmath>

const float PI = 3.14159265359f;

#include "celestialobject.h"

CelestialObject::CelestialObject(float radius, unsigned int pointCount) : sf::CircleShape(radius, pointCount){
	this->acceleration = sf::Vector2f(0.0f,0.0f);
}

void CelestialObject::accelerate(float x, float y){
	this->acceleration.x += x;
	this->acceleration.y += y;
}

void CelestialObject::setAcceleration(float x, float y){
	this->acceleration.x = x;
	this->acceleration.y = y;
}

sf::Vector2f CelestialObject::getDistance(sf::CircleShape& otherObject){
	sf::Vector2f distance(0,0);
	distance.x = (this->getPosition().x + this->getRadius())-
				 (otherObject.getPosition().x + otherObject.getRadius());
	distance.y = (this->getPosition().y + this->getRadius())-
				 (otherObject.getPosition().y + otherObject.getRadius());
	return distance;
}

float CelestialObject::getAngle(sf::CircleShape& otherObject){
	sf::Vector2f distance = this->getDistance(otherObject);
	float angle=std::atan(distance.x/distance.y);
	return angle;
}

sf::Vector2f& CelestialObject::getAcceleration(){
	return this->acceleration;
}