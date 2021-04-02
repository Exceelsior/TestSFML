#include "SFML/Graphics.hpp"
#include <iostream>
#include "Level.h"

//Le main le plus clean du monde

void Update(sf::RenderWindow& mainWindow, sf::Event& event, sf::Clock& clock, Level& level) {

    while (mainWindow.isOpen()) { //Boucle de jeu

        mainWindow.clear();

        float deltaTime = clock.getElapsedTime().asSeconds(); //frametime
        clock.restart(); //On reset la clock pour obtenir le frametime

        while (mainWindow.pollEvent(event)) //Boucle de réception des events
        {
            if (event.type == sf::Event::EventType::Closed) { //On peut fermer la fenêtre
                mainWindow.close();
            }

            level.HUDEvent(event); //On récupère l'appui sur la touche Espace au menu
            level.ShootBalls(event, mainWindow); //On peut aussi tirer
        }

        level.MoveAndCollideItems(deltaTime, mainWindow);
        level.DrawLevel(deltaTime, mainWindow);
        level.DrawHUD(mainWindow); //On peut aussi actualiser le HUD si besoin

        mainWindow.display();
        
    }
    
}

void StartGame() {

    sf::RenderWindow _renderWindow(sf::VideoMode(_windowWidth, _windowHeight), "Un casse brique hors du commun!!" , sf::Style::Close | sf::Style::Titlebar);
    sf::Event _event;
    sf::Clock _clock;
    Level _level(_renderWindow);
    Update(_renderWindow, _event, _clock, _level);
}

int main()
{
    StartGame();
}