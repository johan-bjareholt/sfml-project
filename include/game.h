#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "scene.h"
#include "drawgroup.h"
#include "celestialobject.h"

class GameScene: public Scene {
private:
	DrawGroup bodies;
	DrawGroup gui;
	CelestialObject* ship;
	sf::Vertex* vertex;
	sf::Text* text;
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