#include <iostream>

#include "game.h"

GameScene::GameScene() {
	std::cout << "Switched to GameScene" << std::endl;
	this->shape = new sf::CircleShape(100.f);
	shape->setFillColor(sf::Color::Red);
}

GameScene::~GameScene(){
	delete shape;
}

void GameScene::loop_graphics(sf::RenderWindow& window){
	window.draw(*shape);
}
void GameScene::loop_logic(){

}

void GameScene::input(sf::Event& event){

}