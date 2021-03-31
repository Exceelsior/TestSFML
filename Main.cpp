#include "SFML/Graphics.hpp"
#include <iostream>
#include "Math.h"
#include "Ball.h"
#include "Canon.h"
#include "Level.h"


void Update(sf::RenderWindow& mainWindow, sf::Event& event, sf::Clock& clock, Level& level) {

    Ball* _mainBall = *level.GetBallList().begin();

    while (mainWindow.isOpen()) { //tant que la fenêtre est ouverte (=le vrai Update de Unity)

        mainWindow.clear();
        float deltaTime = clock.getElapsedTime().asSeconds(); //frametime
        clock.restart(); //On reset la clock pour obtenir le frametime
        while (mainWindow.pollEvent(event)) { //On attend un event de fermeture
            if (event.type == sf::Event::EventType::Closed) { //Si l'event est reçu, on ferme la fenêtre
                mainWindow.close();
            }

            if (event.type == sf::Event::EventType::MouseButtonPressed && _mainBall->CheckIfReadyToBeLaunched()) {

                _mainBall->SetLaunched(true);
                _mainBall->SetMoveDirection(CreateNormalizedVector(sf::Mouse::getPosition(mainWindow), _mainBall->GetPosition()));
                _mainBall->SetReadyToLaunch(false);
            }
        }

        
        level.MoveAndCollideItems(mainWindow, deltaTime);
        level.DrawLevel(mainWindow, deltaTime);


        mainWindow.display();
        
    }
}

void StartGame() {

    sf::RenderWindow _renderWindow(sf::VideoMode(_windowWidth, _windowHeight), "Le meilleur casse-brique du monde");
    sf::Event _event;
    sf::Clock _clock;


    
    Level _level(10, 10);

    Update(_renderWindow, _event, _clock, _level);
}

int main()
{
    srand(time(NULL));
    StartGame();
}