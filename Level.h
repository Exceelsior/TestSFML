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
	std::list <Brick*> _brickList; //Liste de toutes les briques de la sc�ne
	std::list <Ball*> _ballList; // Liste de toutes les balles de la sc�ne
	std::list <Ball*> _ammoList; //Liste de toutes les balles TIREES PAR LE JOUEUR de la sc�ne
	//A la base, on avait eu l'id�e d'impl�menter des briques sp�ciales, dont une faisant spawn des petites billes
	//qui ne respawn pas quand elles atteignent le bord inf de l'�cran. Mais pas le temps :(

	int _magSize = 4; //Nombre de billes max que le joueur peut tirer d'affil�e
	int _ammo = 50; //R�serve de billes max du joueur
	
	Canon* _canon;

	std::string _gameState; //String pour classer notre jeu en diff�rents �tats (menuState, gameLoopState, winState, et loseState)

	//Grille du niveau facilement modifiable (on pourrait y r�f�rencer des briques sp�ciales avec des ID > � la vie max des briques, mais pas eu le temps :( )
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
	sf::Time _HUDTimer; //V�ritable chrono de temps de jeu
	sf::Clock _HUDClock; //Clock pour le chrono du jeu
	int _score;

public:
		
	Level(sf::RenderWindow &levelWindow); //Constructeur
	void DrawLevel(float deltaTime, sf::RenderWindow &window); //Affichage des entit�s
	void DrawHUD(sf::RenderWindow &window); //Affichage du HUD
	void HUDEvent(sf::Event& event); //R�ception des events pour changement de HUD
	void MoveAndCollideItems(float deltaTime, sf::RenderWindow &window); //D�placements et physiques
	void ShootBalls(sf::Event &event, sf::RenderWindow &window); //M�thode de tir par le joueur
	void StartTimer(); //M�thode particuli�re permettant de d�marrer le chrono, ou d'en r�cup�rer le temps
	std::list <Ball*> GetBallList() { return _ballList; }; //Simple getter

};