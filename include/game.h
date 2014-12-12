#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "scene.h"
#include "celestialobject.h"

class GameScene: public Scene {
private:
	CelestialObject* planet;
	CelestialObject* moon;
	CelestialObject* ship;
	std::vector<CelestialObject*> celestialObjects;
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