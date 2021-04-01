#include "SFML/Graphics.hpp"
#include <iostream>
#include "Level.h"
#include "GameDisplay.h"

//Note pour plus tard : faire une classe Level qui store : Balle, (futures) Briques, Math (?), Canon, CollisionManager...
void Update(sf::RenderWindow& mainWindow, sf::Event& event, sf::Clock& clock, Level& level,  GameDisplay& game) {

    sf::Clock _clock;
    bool startmenu = true;
    bool currentgame = false;
    bool endgame = false;
    bool gamelaunch = false;
    bool triggerfrontmontant = false;

    while (mainWindow.isOpen()) { //tant que la fenêtre est ouverte (=le vrai Update de Unity)

       // mainWindow.clear();
        float deltaTime = clock.getElapsedTime().asSeconds(); //frametime
        clock.restart(); //On reset la clock pour obtenir le frametime

        while (mainWindow.pollEvent(event)) //On attend un event de fermeture
        {
            if (event.type == sf::Event::EventType::Closed) { //Si l'event est reçu, on ferme la fenêtre
                mainWindow.close();
            }
        }

            if (startmenu == true) // on rentre dans la fenetre de début
            {
                std::cout << "menu" << std::endl;
                game.startofgame();
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) == true && triggerfrontmontant == false)
                {
                   startmenu = false;
                   gamelaunch = true;
                }
                triggerfrontmontant = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
            }

            if (gamelaunch == true) 
            {
                game = GameDisplay(mainWindow, _clock);
                gamelaunch = false;
                currentgame = true;
                _clock.restart();
                std::cout << "initialisation fini" << std::endl;
            }
            else
            {
                if (currentgame == true)
                {
                    level.ShootBalls(event, mainWindow);
                    level.MoveAndCollideItems(mainWindow, deltaTime);
                    level.DrawLevel(mainWindow, deltaTime);
                    game.gui();
                    if (game.life <= 0) //|| level.instancebricks.size() <= 0)
                    {
                       endgame = true;
                       currentgame = false;
                    }
                }
            }
            
            if (endgame == true)
            {
                game.endgame();

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) == true && triggerfrontmontant == false)
                {
                   startmenu = true;
                   currentgame = false;
                   endgame = false;
                }
                triggerfrontmontant = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
            }

            mainWindow.display();
            mainWindow.clear();
     }  
    
}

void StartGame() {

    sf::RenderWindow renderWindow(sf::VideoMode(_windowWidth, _windowHeight), "Un casse brique hors du commun!!" , sf::Style::Close | sf::Style::Titlebar);
    sf::Event _event;
    sf::Clock _clock;
    GameDisplay game(renderWindow, _clock);
    Level _level;
    Update(renderWindow, _event, _clock, _level, game);
}

int main()
{
    srand(time(NULL));
    StartGame();
}