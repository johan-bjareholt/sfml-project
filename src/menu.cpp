#include <iostream>

#include "scene.h"
#include "menu.h"
#include "game.h"
#include "graphics.h"

MenuScene::MenuScene() {
	std::cout << "Switched to MenuScene" << std::endl;
	this->drawgroup = new DrawGroup();
	sf::CircleShape* shape = new sf::CircleShape(100.f);
	shape->setFillColor(sf::Color::White);

	this->drawgroup->add(*shape);

	sf::Text* text = new sf::Text();
	// select the font
	text->setFont(getFont()); // font is a sf::Font
	// set the string to display
	text->setString("Hello world");
	// set the character size
	text->setCharacterSize(50); // in pixels, not points!
	// set the color
	text->setColor(sf::Color::White);
	// set the position
	text->setPosition(200,100);
	//text->setStyle(sf::Text::Bold | sf::Text::Underlined);
	// inside the main loop, between window.clear() and window.display()
	this->drawgroup->add(*text);
}

MenuScene::~MenuScene(){
	drawgroup->deleteAll();
	delete drawgroup;
}

void MenuScene::loop_logic(){

}

void MenuScene::loop_graphics(sf::RenderWindow& window){
	drawgroup->draw(window);
}

void MenuScene::input(sf::Event& event){
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
	if (event.type == sf::Event::EventType::KeyPressed){
		if (event.key.code == sf::Keyboard::Return){
			switchScene(new GameScene());
		}
	}
}