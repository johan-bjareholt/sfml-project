#include "menu.h"

MenuScene::MenuScene() {

}

MenuScene::~MenuScene(){
	delete shape;
}

void MenuScene::load_graphics(){
	this->shape = new sf::CircleShape(100.f);
	shape->setFillColor(sf::Color::Green);
}

void MenuScene::load_input(){

}

void MenuScene::loop_graphics(sf::RenderWindow& window){
	window.draw(*shape);
}
void MenuScene::loop_input(){

}