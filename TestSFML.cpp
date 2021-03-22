#include "SFML/Graphics.hpp"
#include <iostream>

int main()
{
    sf::RenderWindow renderWindow(sf::VideoMode(640, 480), "Ma premiere fenetre SFML");
    sf::Event event;


    sf::Clock clock;
    
    while (renderWindow.isOpen()) {
        while (renderWindow.pollEvent(event)) {
            if (event.type == sf::Event::EventType::Closed) {
                renderWindow.close();
            }
        }

        std::cout << "Duree entre 2 tours de boucle isOpen : " << clock.getElapsedTime().asMicroseconds() << " microsecondes" << std::endl;
        clock.restart();
        
        renderWindow.clear();
        renderWindow.display();
    }
}