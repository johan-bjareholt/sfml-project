#ifndef MENU_H
#define MENU_H

#include "scene.h"
#include <SFML/Graphics.hpp>

class MenuScene: public Scene {
private:
	sf::CircleShape* shape;
public:
	MenuScene();
	~MenuScene();
	void loop_graphics(sf::RenderWindow&);
	void loop_logic();
	void input(sf::Event&);
};

#endif