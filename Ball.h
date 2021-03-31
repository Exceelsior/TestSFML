#pragma once
#include "Entity.h"
#include "Brick.h"

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


public:

	//constructeur
	Ball(float ballRadius, sf::Vector2f startPosition, bool shotFromCanon);

	sf::Vector2f GetStartPosition() { return _startPosition; };

	void SetReadyToLaunch(bool isReady) { _isReadyToBeLaunched = isReady; };
	bool CheckIfReadyToBeLaunched() { return _isReadyToBeLaunched; };

	void SetLaunched(bool hasBeenLaunched) { _hasBeenLaunched = hasBeenLaunched; };
	bool CheckIfHasBeenLaunched() { return _hasBeenLaunched; };

	float GetBallRadius() { return _ballRadius; };

	bool CheckWallCollision();

	void BrickCollision(Brick& brick);

	void SetToDestroyed(bool isDestroyed) { _hasBeenDestroyed = isDestroyed; };
	bool CheckIfHasBeenDestroyed() { return _hasBeenDestroyed; };

	bool CheckIfShotFromCanon() { return _shotFromCanon; };

};