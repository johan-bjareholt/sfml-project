#ifndef SCENE_H
#define SCENE_H

#include <SFML/Graphics.hpp>

class Scene {
public:
	virtual void loop_graphics(sf::RenderWindow&)=0;
	virtual void loop_logic()=0;
	virtual void input(sf::Event&)=0;
};

void switchScene(Scene*);
Scene* getScene();

#endif