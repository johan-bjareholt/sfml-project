#include <iostream>

#include "scene.h"
#include "menu.h"
#include "game.h"

GameScene::GameScene() {
	std::cout << "Switched to GameScene" << std::endl;
	this->planet = new sf::CircleShape(10000.f);
	this->planet->setFillColor(sf::Color::Green);
	this->planet->setPosition(-10000,0);

	this->ship = new sf::CircleShape(20.f);
	this->ship->setFillColor(sf::Color::Yellow);
	this->ship->setPosition(0,0);

	this->vertex = new sf::Vertex(sf::Vector2f(10, 50), sf::Color::Red, sf::Vector2f(100, 100));

	zoom = 3;
}

GameScene::~GameScene(){
	delete planet;
	delete ship;
	delete vertex;
	delete view;
}

void GameScene::loop_graphics(sf::RenderWindow& window){
	window.setView(*view);
	window.draw(*planet);
	window.draw(*ship);
}
void GameScene::loop_logic(){
	int speed = 30;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		this->ship->move(speed,0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		this->ship->move(-speed,0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		this->ship->move(0,-speed);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		this->ship->move(0,speed);

	int cameraW = 350*zoom;
	int cameraH = 200*zoom;
	int cameraX = this->ship->getPosition().x-(cameraW/2);
	int cameraY = this->ship->getPosition().y-(cameraH/2);
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