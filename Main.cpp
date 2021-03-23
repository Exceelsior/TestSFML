#include "SFML/Graphics.hpp"
#include <iostream>
//#include "Utils.h"
//#include "Ball.h"

int iLargeurFenetre = 480;
int iHauteurFenetre = 720;
int iBallSize = 20;
int iBallRadius = (iHauteurFenetre / iLargeurFenetre) * iBallSize;
sf::CircleShape ball(iBallRadius);
float fLaunchSpeed = 500;
bool bHasButtonGotPressed;
bool bIsReadyToBeLaunched;
sf::Vector2f v2StartPosition(iLargeurFenetre / 2, iHauteurFenetre);

void Update(sf::RenderWindow& mainWindow, sf::Event& event, sf::Clock& clock) {

    while (mainWindow.isOpen()) { //tant que la fenêtre est ouverte

        mainWindow.clear();
        float deltaTime = clock.getElapsedTime().asSeconds(); //frameTime

        while (mainWindow.pollEvent(event)) { //On attend un event de fermeture
            if (event.type == sf::Event::EventType::Closed) { //Si l'event est reçu, on ferme la fenêtre
                mainWindow.close();
            }

            if (event.type == sf::Event::EventType::MouseButtonPressed && bIsReadyToBeLaunched) {
                bHasButtonGotPressed = true;
                bIsReadyToBeLaunched = false;
            }
        }

        if (bHasButtonGotPressed) {
            ball.setPosition(sf::Vector2f(ball.getPosition().x, ball.getPosition().y - fLaunchSpeed * deltaTime));
        }

        if (ball.getPosition().y < 0) {
            ball.setPosition(v2StartPosition);
            bIsReadyToBeLaunched = true;
            bHasButtonGotPressed = false;
        }

        mainWindow.draw(ball);
        mainWindow.display();
        clock.restart(); //On reset la clock
    }
}

void Start() {

    sf::RenderWindow renderWindow(sf::VideoMode(480, 720), "Ma premiere fenetre SFML");
    sf::Event event;
    sf::Clock clock;

    ball.setPosition(v2StartPosition);
    ball.setOrigin(sf::Vector2f(ball.getLocalBounds().width / 2, ball.getLocalBounds().height));
    ball.setFillColor(sf::Color(0, 255, 255, 255)); //On le colore en cyan

    bIsReadyToBeLaunched = true;
    Update(renderWindow, event, clock);
    
}

int main()
{
    Start();
}