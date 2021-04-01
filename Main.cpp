#include "SFML/Graphics.hpp"
#include <iostream>
#include "Level.h"


void Update(sf::RenderWindow& mainWindow, sf::Event& event, sf::Clock& clock, Level& level) {

    while (mainWindow.isOpen()) { //tant que la fenêtre est ouverte (=le vrai Update de Unity)

        mainWindow.clear();
        float deltaTime = clock.getElapsedTime().asSeconds(); //frametime
        clock.restart(); //On reset la clock pour obtenir le frametime
        while (mainWindow.pollEvent(event)) { //On attend un event de fermeture
            if (event.type == sf::Event::EventType::Closed) { //Si l'event est reçu, on ferme la fenêtre
                mainWindow.close();
            }

            level.ShootBalls(event, mainWindow);
        }
        
        level.MoveAndCollideItems(mainWindow, deltaTime);
        level.DrawLevel(mainWindow, deltaTime);


        mainWindow.display();
        
    }
}

void StartGame() {

    sf::RenderWindow _renderWindow(sf::VideoMode(_windowWidth, _windowHeight), "Le casse-brique le plus instable du monde");
    sf::Event _event;
    sf::Clock _clock;
    Level _level;

    Update(_renderWindow, _event, _clock, _level);
}

int main()
{
    srand(time(NULL));
    StartGame();
}