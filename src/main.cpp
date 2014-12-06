#include <iostream>

#include <SFML/Graphics.hpp>


#include "graphics.h"
#include "scene.h"
#include "menu.h"

int main()
{
    // Setup window
    sf::Vector2u size (1280,720);
    std::string title = "My SFML program";
    createWindow(size, title);
    sf::RenderWindow* window = getWindow();

    // Set scene
    switchScene(new MenuScene());
    Scene* currentScene = getScene();

    while (window->isOpen())
    {
        // Update scene if it has changed
        currentScene = getScene();
        // Input
        sf::Event event;
        while (window->pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window->close();
            else
                currentScene->input(event);
        }
        // Game logic
        currentScene->loop_logic();
        // Graphics
        window->clear();
        currentScene->loop_graphics(*window);
        window->display();
    }
    deleteWindow();

    return 0;
}