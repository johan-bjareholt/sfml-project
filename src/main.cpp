#include <iostream>

#include <SFML/Graphics.hpp>

#include "scene.h"
#include "menu.h"
#include "game.h"

int main()
{
    // Basic window options
    sf::Vector2u size (1280,720);
    std::string title = "My SFML program";
    int windowOptions = sf::Style::None | sf::Style::Titlebar | sf::Style::Close;
    // Create window
    sf::RenderWindow window(sf::VideoMode(size.x, size.y), title, windowOptions);
    // Frame cap
    window.setFramerateLimit(240);
    // Uncomment to enable vsync
    //window.setVerticalSyncEnabled(true);

    switchScene(new MenuScene());
    Scene* currentScene = getScene();

    while (window.isOpen())
    {
        // Update scene if it has changed
        currentScene = getScene();
        // Input
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
            else
                currentScene->input(event);
        }
        // Game logic
        currentScene->loop_logic();
        // Graphics
        window.clear();
        currentScene->loop_graphics(window);
        window.display();
    }

    return 0;
}