#pragma once
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Utils.h"
#include <iostream>

//Classe regroupant les méthodes et attributs nécessaires aux HUD pendant le jeu

class GameHUD
{
private:

    sf::RenderWindow* _gameWindow;
    sf::Font _font; //Police d'écriture

    sf::Text _menuTextTitle; //Titre  du menu
    sf::Text _menuTextMessage; //Message du menu demandant l'appui sur la barre espace

    sf::Text _gameLoopTextClock; //Texte du chrono (UI)
    sf::Text _gameLoopTextScore; //Texte de score (UI)
    sf::Text _gameLoopTextAmmo; //Texte des munitions (UI)

    sf::Text _gameEndTextScore; //Score affiché à la fin du jeu
    sf::Text _gameEndTextClock; //Temps /       /  /  /   /   /
    sf::Text _gameEndTextMessage;//Message "gagné" ou "perdu"
    
    bool _isHUDBeingDisplayed; //booléen pratique pour éviter de réinitialiser chaque HUD à chaque frame

public:

    void InitializeMenu();
    void DisplayMenuHUD();

    void InitializeGameLoopHUD(int ammo, int score, float time);
    void DisplayGameLoopHUD(float time);
    

    void InitializeGameEndHUD(bool gameWon, int score, int time);
    void DisplayGameEndHUD();
   
    void ActualizeScore(int score);
    GameHUD(sf::RenderWindow& mainWindow);

    bool CheckIfHUDIsInitialized() { return _isHUDBeingDisplayed; };
    void SetHUDToInitialized(bool isDisplayed) { _isHUDBeingDisplayed = isDisplayed; };
};

