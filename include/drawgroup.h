#ifndef DRAWGROUP_H
#define DRAWGROUP_H

#include <vector>
#include <SFML/Graphics.hpp>

class DrawGroup {
private:
	std::vector<sf::Drawable*> drawables;
public:
	void add(sf::Drawable&);
	void remove(sf::Drawable*);
	void draw(sf::RenderWindow& window);
	void deleteAll();

	sf::Drawable* operator[](int index);
	int size();
};

#endif