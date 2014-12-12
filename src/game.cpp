#include <iostream>
#include <cmath>

#include "scene.h"
#include "menu.h"
#include "game.h"

GameScene::GameScene() {
	std::cout << "Switched to GameScene" << std::endl;
	this->planet = new CelestialObject(10000.f, 5000);
	this->planet->setFillColor(sf::Color(0,255,0));
	this->planet->setPosition(-10000,0);

	this->moon = new CelestialObject(500.f, 250);
	this->moon->setFillColor(sf::Color(175,175,175));
	this->moon->setPosition(-500,-5000);
	this->moon->accelerate(0.0f, 0.0f);

	this->ship = new CelestialObject(20.f);
	this->ship->setFillColor(sf::Color::Yellow);
	this->ship->setPosition(0,0);

	celestialObjects.push_back(ship);
	celestialObjects.push_back(planet);
	//celestialObjects.push_back(moon);

	this->vertex = new sf::Vertex(sf::Vector2f(10, 50), sf::Color::Red, sf::Vector2f(100, 100));

	zoom = 3;
}

GameScene::~GameScene(){
	delete planet;
	delete moon;
	delete ship;
	delete vertex;
	delete view;
}

void GameScene::loop_graphics(sf::RenderWindow& window){
	window.setView(*view);
	window.draw(*planet);
	window.draw(*moon);
	window.draw(*ship);
}
void GameScene::loop_logic(){
	float speed = 0.5;
	// Spaceship movements
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		this->ship->accelerate(speed,0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		this->ship->accelerate(-speed,0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		this->ship->accelerate(0.f,-speed);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		this->ship->accelerate(0.f,speed);

	const float PI = std::asin(-1);
	for (int co=0; co<celestialObjects.size(); co++){
		CelestialObject* selectedObject = celestialObjects[co];
		float m1 = selectedObject->getRadius();

		// Calculate applied force by all other celestial objects
		for (int co2=co+1; co2<celestialObjects.size(); co2++){
			CelestialObject* targetObject = celestialObjects[co2];
			float m2 = targetObject->getRadius();
			// Calculate total force
			float G = 0.5;
			float r = m1+m2;
			float force = G*((m1*m2)/r);
			// Get x and y distance between objects
			sf::Vector2f distance = selectedObject->getDistance(*targetObject);
			std::cout << distance.x << "," << distance.y << std::endl;
			// Calculate angle between objects
			float forceAngle = selectedObject->getAngle(*targetObject);
			double moveX = std::cos(forceAngle)*force/targetObject->getRadius();
			double moveY = std::sin(forceAngle)*force/targetObject->getRadius();
			selectedObject->accelerate(moveX, moveY);
			targetObject->accelerate(-moveX, -moveY);
			std::cout << forceAngle<<":"<< moveX << "," << moveY << std::endl;
		}
		selectedObject->move(selectedObject->getAcceleration());
	}

	this->ship->move(this->ship->getAcceleration());

	// Calculate new camera position and size
	int cameraW = 350*zoom;
	int cameraH = 200*zoom;
	int cameraX = this->ship->getPosition().x-(cameraW/2);
	int cameraY = this->ship->getPosition().y-(cameraH/2);
	// Update camera view
	this->view = new sf::View(sf::FloatRect(cameraX, cameraY, cameraW, cameraH));
}

void GameScene::input(sf::Event& event){
	if (event.type == sf::Event::EventType::KeyReleased)
		if (event.key.code == sf::Keyboard::Escape)
			switchScene(new MenuScene());
	if (event.type == sf::Event::EventType::MouseWheelMoved){
		if (event.mouseWheel.delta < 0)
			zoom *= -event.mouseWheel.delta*0.95;
		else
			zoom *= event.mouseWheel.delta*1.05;
	}
}