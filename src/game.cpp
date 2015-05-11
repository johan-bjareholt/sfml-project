#include <iostream>
#include <sstream>
#include <cmath>

#include "scene.h"
#include "menu.h"
#include "game.h"
#include "drawgroup.h"
#include "graphics.h"
#include "main.h"

GameScene::GameScene() {
	std::cout << "Switched to GameScene" << std::endl;
	Planet* planet = new Planet(10000.f, 0, "Earth");
	planet->setFillColor(sf::Color(0,255,0));
	this->bodies.add(*planet);

	Planet* moon = new Planet(1000.f, 0, "Moon");
	moon->setFillColor(sf::Color(175,175,175));
	moon->setPosition(0,30000);
	moon->accelerate(-1500.0f, 0.0f);
	this->bodies.add(*moon);

	this->ship = new Spaceship("Spaceship1");
	ship->setPosition(0,12000);
	this->bodies.add(*ship);

	this->vertex = new sf::Vertex(sf::Vector2f(10, 50), sf::Color::Red, sf::Vector2f(100, 100));

	zoom = 3;


	infoText = new sf::Text("", getFont(), 24);
	infoText2 = new sf::Text("", getFont(), 24);
	infoText2->setPosition(0,30);
	// set the color
	infoText->setColor(sf::Color::White);
	infoText2->setColor(sf::Color::White);

	// Navball
	this->navball = new Navball(this->ship);

	// inside the main loop, between window.clear() and window.display()
	this->gui.add(*infoText);
	this->gui.add(*infoText2);

	// Initialize other variables
	this->selectedEntity = nullptr;

	// Views
	this->guiview = new sf::View(sf::FloatRect(0,0,1280,720));
	this->gameview = new sf::View();
}

GameScene::~GameScene(){
	this->bodies.deleteAll();
	this->gui.deleteAll();
	delete vertex;
	delete navball;
	delete gameview;
	delete guiview;
}

void GameScene::loop_graphics(sf::RenderWindow& window){
	// Set game view
	window.setView(*gameview);
	// Draw game elements
	bodies.draw(window);
	this->ship->draw(window);

	// Set default view
	window.setView(*guiview);
	// Draw GUI
	gui.draw(window);
	navball->draw(window, selectedEntity);
}

void GameScene::loop_logic(){
	// Spaceship WASD movement
	float speed = 100;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->ship->rotate(3.14*deltaTime.asSeconds());
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->ship->rotate(-3.14*deltaTime.asSeconds());
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->ship->throttle(speed);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->ship->throttle(-speed);

	// Iterate over all celestial objects
	for (int co=0; co<bodies.size(); co++){
		// Selected CelestialObject
		CelestialObject* selectedObject = dynamic_cast<CelestialObject*>(bodies[co]);
		float m1 = selectedObject->getMass();

		// Calculate force on/from all other celestial objects
		for (int co2=co+1; co2<bodies.size(); co2++){
			if (co2 != co){
				// Other CelestialObject to interfere with the selected one
				CelestialObject* targetObject = dynamic_cast<CelestialObject*>(bodies[co2]);
				float m2 = targetObject->getMass();

				// Calculate force between the celestial objects
				float G = 6.673;
				float r = selectedObject->getDistance(*targetObject);
				float force = G*((m1*m2)/(r*r));

				// Calculate angle between objects
				float forceAngle = selectedObject->getAngle(*targetObject);

				// Totalspeed
				float selectedSpeed = force/selectedObject->getMass();
				float targetSpeed = force/targetObject->getMass();

				// Calculate gravitational force
				float accselectedX = std::cos(forceAngle)*selectedSpeed*deltaTime.asSeconds();
				float accselectedY = std::sin(forceAngle)*selectedSpeed*deltaTime.asSeconds();
				float acctargetX = std::cos(forceAngle+3.14)*targetSpeed*deltaTime.asSeconds();
				float acctargetY = std::sin(forceAngle+3.14)*targetSpeed*deltaTime.asSeconds();

				// Apply gravitational force
				selectedObject->accelerate(accselectedX, accselectedY);
				targetObject->accelerate(acctargetX, acctargetY);

				// Collision handling
				if (selectedObject->getCollision(*targetObject)){
					selectedObject->onCollision(*targetObject);
				}
			}
		}
		// Apply force
		selectedObject->move(selectedObject->getVelocity()*deltaTime.asSeconds());
	}

	/*
		GUI
	*/
	// InfoText
	if (this->selectedEntity != nullptr){
		std::stringstream ss;
		ss	<< "X:" << this->selectedEntity->getPosition().x
			<< ", Y:" << this->selectedEntity->getPosition().y
			<< std::endl
			<< "dX:" << this->selectedEntity->getVelocity().x
			<< ", dY:" << this->selectedEntity->getVelocity().y;
		this->infoText2->setString(ss.str());
	}

	/*
		Views
	*/

	// Calculate new camera position and size
	int cameraW = 350*zoom;
	int cameraH = -200*zoom;
	double cameraX = this->ship->getPosition().x-(cameraW/2)+this->ship->getRadius();
	double cameraY = this->ship->getPosition().y-(cameraH/2)+this->ship->getRadius();

	// Update gameview
	this->gameview->reset(sf::FloatRect(cameraX, cameraY, cameraW, cameraH));
}

void GameScene::input(sf::Event& event){
	// Escape
	if (event.type == sf::Event::EventType::KeyReleased)
		if (event.key.code == sf::Keyboard::Escape)
			switchScene(new MenuScene());

	/*
		Mouse Movement
	*/
	// Mouse interaction with game view
	if (event.type == sf::Event::EventType::MouseButtonReleased){
		// Get mouse pos
		sf::Vector2i mousepos = sf::Mouse::getPosition(*getWindow());
		// Convert mouse pos to world pos
		sf::Vector2f mouseposworld =
			getWindow()->mapPixelToCoords(mousepos, *this->gameview);
		// Check each planet for
		for (int co=0; co<bodies.size(); co++){
			CelestialObject* targetObject = dynamic_cast<CelestialObject*>(bodies[co]);
			if (targetObject->getCollision(mouseposworld)){
				std::cout << "Mouse is pointing at a planet!" << std::endl;
				this->infoText->setString(targetObject->getName());
				this->selectedEntity = targetObject;
			}
		}
	}

	/*
		MouseWheel
	*/
	// Zoom in/out
	if (event.type == sf::Event::EventType::MouseWheelMoved){
		if (event.mouseWheel.delta < 0)
			zoom *= -event.mouseWheel.delta*0.95;
		else
			zoom *= event.mouseWheel.delta*1.05;
	}
}
