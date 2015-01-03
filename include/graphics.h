#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SFML/Graphics.hpp>

sf::RenderWindow* getWindow();
void createWindow(sf::Vector2u size, std::string title);
void deleteWindow();
sf::Font& getFont();

#endif