#include <iostream>
#include <cmath>

#include "scene.h"
#include "menu.h"
#include "game.h"
#include "drawgroup.h"
#include "graphics.h"
#include "main.h"

GameScene::GameScene() {
	std::cout << "Switched to GameScene" << std::endl;
	CelestialObject* planet = new CelestialObject(10000.f);
	planet->setFillColor(sf::Color(0,255,0));
	this->bodies.add(*planet);

	CelestialObject* moon = new CelestialObject(1000.f);
	moon->setFillColor(sf::Color(175,175,175));
	moon->setPosition(0,30000);
	moon->accelerate(-1500.0f, 0.0f);
	this->bodies.add(*moon);

	this->ship = new CelestialObject(10.f);
	ship->setFillColor(sf::Color::Yellow);
	ship->setPosition(0,12000);
	this->bodies.add(*ship);

	this->vertex = new sf::Vertex(sf::Vector2f(10, 50), sf::Color::Red, sf::Vector2f(100, 100));

	zoom = 3;


	text = new sf::Text();
	// select the font
	text->setFont(getFont()); // font is a sf::Font
	// set the string to displayide a computer which can distort the analog signals. How bad is your onboard audio? If its good I'd skip the DAC and
	text->setString("Hello world");
	// set the character size
	text->setCharacterSize(24); // in pixels, not points!
	// set the color
	text->setColor(sf::Color::White);
	// inside the main loop, between window.clear() and window.display()
	this->gui.add(*text);

	this->guiview = new sf::View(sf::FloatRect(0,0,1280,720));
	this->gameview = new sf::View();
}

GameScene::~GameScene(){
	this->bodies.deleteAll();
	this->gui.deleteAll();
	delete vertex;
	delete gameview;
	delete guiview;
}

void GameScene::loop_graphics(sf::RenderWindow& window){
	window.setView(*gameview);
	bodies.draw(window);
	window.setView(*guiview);
	gui.draw(window);
}
void GameScene::loop_logic(){
	// Spaceship WASD movement
	float speed = 100;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->ship->accelerate(speed,0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->ship->accelerate(-speed,0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->ship->accelerate(0.f,speed);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->ship->accelerate(0.f,-speed);

	// Iterate over all celestial objects
	for (int co=0; co<bodies.size(); co++){
		CelestialObject* selectedObject = dynamic_cast<CelestialObject*>(bodies[co]);
		float m1 = selectedObject->getMass();

		// Calculate force on/from all other celestial objects
		for (int co2=co+1; co2<bodies.size(); co2++){
			if (co2 != co){
				CelestialObject* targetObject = dynamic_cast<CelestialObject*>(bodies[co2]);
				float m2 = targetObject->getMass();

				// Calculate force between the celestial objects
				float G = 9.8;
				float r = selectedObject->getDistance(*targetObject);
				float force = G*((m1*m2)/(r*r));
				if (selectedObject->getCollision(*targetObject)){
					selectedObject->onCollision(*targetObject);
				}

				else {
					// Calculate angle between objects
					float forceAngle = selectedObject->getAngle(*targetObject);

					// Totalspeed
					float selectedSpeed = force/selectedObject->getMass();
					//float selectedSpeed = force*targetObject->getMass();
					float targetSpeed = force/targetObject->getMass();
					//float targetSpeed = force*selectedObject->getMass();

					//std::cout << force << std::endl;

					// Calculate gravitational force
					float accselectedX = std::cos(forceAngle)*selectedSpeed*deltaTime.asSeconds();
					float accselectedY = std::sin(forceAngle)*selectedSpeed*deltaTime.asSeconds();
					float acctargetX = std::cos(forceAngle+3.14)*targetSpeed*deltaTime.asSeconds();
					float acctargetY = std::sin(forceAngle+3.14)*targetSpeed*deltaTime.asSeconds();

					// Apply gravitational force
					selectedObject->accelerate(accselectedX, accselectedY);
					targetObject->accelerate(acctargetX, acctargetY);

					//if (co==0 && co2==1)
					//std::cout << forceAngle << ":" << acctargetX << "," << acctargetY << std::endl;
					//std::cout << "cos: " << std::cos(forceAngle) << " sin:" << std::sin(forceAngle) << std::endl;
				}
			}
		}
		// Apply force
		selectedObject->move(selectedObject->getSpeed()*deltaTime.asSeconds());
	}

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
		Mouse
	*/
	// Zoom in/out
	if (event.type == sf::Event::EventType::MouseWheelMoved){
		if (event.mouseWheel.delta < 0)
			zoom *= -event.mouseWheel.delta*0.95;
		else
			zoom *= event.mouseWheel.delta*1.05;
	}
	// Mouse interaction with game view
	if (event.type == sf::Event::EventType::MouseMoved){
		// Get mouse pos
		sf::Vector2i mousepos = sf::Mouse::getPosition(*getWindow());
		// Convert mouse pos to world pos
		sf::Vector2f mouseposworld =
			getWindow()->mapPixelToCoords(mousepos, *this->gameview);
		// Check each planet for
		for (int co=0; co<bodies.size(); co++){
			CelestialObject* targetObject = dynamicma_cast<CelestialObject*>(bodies[co]);
			if (targetObject->getCollision(mouseposworld)){
				std::cout << "Mouse is pointing at a planet!" << std::endl;
			}
		}
	}
}
