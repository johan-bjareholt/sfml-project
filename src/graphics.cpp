#include <iostream>

#include "graphics.h"

sf::RenderWindow* window;
sf::Font* font=NULL;
const std::string fontname = "assets/fonts/calibri.ttf";

sf::RenderWindow* getWindow(){
	return window;
}

void createWindow(sf::Vector2u size, std::string title){
	// Options
    int windowOptions = sf::Style::None | sf::Style::Titlebar | sf::Style::Close;
    // Create window
    window = new sf::RenderWindow(sf::VideoMode(size.x, size.y), title, windowOptions);
    // Uncomment to enable vsync
    window->setVerticalSyncEnabled(true);
}


void deleteWindow(){
	delete window;
}

sf::Font* getFont(){
	if (font==NULL){
		if (!font->loadFromFile(fontname))
		{
			std::cout << "Could not load font " << fontname << std::endl;
		}
	}
	return font;
}