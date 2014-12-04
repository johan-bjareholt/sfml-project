#include <SFML/Graphics.hpp>

#include "scene.h"
#include "menu.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");

    Scene* currentScene = new MenuScene();
    Scene* previousScene = NULL;

    while (window.isOpen())
    {
        if (currentScene != previousScene){
            if (previousScene!=NULL)
                delete previousScene;
            currentScene->load_input();
            currentScene->load_graphics();
            previousScene = currentScene;
        }
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        currentScene->loop_input();
        currentScene->loop_graphics(window);
        window.display();
    }

    return 0;
}