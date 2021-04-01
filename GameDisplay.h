#pragma once
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
class GameDisplay
{
public:
    int score;
    int life;
    int endtime;
    sf::RenderWindow* game;
    bool timesaver;
    sf::Time timegoes;
    sf::Clock* timer;
    sf::Font font;

    //void timedisplay();
    //void posterscore();
    void endgame();
    void gui();
    //void affichagePartie();
    void startofgame();
    GameDisplay(sf::RenderWindow& mainWindow, sf::Clock& gametimer);
};

