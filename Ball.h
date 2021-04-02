#pragma once
#include "Entity.h"
#include "Brick.h"
#include <vector>
#include <algorithm>
#include <string>
#include <list>
#include <iostream>

//Classe Balle contenant les infos de rayon, de lancement, et les méthodes de collision

class Ball :public Entity {

private:

	float _ballRadius; //taille de la balle

	sf::Vector2f _startPosition;

	bool _isReadyToBeLaunched;
	bool _hasBeenLaunched;

	int _ballDamages;

	bool _shotFromCanon;
	bool _hasBeenDestroyed;

	bool _hasCollidedWithBrick; //booléen qui autorisera ou non la collision avec une brique
	bool _hasCollidedWithWall; //idem avec les murs
	std::list <char> _wallsCollided; //Liste des murs avec lesquelles la balle est rentrée en contact pendant 1 tour de boucle
	std::list <Brick*> _bricksCollided; //idem avec les briques

public:

	//constructeur
	Ball(float ballRadius, sf::Vector2f startPosition, bool shotFromCanon);

	sf::Vector2f GetStartPosition() { return _startPosition; };

	//Getter/setter du lancement des billes du joueur, utile pour l'action de tir
	void SetReadyToLaunch(bool isReady) { _isReadyToBeLaunched = isReady; };
	bool CheckIfReadyToBeLaunched() { return _isReadyToBeLaunched; };

	//Idem mais utile pour les mouvements et collisions
	void SetLaunched(bool hasBeenLaunched) { _hasBeenLaunched = hasBeenLaunched; };
	bool CheckIfHasBeenLaunched() { return _hasBeenLaunched; };

	//Explicite
	float GetBallRadius() { return _ballRadius; };

	//Collisions
	bool WallCollisions();
	void BrickCollision(Brick* brick);

	//Getter/setter de la destruction des billes secondaires (billes apparaissant à la destruction de briques spéciales)
	void SetToDestroyed(bool isDestroyed) { _hasBeenDestroyed = isDestroyed; };
	bool CheckIfHasBeenDestroyed() { return _hasBeenDestroyed; };

	bool CheckIfShotFromCanon() { return _shotFromCanon; };

	void ResetBricksCollisions();
	void ResetWallsCollisions();

	bool CheckIfCollidedWithWall(char wall);
	bool CheckIfCollidedWithBrick(Brick* brick);
};