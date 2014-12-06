#include "celestialobject.h"

CelestialObject::CelestialObject(float radius, unsigned int pointCount) : sf::CircleShape(radius, pointCount){
	this->acceleration = sf::Vector2<float>(0.0f,0.0f);
}

void CelestialObject::accelerate(float x, float y){
	this->acceleration.x += x;
	this->acceleration.y += y;
}

void CelestialObject::setAcceleration(float x, float y){
	this->acceleration.x = x;
	this->acceleration.y = y;
}

sf::Vector2<float>& CelestialObject::getAcceleration(){
	return this->acceleration;
}