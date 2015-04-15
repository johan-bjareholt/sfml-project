#include <iostream>
#include <cmath>

#include "scene.h"
#include "menu.h"
#include "game.h"
#include "drawgroup.h"
#include "graphics.h"

GameScene::GameScene() {
	std::cout << "Switched to GameScene" << std::endl;
	CelestialObject* planet = new CelestialObject(10000.f);
	planet->setFillColor(sf::Color(0,255,0));
	planet->setPosition(-10000,0);
	this->bodies.add(*planet);

	CelestialObject* moon = new CelestialObject(1000.f);
	moon->setFillColor(sf::Color(175,175,175));
	moon->setPosition(50000,-50000);
	moon->accelerate(-100.0f, 0.0f);
	this->bodies.add(*moon);

	this->ship = new CelestialObject(50.f);
	ship->setFillColor(sf::Color::Yellow);
	ship->setPosition(0,0);
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
	float speed = 5;
	// Spaceship movements
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		this->ship->accelerate(speed,0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		this->ship->accelerate(-speed,0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		this->ship->accelerate(0.f,-speed);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		this->ship->accelerate(0.f,speed);

	for (int co=0; co<bodies.size(); co++){
		CelestialObject* selectedObject = dynamic_cast<CelestialObject*>(bodies[co]);
		float m1 = selectedObject->getRadius();

		// Calculate applied force by all other celestial objects
		for (int co2=0; co2<bodies.size(); co2++){
			if (co2 != co){
				CelestialObject* targetObject = dynamic_cast<CelestialObject*>(bodies[co2]);
				float m2 = targetObject->getRadius();
				// Calculate total force
				float G = 0.0003;
				float r = selectedObject->getRadius()+targetObject->getRadius();
				float force = G*((m1*m2)/(r*r));
				// Get x and y distance between objects
				sf::Vector2f distance = selectedObject->getDistance(*targetObject);
				std::cout << distance.x << "," << distance.y << std::endl;
				// Chech for collision
				double hypo = sqrt(pow(distance.x,2)+pow(distance.y,2));
				if (hypo<r)
					std::cout << "Planets are colliding!" << std::endl;

				else {
					// Calculate angle between objects
					float forceAngle = selectedObject->getAngle(*targetObject);
					// Calculate gravitational force
					double moveselectedX = std::cos(forceAngle)*force*targetObject->getRadius();
					double moveselectedY = std::sin(forceAngle)*force*targetObject->getRadius();
					double movetargetX = std::cos(forceAngle)*force*selectedObject->getRadius();
					double movetargetY = std::sin(forceAngle)*force*selectedObject->getRadius();
					// Apply gravitational force
					selectedObject->accelerate(-moveselectedX, moveselectedY);
					targetObject->accelerate(movetargetX, -movetargetY);
					std::cout << forceAngle << ":" << movetargetX << "," << movetargetY << std::endl;
					std::cout << "cos: " << std::cos(forceAngle) << " sin:" << std::sin(forceAngle) << std::endl;
				}
			}
		}
		selectedObject->move(selectedObject->getAcceleration());
	}

	// Calculate new camera position and size
	int cameraW = 350*zoom;
	int cameraH = 200*zoom;
	double cameraX = this->ship->getPosition().x-(cameraW/2)+this->ship->getRadius();
	double cameraY = this->ship->getPosition().y-(cameraH/2)+this->ship->getRadius();
	// Update camera view
	//sf::View* oldview = this->gameview;
	this->gameview->reset(sf::FloatRect(cameraX, cameraY, cameraW, cameraH));
	//this->gameview = new sf::View(sf::FloatRect(cameraX, cameraY, cameraW, cameraH));
	//delete oldview;
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
	if (event.type == sf::Event::EventType::MouseMoved){
		//sf::Vector2f mousepos = getWindow()->ConvertCoords(getWindow()->GetInput().GetMouseX(), getWindow()->GetInput().GetMouseY());
		//sf::Event::MouseMoveEvent move = event.mouseMove;
		//std::cout << mousepos.x << "," << mousepos.y << std::endl;
	}
}
