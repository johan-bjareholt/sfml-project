#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "scene.h"
#include "drawgroup.h"

#include "celestialobject.h"
#include "planet.h"
#include "spaceship.h"
#include "navball.h"

class GameScene: public Scene {
private:
	// Game
	sf::View* gameview;
	double zoom;
	DrawGroup bodies;
	Spaceship* ship;
	sf::Vertex* vertex;
	// Gui
	sf::View* guiview;
	DrawGroup gui;
	sf::Text* infoText;
	sf::Text* infoText2;
	CelestialObject* selectedEntity;
	Navball* navball;
public:
	GameScene();
	~GameScene();
	void loop_graphics(sf::RenderWindow&);
	void loop_logic();
	void input(sf::Event&);
};

#endif
