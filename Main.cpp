#include "SFML/Graphics.hpp"
#include <iostream>
#include "Utils.h"
#include "Math.h"
#include "Ball.h"
#include "Canon.h"

bool hasButtonGotPressed;

void Update(sf::RenderWindow& mainWindow, sf::Event& event, sf::Clock& clock, Utils& utils, Math& math, Ball& mainBall) {

    while (mainWindow.isOpen()) { //tant que la fenêtre est ouverte

        mainWindow.clear();
        float deltaTime = clock.getElapsedTime().asSeconds(); //frameTime

        while (mainWindow.pollEvent(event)) { //On attend un event de fermeture
            if (event.type == sf::Event::EventType::Closed) { //Si l'event est reçu, on ferme la fenêtre
                mainWindow.close();
            }

            if (event.type == sf::Event::EventType::MouseButtonPressed && mainBall.CheckIfReadyToBeLaunched()) {

                hasButtonGotPressed = true;
                mainBall.SetSpeedDirection(math.CreateNormalizedVector(sf::Mouse::getPosition(mainWindow), mainBall.GetPosition()));
                mainBall.SetReadyToLaunch(false);
            }
        }

        if (hasButtonGotPressed) {

            mainBall.SetPosition(mainBall.GetPosition() + mainBall.GetSpeedDirection() * deltaTime * mainBall.GetMoveSpeed());
        }

        mainWindow.draw(*mainBall.GetShape());
        mainWindow.display();
        clock.restart(); //On reset la clock
    }
}

void StartGame() {

    Utils utils; //Objet aux méthodes et attributs divers
    Math math;
    sf::RenderWindow renderWindow(sf::VideoMode(utils._width, utils._height), "Le meilleur casse-brique du monde");
    sf::Event event;
    sf::Clock clock;

    Ball _mainBall((utils._height / utils._width) * 10, sf::Vector2f(utils._width / 2, utils._height));

    Update(renderWindow, event, clock, utils, math, _mainBall);
}

int main()
{
    StartGame();
}