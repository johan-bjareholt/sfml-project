#include <cmath>
#include <iostream>

#include "celestialobject.h"
#include "main.h"

CelestialObject::CelestialObject(float radius, float mass, std::string name) : sf::CircleShape(radius, radius){
	this->name = name;
	this->setOrigin(radius, radius);
	this->velocity = sf::Vector2f(0.0f,0.0f);
	if (mass <= 0)
		this->setMass(radius*radius*PI*100);
	else
		this->setMass(mass);
}

void CelestialObject::accelerate(float x, float y){
	this->velocity.x += x;
	this->velocity.y += y;
}

void CelestialObject::setAcceleration(float x, float y){
	this->velocity.x = x;
	this->velocity.y = y;
}

std::string CelestialObject::getName(){
	return this->name;
}

sf::Vector2f& CelestialObject::getVelocity(){
	return this->velocity;
}

float CelestialObject::getSpeed(){
	return sqrt(pow(this->velocity.x,2)+pow(this->velocity.y,2));
}

float CelestialObject::getMass(){
	return this->mass;
}

void CelestialObject::setMass(float mass){
	this->mass = mass;
}

sf::Vector2f CelestialObject::getDistanceVector(const sf::Vector2f& point){
	sf::Vector2f distance(0,0);
	distance.x = (this->getPosition().x - point.x);
	distance.y = (this->getPosition().y - point.y);
	return distance;
}

sf::Vector2f CelestialObject::getDistanceVector(sf::CircleShape& otherObject){
	return this->getDistanceVector(otherObject.getPosition());
}

float CelestialObject::getDistance(const sf::Vector2f& point){
	sf::Vector2f distance = this->getDistanceVector(point);
	return sqrt(pow(distance.x,2)+pow(distance.y,2));
}

float CelestialObject::getDistance(sf::CircleShape& otherObject){
	return this->getDistance(this->getDistanceVector(otherObject));
}

bool CelestialObject::getCollision(sf::Vector2f& point){
	sf::Vector2f position = this->getPosition();
	sf::Vector2f distance(position.x-point.x, position.y-point.y);
	float hypo = sqrt(pow(distance.x,2)+pow(distance.y,2));
	std::cout << distance.x << "," << distance.y << "=" << hypo << std::endl;
	if (hypo < this->getRadius())
		return true;
	else
		return false;
}

bool CelestialObject::getCollision(sf::CircleShape& other){
	sf::Vector2f distance = this->getDistanceVector(other);
	float rsum = this->getRadius() + other.getRadius();
	float hypolen = sqrt(pow(distance.x,2)+pow(distance.y,2));
	if (hypolen < rsum)
		return true;
	else
		return false;
}

void CelestialObject::onCollision(CelestialObject& other){
	/*
		Implement impulse algorithm
	*/

	this->velocity.x *= -1;
	this->velocity.y *= -1;
	other.velocity.x *= -1;
	other.velocity.y *= -1;
	//this->move(-this->velocity.x*deltaTime.asSeconds(), -this->velocity.y*deltaTime.asSeconds());

	/*
	float movementforce1 = sqrt(pow(this->velocity.x,2)*pow(this->velocity.y,2))*this->getMass();
	float movementforce2 = sqrt(pow(other.velocity.x,2)*pow(other.velocity.y,2))*other.getMass();

	float movementangle1 = std::atan2(this->velocity.x, this->velocity.y);
	float movementangle2 = std::atan2(other.velocity.x, other.velocity.y);
	*/

	/*
	if (movementforce1 > movementforce2){
		other.velocity = this->velocity;
	}
	else {
		this->velocity = other.velocity;
	}
	*/



	std::cout << "Planets are colliding!" << std::endl;
}

float CelestialObject::getAngle(CelestialObject& otherObject){
	sf::Vector2f distance = this->getDistanceVector(otherObject);
	float angle=std::atan2(distance.y,distance.x);
	return angle;
}
