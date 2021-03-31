#include "Level.h"
#include "Math.h"

//Constructeur
Level::Level(int sizeX, int sizeY) {

	//Construction de l'ensemble des briques (positions fixes, pv aléatoires)
	for (int i = 0; i < sizeX; i++) {
		for (int j = 0; j < sizeY; j++) {

			_brickList.push_back(new Brick(sf::Vector2f(i*_windowWidth/sizeX, j*_windowWidth/(2*sizeY)),
				sf::Vector2f(_windowWidth/sizeX, _windowHeight /(3*sizeY)), rand() % 4 + 1));
		}
	}
	//Création du canon
	_canon = new Canon(sf::Vector2f(_windowWidth / 2, _windowHeight),
		sf::Vector2f((_windowHeight / _windowWidth) * 40, (_windowHeight / _windowWidth) * 80));
	
	//Création de la balle principale (tirée depuis le canon, jamais vraiment détruite)
	_ballList.push_back(new Ball((_windowHeight / _windowWidth) * 10, _canon->GetPosition(), true));
}

void Level::DrawLevel(sf::RenderWindow &window, float deltaTime){

	//Affichage des briques
	auto _itBricks = _brickList.begin();
	while (_itBricks != _brickList.end()) {

		Brick* currentBrick = *_itBricks;
		window.draw(*currentBrick->GetShape());
		_itBricks++;
		
	}

	//Affichage des balles
	auto _itBalls = _ballList.begin();
	while (_itBalls != _ballList.end()) {

		Ball* currentBall = *_itBalls;
		window.draw(*currentBall->GetShape());
		_itBalls++;
		
	}

	window.draw(*_canon->GetShape());
}

void Level::MoveAndCollideItems(sf::RenderWindow& window, float deltaTime) {

	//Boucle de mouvements et collisions de toutes les balles du niveau
	auto _itBalls = _ballList.begin();
	while (_itBalls != _ballList.end()) {

		Ball* currentBall = *_itBalls;

		if (currentBall->CheckWallCollision()) {
			if (currentBall->CheckIfShotFromCanon()) {
				currentBall->SetReadyToLaunch(true);
				currentBall->SetLaunched(false);
			}
			else {
				currentBall->SetToDestroyed(true);
			}
		}

		//Boucle de collision avec toutes les briques existantes
		auto _itBricks = _brickList.begin();
		while (_itBricks != _brickList.end()) {

			Brick* currentBrick = *_itBricks;

			currentBall->BrickCollision(*currentBrick);

			if (currentBrick->CheckIfHasBeenDestroyed()) { //Si la brique n'a plus de pv, on la retire de la liste
				_itBricks = _brickList.erase(_itBricks);
			}
			else {
				_itBricks++;
			}
		}

		if (currentBall->CheckIfHasBeenDestroyed()) {
			_itBalls = _ballList.erase(_itBalls);
		}
		else {
			if (currentBall->CheckIfHasBeenLaunched()) { //Déplacements de la balle
				currentBall->SetPosition(currentBall->GetPosition() +
					currentBall->GetMoveDirection() * deltaTime * currentBall->GetMoveSpeed());
			}

			_itBalls++;
		}
	}

	//Rotation du canon
	RotateSpriteToMouse(*_canon->GetShape(), window); //Rotation selon la position de la souris
}
