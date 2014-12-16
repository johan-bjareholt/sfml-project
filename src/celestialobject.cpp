#include <cmath>

const float PI = std::asin(-1);

#include "celestialobject.h"

CelestialObject::CelestialObject(float radius, float mass) : sf::CircleShape(radius, radius/2){
	this->acceleration = sf::Vector2f(0.0f,0.0f);
	if (mass <= 0)
		this->mass = pow(radius,2)*PI;
	else
		this->mass = mass;
}

void CelestialObject::accelerate(float x, float y){
	this->acceleration.x += x;
	this->acceleration.y += y;
}

void CelestialObject::setAcceleration(float x, float y){
	this->acceleration.x = x;
	this->acceleration.y = y;
}


sf::Vector2f& CelestialObject::getAcceleration(){
	return this->acceleration;
}

double CelestialObject::getMass(){
	return this->mass;
}

void CelestialObject::setMass(double mass){
	this->mass = mass;
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
	float angle=std::atan2(-distance.y,distance.x);
	return angle;
}