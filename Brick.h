#pragma once
#include "Entity.h"

//Classe Brique contenant les infos de taille, vie et destruction

class Brick : public Entity {

private:

	int _life;
	sf::Vector2f _size;
	bool _hasBeenDestroyed;

public:

	void ActualizeColors();

	//Constructeur
	Brick(sf::Vector2f position, sf::Vector2f size, int life);

	void SetToDestroyed(bool isDestroyed) { _hasBeenDestroyed = isDestroyed; };
	void TakeDamages(float damages);

	bool CheckIfHasBeenDestroyed() { return _hasBeenDestroyed; };

};