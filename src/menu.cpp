#include <iostream>

#include "scene.h"
#include "menu.h"
#include "game.h"

MenuScene::MenuScene() {
	std::cout << "Switched to MenuScene" << std::endl;
	this->shape = new sf::CircleShape(100.f);
	shape->setFillColor(sf::Color::Green);
}

MenuScene::~MenuScene(){
	delete shape;
}

void MenuScene::loop_logic(){

}

void MenuScene::loop_graphics(sf::RenderWindow& window){
	window.draw(*shape);
}

void MenuScene::input(sf::Event& event){
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		switchScene(new GameScene());
}