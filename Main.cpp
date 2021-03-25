#include "SFML/Graphics.hpp"
#include <iostream>
#include "Math.h"
#include "Ball.h"

void ConstructLevel(float rows, float columns) {

    std::vector <Brick> _brickList;

    for (int i = 0; i < rows; i++) {
        
        for (int j = 0; j < columns; j++) {

            

        }
    }


    //return une array de Bricks ?
}


//Note pour plus tard : faire une classe Level qui store : Balle, (futures) Briques, Utils (?), Math (?), Canon, CollisionManager...
void Update(sf::RenderWindow& mainWindow, sf::Event& event, sf::Clock& clock, Ball& mainBall, Brick& brick) {

    while (mainWindow.isOpen()) { //tant que la fenêtre est ouverte (=le vrai Update de Unity)

        mainWindow.clear();
        float deltaTime = clock.getElapsedTime().asSeconds(); //frametime

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

        mainBall.BrickCollision(brick);


        mainWindow.draw(*mainBall.GetShape());
        mainWindow.draw(*brick.GetShape());
        mainWindow.display();
        clock.restart(); //On reset la clock pour obtenir le frametime
    }
}

void StartGame() {

    sf::RenderWindow _renderWindow(sf::VideoMode(_windowWidth, _windowHeight), "Le meilleur casse-brique du monde");
    sf::Event _event;
    sf::Clock _clock;

    Ball _mainBall((_windowHeight / _windowWidth) * 10, sf::Vector2f(_windowWidth / 2, _windowHeight));
    Brick _brick(sf::Vector2f(_windowWidth / 2, _windowHeight / 2), sf::Vector2f(50, 25));

    Update(_renderWindow, _event, _clock, _mainBall, _brick);
}

int main()
{
    StartGame();
}