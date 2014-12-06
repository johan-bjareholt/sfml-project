#ifndef GAME_H
#define GAME_H

#include "scene.h"
#include <SFML/Graphics.hpp>

class GameScene: public Scene {
private:
	sf::CircleShape* planet;
	sf::CircleShape* ship;
	sf::Vertex* vertex;
	sf::View* view;
	double zoom;
public:
	GameScene();
	~GameScene();
	void loop_graphics(sf::RenderWindow&);
	void loop_logic();
	void input(sf::Event&);
};

#endif