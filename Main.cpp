#include "SFML/Graphics.hpp"
#include <iostream>
#include "Utils.h"
#include "Math.h"
#include "Ball.h"
#include "Canon.h"
#include "CollisionManager.h"
#include "Entity.h"

//Note pour plus tard : faire une classe Level qui store : Balle, (futures) Briques, Utils (?), Math (?), Canon, CollisionManager...
void Update(sf::RenderWindow& mainWindow, sf::Event& event, sf::Clock& clock, Utils& utils, Math& math, Ball& mainBall, std::vector <Entity>& entities, CollisionManager collisionManager) {

    while (mainWindow.isOpen()) { //tant que la fenêtre est ouverte (=le vrai Update de Unity)

        mainWindow.clear();
        float deltaTime = clock.getElapsedTime().asSeconds(); //frametime

        while (mainWindow.pollEvent(event)) { //On attend un event de fermeture
            if (event.type == sf::Event::EventType::Closed) { //Si l'event est reçu, on ferme la fenêtre
                mainWindow.close();
            }

            if (event.type == sf::Event::EventType::MouseButtonPressed && mainBall.CheckIfReadyToBeLaunched()) {

                mainBall.SetLaunched(true);
                mainBall.SetSpeedDirection(math.CreateNormalizedVector(sf::Mouse::getPosition(mainWindow), mainBall.GetPosition()));
                mainBall.SetReadyToLaunch(false);
            }
        }

        if (mainBall.CheckIfHasBeenLaunched()) {
            mainBall.SetPosition(mainBall.GetPosition() + mainBall.GetSpeedDirection() * deltaTime * mainBall.GetMoveSpeed());
        }

        if (collisionManager.ManageCollision(entities)) {
            mainBall.SetReadyToLaunch(true);
        }

        mainWindow.draw(*mainBall.GetShape());
        mainWindow.display();
        clock.restart(); //On reset la clock pour obtenir le frametime
    }
}

void StartGame() {

    Utils _utils; //Objet aux méthodes et attributs divers
    Math _math;
    sf::RenderWindow _renderWindow(sf::VideoMode(_utils._width, _utils._height), "Le meilleur casse-brique du monde");
    sf::Event _event;
    sf::Clock _clock;
    CollisionManager _collisionManager(_utils._width, _utils._height);

    std::vector <Entity> _entities;
    Ball _mainBall((_utils._height / _utils._width) * 10, sf::Vector2f(_utils._width / 2, _utils._height));
    _entities.push_back(_mainBall);

    Update(_renderWindow, _event, _clock, _utils, _math, _mainBall, _entities, _collisionManager);
}

int main()
{
    StartGame();
}