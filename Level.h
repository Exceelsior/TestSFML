#pragma once
#include "Ball.h"
#include "Canon.h"
#include "Brick.h"
#include <iterator>
#include <list>
#include "GameHUD.h"
#include "Math.h"

//Classe du niveau, c'est ici qu'on supervise quasiment tout ce qui se passe dans le jeu (sorte de super-manager)

class Level {

private:
	std::list <Brick*> _brickList; //Liste de toutes les briques de la scène
	std::list <Ball*> _ballList; // Liste de toutes les balles de la scène
	std::list <Ball*> _ammoList; //Liste de toutes les balles TIREES PAR LE JOUEUR de la scène
	//A la base, on avait eu l'idée d'implémenter des briques spéciales, dont une faisant spawn des petites billes
	//qui ne respawn pas quand elles atteignent le bord inf de l'écran. Mais pas le temps :(

	int _magSize = 4; //Nombre de billes max que le joueur peut tirer d'affilée
	int _ammo = 50; //Réserve de billes max du joueur
	
	Canon* _canon;

	std::string _gameState; //String pour classer notre jeu en différents états (menuState, gameLoopState, winState, et loseState)

	//Grille du niveau facilement modifiable (on pourrait y référencer des briques spéciales avec des ID > à la vie max des briques, mais pas eu le temps :( )
	int _levelArray[10][10] = {
	{0,2,2,3,3,3,3,2,2,0},
	{2,1,0,0,0,0,0,0,1,2},
	{2,1,0,2,3,3,2,0,1,2},
	{2,1,0,3,4,4,3,0,1,2},
	{2,1,0,3,4,4,3,0,1,2},
	{2,1,0,2,3,3,2,0,1,2},
	{2,1,0,0,0,0,0,0,1,2},
	{2,1,0,0,0,0,0,0,1,2},
	{2,1,1,0,2,2,0,1,1,2},
	{0,2,2,0,3,3,0,2,2,0}
	};

	GameHUD* _levelHUD; //HUD du niveau, variable en fonction du gameState

	bool _isTimePassing; //Vraiment utile ??
	sf::Time _HUDTimer; //Véritable chrono de temps de jeu
	sf::Clock _HUDClock; //Clock pour le chrono du jeu
	int _score;

public:
		
	Level(sf::RenderWindow &levelWindow); //Constructeur
	void DrawLevel(float deltaTime, sf::RenderWindow &window); //Affichage des entités
	void DrawHUD(sf::RenderWindow &window); //Affichage du HUD
	void HUDEvent(sf::Event& event); //Réception des events pour changement de HUD
	void MoveAndCollideItems(float deltaTime, sf::RenderWindow &window); //Déplacements et physiques
	void ShootBalls(sf::Event &event, sf::RenderWindow &window); //Méthode de tir par le joueur
	void StartTimer(); //Méthode particulière permettant de démarrer le chrono, ou d'en récupérer le temps
	std::list <Ball*> GetBallList() { return _ballList; }; //Simple getter

};