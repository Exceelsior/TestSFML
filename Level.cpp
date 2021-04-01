#include "Level.h"
#include "Math.h"

//Constructeur
Level::Level() {

	int _rows = sizeof _levelArray / sizeof _levelArray[0]; //Nombre de lignes
	int _cols = sizeof _levelArray[1] / sizeof(int); //Nombre de colonnes

	//Construction de l'ensemble des briques (positions fixes, pv aléatoires)
	for (int i = 0; i < _rows; i++) {
		for (int j = 0; j< _cols; j++) {

			if (_levelArray[i][j] > 0) {
				_brickList.push_back(new Brick(sf::Vector2f(j*_windowWidth/_cols, (i*_windowWidth/2)/(_rows)), //Position
				sf::Vector2f(_windowWidth/(_rows), (_windowWidth/2)/(_cols)), _levelArray[i][j])); //taille et vie
			}
		}
	}

	//Création du canon
	_canon = new Canon(sf::Vector2f(_windowWidth / 2, _windowHeight),
		sf::Vector2f((_windowHeight / _windowWidth) * 40, (_windowHeight / _windowWidth) * 80));
	
	//On crée et inclue les munitions du joueur à la liste des balles du niveau
	for (int i = 0; i < _maxAmmo; i++) {
		_ballList.push_back(new Ball((_windowHeight / _windowWidth) * 10, _canon->GetPosition(), true));
	}
	
	//On inclue ces munitions dans la liste des munitions du joueur
	for (auto it = _ballList.begin(); it != _ballList.end(); it++) {
		_ammoList.push_back(*it);
	}

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

			currentBall->BrickCollision(currentBrick);

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


void Level::ShootBalls(sf::Event &event, sf::RenderWindow &window) {

	if (event.type == sf::Event::MouseButtonPressed) {

		for (auto it = _ammoList.begin(); it != _ammoList.end(); it++) {
			
			Ball* _currentAmmo = *it;

			if (_currentAmmo->CheckIfReadyToBeLaunched()) {
				_currentAmmo->SetLaunched(true);
				_currentAmmo->SetMoveDirection(CreateNormalizedVector(sf::Mouse::getPosition(window), _currentAmmo->GetPosition()));
				_currentAmmo->SetReadyToLaunch(false);
				break;
			}
		}
	}
}