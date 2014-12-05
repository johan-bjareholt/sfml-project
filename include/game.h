#ifndef GAME_H
#define GAME_H

#include "scene.h"
#include <SFML/Graphics.hpp>

class GameScene: public Scene {
private:
	sf::CircleShape* shape;
public:
	GameScene();
	~GameScene();
	void loop_graphics(sf::RenderWindow&);
	void loop_logic();
	void input(sf::Event&);
};

#endif