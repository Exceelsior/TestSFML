#include "GameDisplay.h"


GameDisplay::GameDisplay(sf::RenderWindow& mainWindow, sf::Clock& gametimer)
{
    font.loadFromFile("Xeliard.ttf");
    timesaver = true;
    timer = &gametimer;
    game = &mainWindow;
    score = 0;
    life = 3;
}

void GameDisplay::gui()
{
    sf::Text clock;
    sf::Text pointscore;
    clock.setFont(font);
    pointscore.setFont(font);
    clock.setCharacterSize(30);
    pointscore.setCharacterSize(30);
    clock.setFillColor(sf::Color::White);
    pointscore.setFillColor(sf::Color::White);
    timegoes = timer->getElapsedTime();
    clock.setString("Temps : " + std::to_string((timegoes.asSeconds())));
    pointscore.setString("Score: " + std::to_string((score)));
    clock.setPosition(850, 5);
    pointscore.setPosition(200, 5);
    game->draw(clock);
    game->draw(pointscore);

}

void GameDisplay::startofgame() // Affichage de texte pour la premiere fenêtre de jeu 
{
    sf::Text title;
    sf::Text startmessage;
    title.setFont(font);
    title.setCharacterSize(100);
    title.setFillColor(sf::Color::Red);
    title.setPosition(45, 160);
    title.setStyle(sf::Text::Bold);
    title.setString("Un casse brique hors du commun!!");
    startmessage.setFont(font);
    startmessage.setCharacterSize(35);
    startmessage.setFillColor(sf::Color::Yellow);
    startmessage.setPosition(125, 600);
    startmessage.setString("Appuyez sur la touche espace pour commencer la partie ");
    game->draw(title);
    game->draw(startmessage);
}

void GameDisplay::endgame() // Affichage de la fênetre de fin( Victoire ou Défaite ) avec les textes de score , du temps et possibilité de recommencer le jeu. 
{
    sf::Text clock;
    sf::Text pointscore;
    sf::Text end;
    sf::Text endmessage;



    clock.setFont(font);
    pointscore.setFont(font);

    clock.setCharacterSize(50);
    pointscore.setCharacterSize(50);

    clock.setFillColor(sf::Color::Green);
    pointscore.setFillColor(sf::Color::Green);
    if (timesaver == true)
    {
        timegoes = timer->getElapsedTime();
        endtime = timegoes.asSeconds();
        timesaver = false;

    }
    clock.setString("Temps : " + std::to_string((endtime)));
    pointscore.setString("Score: " + std::to_string((score)));

    clock.setPosition(700, 60);
    pointscore.setPosition(200, 60);

    end.setFont(font);
    end.setCharacterSize(80);
    end.setFillColor(sf::Color::Red);
    end.setPosition(450, 300);
    end.setStyle(sf::Text::Bold);

    endmessage.setFont(font);
    endmessage.setCharacterSize(26);
    endmessage.setFillColor(sf::Color::Yellow);
    endmessage.setPosition(260, 620);
    endmessage.setString("Pour retourner au menu appuyez sur la touche espace");

    if (life == 0)
    {
        end.setString("PERDU");
    }
    else
    {
        end.setString("GAGNE");
    }

    game->draw(clock);
    game->draw(pointscore);
    game->draw(end);
    game->draw(endmessage);

}
