#include "SFML/Graphics.hpp"
#include <iostream>
#include "Math.h"
#include "Ball.h"
#include "Canon.h"
#include "Level.h"

//Note pour plus tard : faire une classe Level qui store : Balle, (futures) Briques, Math (?), Canon, CollisionManager...
void Update(sf::RenderWindow& mainWindow, sf::Event& event, sf::Clock& clock, Ball& mainBall, Level& level, Canon& canon) {

    while (mainWindow.isOpen()) { //tant que la fenêtre est ouverte (=le vrai Update de Unity)

        mainWindow.clear();
        float deltaTime = clock.getElapsedTime().asSeconds(); //frametime
        clock.restart(); //On reset la clock pour obtenir le frametime
        while (mainWindow.pollEvent(event)) { //On attend un event de fermeture
            if (event.type == sf::Event::EventType::Closed) { //Si l'event est reçu, on ferme la fenêtre
                mainWindow.close();
            }

            if (event.type == sf::Event::EventType::MouseButtonPressed && mainBall.CheckIfReadyToBeLaunched()) {

                mainBall.SetLaunched(true);
                mainBall.SetMoveDirection(CreateNormalizedVector(sf::Mouse::getPosition(mainWindow), mainBall.GetPosition()));
                mainBall.SetReadyToLaunch(false);
            }
        }

        if (mainBall.CheckIfHasBeenLaunched()) {
            mainBall.SetPosition(mainBall.GetPosition() + mainBall.GetMoveDirection() * deltaTime * mainBall.GetMoveSpeed());
        }

        if (mainBall.CheckWallCollision()) {
            mainBall.SetReadyToLaunch(true);
            mainBall.SetLaunched(false);
        }

        RotateSpriteToMouse(*canon.GetShape(), mainWindow); //rotation du canon

       
        level.DrawLevel(mainWindow);
        //mainBall.BrickCollision(brick); //Collisions avec les briques
        //mainWindow.draw(*brick.GetShape());
        
        
        mainWindow.draw(*mainBall.GetShape());
        mainWindow.draw(*canon.GetShape());
        mainWindow.display();
        
    }
}

void StartGame() {

    sf::RenderWindow _renderWindow(sf::VideoMode(_windowWidth, _windowHeight), "Le meilleur casse-brique du monde");
    sf::Event _event;
    sf::Clock _clock;


    
    Level _level(10, 10);
    Canon _canon(sf::Vector2f(_windowWidth / 2, _windowHeight), sf::Vector2f((_windowHeight / _windowWidth) * 40, (_windowHeight / _windowWidth) * 80));
    Ball _mainBall((_windowHeight / _windowWidth) * 10, _canon.GetPosition());

    Update(_renderWindow, _event, _clock, _mainBall, _level, _canon);
}

int main()
{
    srand(time(NULL));
    StartGame();
}