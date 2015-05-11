#include <iostream>

#include "scene.h"
#include "menu.h"
#include "game.h"
#include "graphics.h"

MenuScene::MenuScene() {
	std::cout << "Switched to MenuScene" << std::endl;
	this->drawgroup = new DrawGroup();

	sf::Text* text = new sf::Text();
	// select the font
	text->setFont(getFont());
	text->setString("Spacesim-2d");
	text->setCharacterSize(50);
	text->setColor(sf::Color::White);
	text->setPosition(500,200);
	//text->setStyle(sf::Text::Bold | sf::Text::Underlined);
	this->drawgroup->add(*text);

	sf::Text* text2 = new sf::Text();
	text2->setFont(getFont());
	text2->setString("Press Enter to start");
	text2->setCharacterSize(30);
	text2->setColor(sf::Color::White);
	text2->setPosition(500,270);
	this->drawgroup->add(*text2);
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
	if (event.type == sf::Event::EventType::KeyPressed){
		if (event.key.code == sf::Keyboard::Return){
			switchScene(new GameScene());
		}
	}
}
