#ifndef SCENE_H
#define SCENE_H

#include <SFML/Graphics.hpp>

class Scene {
public:
	virtual void load_graphics()=0;
	virtual void load_input()=0;
	virtual void loop_graphics(sf::RenderWindow&)=0;
	virtual void loop_input()=0;
};

#endif