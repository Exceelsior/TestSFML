#include "GameHUD.h"

GameHUD::GameHUD(sf::RenderWindow &mainWindow)
{
    _font.loadFromFile("Xeliard.ttf");
    _gameWindow = &mainWindow;
}

void GameHUD::InitializeGameLoopHUD(int ammo, int score, float time)
{
    
    _gameLoopTextClock.setFont(_font);
    _gameLoopTextClock.setCharacterSize(_windowWidth / 20);
    _gameLoopTextClock.setString("Temps : " + std::to_string((int(time))));
    _gameLoopTextClock.setFillColor(sf::Color::White);
    sf::FloatRect _gameLoopTextClockRect = _gameLoopTextClock.getLocalBounds();
    _gameLoopTextClock.setOrigin(_gameLoopTextClockRect.left,
        _gameLoopTextClockRect.top + _gameLoopTextClockRect.height);
    _gameLoopTextClock.setPosition(0, _windowHeight);

    _gameLoopTextScore.setFont(_font);
    _gameLoopTextScore.setCharacterSize(_windowWidth / 20);
    _gameLoopTextScore.setFillColor(sf::Color::White);
    _gameLoopTextScore.setString("Score: " + std::to_string((score)));
    sf::FloatRect _gameLoopTextScoreRect = _gameLoopTextScore.getLocalBounds();
    _gameLoopTextScore.setOrigin(_gameLoopTextScoreRect.left,
        _gameLoopTextScoreRect.top + _gameLoopTextScoreRect.height);
    _gameLoopTextScore.setPosition(0, 9*_windowHeight/10);

    _gameLoopTextAmmo.setFont(_font);
    _gameLoopTextAmmo.setCharacterSize(_windowWidth / 20);
    _gameLoopTextAmmo.setFillColor(sf::Color::White);
    _gameLoopTextAmmo.setString("Ammo: " + std::to_string((ammo)));
    sf::FloatRect _gameLoopTextAmmoRect = _gameLoopTextAmmo.getLocalBounds();
    _gameLoopTextAmmo.setOrigin(_gameLoopTextAmmoRect.left + _gameLoopTextAmmoRect.width,
        _gameLoopTextScoreRect.top + _gameLoopTextScoreRect.height);
    _gameLoopTextAmmo.setPosition(_windowWidth, _windowHeight);

}


void GameHUD::DisplayGameLoopHUD(float time) {
    _gameLoopTextClock.setString("Temps : " + std::to_string((time)));
    _gameWindow->draw(_gameLoopTextClock);
    _gameWindow->draw(_gameLoopTextScore);
    _gameWindow->draw(_gameLoopTextAmmo);
}

void GameHUD::InitializeMenu() // Affichage de texte pour la premiere fenêtre de jeu 
{
    
    _menuTextTitle.setFont(_font);
    _menuTextTitle.setFillColor(sf::Color::Red);
    _menuTextTitle.setStyle(sf::Text::Bold);
    _menuTextTitle.setString("Un casse-brique hors du commun !!");
    _menuTextTitle.setCharacterSize(_windowWidth / 21);
    sf::FloatRect _menuTextTitleRect = _menuTextTitle.getLocalBounds();
    _menuTextTitle.setOrigin(_menuTextTitleRect.left + _menuTextTitleRect.width / 2, _menuTextTitleRect.top + _menuTextTitleRect.height / 2);
    _menuTextTitle.setPosition(_windowWidth/2 , _windowHeight/4);
    
    _menuTextMessage.setFont(_font);
    _menuTextMessage.setFillColor(sf::Color::Yellow);
    _menuTextMessage.setString("Appuyez sur la touche espace pour commencer la partie ");
    _menuTextMessage.setCharacterSize(_windowWidth/30);
    sf::FloatRect _menuTextMessageRect = _menuTextMessage.getLocalBounds();
    _menuTextMessage.setOrigin(_menuTextMessageRect.left + _menuTextMessageRect.width / 2, _menuTextMessageRect.top + _menuTextMessageRect.height / 2);
    _menuTextMessage.setPosition(_windowWidth/2, _windowHeight*3/4);

}

void GameHUD::DisplayMenuHUD() {
    _gameWindow->draw(_menuTextTitle);
    _gameWindow->draw(_menuTextMessage);
}


void GameHUD::InitializeGameEndHUD(bool gameWon, int score, int time) // Affichage de la fênetre de fin( Victoire ou Défaite ) avec les textes de score , du temps et possibilité de recommencer le jeu. 
{
    _gameEndTextScore.setFont(_font);
    _gameEndTextScore.setCharacterSize(_windowWidth/15);
    _gameEndTextScore.setFillColor(sf::Color::Green);
    _gameEndTextScore.setString("Score: " + std::to_string((score)));
    sf::FloatRect _gameEndTextScoreRect = _gameEndTextScore.getLocalBounds();
    _gameEndTextScore.setOrigin(_gameEndTextScoreRect.left + _gameEndTextScoreRect.width / 2,
        _gameEndTextScoreRect.top + _gameEndTextScoreRect.height / 2);
    _gameEndTextScore.setPosition(_windowWidth/2, _windowHeight*2/3);


    _gameEndTextClock.setFont(_font);
    _gameEndTextClock.setCharacterSize(_windowWidth / 15);
    _gameEndTextClock.setFillColor(sf::Color::Green);
    _gameEndTextClock.setString("Temps: " + std::to_string((time)));
    sf::FloatRect _gameEndTextClockRect = _gameEndTextClock.getLocalBounds();
    _gameEndTextClock.setOrigin(_gameEndTextClockRect.left + _gameEndTextClockRect.width / 2,
        _gameEndTextClockRect.top + _gameEndTextClockRect.height / 2);
    _gameEndTextClock.setPosition(_windowWidth / 2, _windowHeight*3/4);

    _gameEndTextMessage.setFont(_font);
    _gameEndTextMessage.setCharacterSize(_windowWidth / 15);
    _gameEndTextMessage.setFillColor(sf::Color::Red);

    if (gameWon) {
        _gameEndTextMessage.setString("Gagné !");
    }
    else
    {
        _gameEndTextMessage.setString("Perdu !");
    }

    sf::FloatRect _gameEndTextMessageRect = _gameEndTextMessage.getLocalBounds();
    _gameEndTextMessage.setOrigin(_gameEndTextMessageRect.left + _gameEndTextMessageRect.width / 2,
        _gameEndTextMessageRect.top + _gameEndTextMessageRect.height / 2);
    _gameEndTextMessage.setPosition(_windowWidth / 2, _windowHeight/3);

}

void GameHUD::DisplayGameEndHUD() {

    _gameWindow->draw(_gameEndTextScore);
    _gameWindow->draw(_gameEndTextClock);
    _gameWindow->draw(_gameEndTextMessage);
}

void GameHUD::ActualizeScore(int score)
{
    _gameLoopTextScore.setString("Score: " + std::to_string((score)));
    _gameWindow->draw(_gameLoopTextScore);
}