#include "drawgroup.h"

void DrawGroup::add(sf::Drawable& drawable){
	drawables.push_back(&drawable);
}

void DrawGroup::remove(sf::Drawable* drawable){
	for (int i=0; i<drawables.size(); i++){
		if (drawable==drawables[i]){
			drawables.erase(drawables.begin()+i);
		}
	}
}

void DrawGroup::deleteAll(){
	for (int i=0; i<drawables.size(); i++){
		delete drawables[i];
	}
}

void DrawGroup::draw(sf::RenderWindow& window){
	for (int i=0; i<drawables.size(); i++){
		window.draw(*drawables[i]);
	}
}




sf::Drawable* DrawGroup::operator[](int index){
	return drawables[index];
}

int DrawGroup::size(){
	return drawables.size();
}