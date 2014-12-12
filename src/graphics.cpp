#include "graphics.h"

sf::RenderWindow* window;

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