#include "Level.h"

//Constructeur
Level::Level(sf::RenderWindow& levelWindow) {


	int _rows = sizeof _levelArray / sizeof _levelArray[0]; //Nombre de lignes de briques
	int _cols = sizeof _levelArray[1] / sizeof(int); //Nombre de colonnes de briques

	//Construction de l'ensemble des briques selon la matrice _levelArray
	for (int i = 0; i < _rows; i++) {
		for (int j = 0; j < _cols; j++) {

			if (_levelArray[i][j] > 0) {
				_brickList.push_back(new Brick(sf::Vector2f(j * _windowWidth / _cols, (i * _windowWidth / 2) / (_rows)), //Position
					sf::Vector2f(_windowWidth / (_rows), (_windowWidth / 2) / (_cols)), _levelArray[i][j])); //taille et vie
			}
		}
	}

	//Création d'un canon au style...minimaliste, mais fonctionnel
	_canon = new Canon(sf::Vector2f(_windowWidth / 2, _windowHeight),
		sf::Vector2f((_windowHeight / _windowWidth) * 40, (_windowHeight / _windowWidth) * 80));

	//On crée et inclue les munitions du joueur à la liste des balles du niveau
	for (int i = 0; i < _magSize; i++) {
		_ballList.push_back(new Ball((_windowHeight / _windowWidth) * 10, _canon->GetPosition(), true));
	}

	//On inclue ces munitions dans la liste des munitions du joueur
	for (auto it = _ballList.begin(); it != _ballList.end(); it++) {
		_ammoList.push_back(*it);
	}

	_gameState = "menuState"; //état de départ
	_levelHUD = new GameHUD(levelWindow);
	_score = 0;
}

//Les briques, le canon, et les balles ne seront affichées que dans le state "gameLoop"
void Level::DrawLevel(float deltaTime, sf::RenderWindow& window) {

	if (_gameState == "gameLoopState") {

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

		//Affichage du canon
		window.draw(*_canon->GetShape());
	}

}

//Méthode des collisions et déplacements d'entités appelée en permanence dans le state gameLoop
void Level::MoveAndCollideItems(float deltaTime, sf::RenderWindow& window) {

	if (_gameState == "gameLoopState") { //Si on est pas en train de jouer (ie dans le menu ou à la fin du jeu), on ne bouge rien

		//Boucle de mouvements et collisions de toutes les balles du niveau
		auto _itBalls = _ballList.begin();

		while (_itBalls != _ballList.end()) {

			Ball* currentBall = *_itBalls;
			currentBall->ResetBricksCollisions();

			if (currentBall->WallCollisions()) {

				if (currentBall->CheckIfShotFromCanon() && _ammo > 0) {

					currentBall->SetReadyToLaunch(true);
					currentBall->SetLaunched(false);
				}
				else if(currentBall->CheckIfShotFromCanon() && _ammo <= 0 && _brickList.size() > 0){

					currentBall->SetLaunched(false);
					_gameState = "loseState";
					_levelHUD->SetHUDToInitialized(false);
				}
				else{

					currentBall->SetToDestroyed(true); //On avait mis ça au cas où certaines briques spéciales feraient spawn d'autres balles "secondaires"
				}
			}

			//Boucle de collision avec toutes les briques existantes
			auto _itBricks = _brickList.begin();

			while (_itBricks != _brickList.end()) {

				Brick* currentBrick = *_itBricks;

				currentBall->BrickCollision(currentBrick);

				if (currentBrick->CheckIfHasBeenDestroyed()) { //Si la brique n'a plus de pv, on la retire de la liste

					_score += currentBrick->GetValue();
					_levelHUD->ActualizeScore(_score);
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

		if (_brickList.size() <= 0) {
			_gameState = "winState";
			_levelHUD->SetHUDToInitialized(false);
		}

		//Rotation du canon
		RotateSpriteToMouse(*_canon->GetShape(), window); //Rotation selon la position de la souris
	}
	
}


void Level::ShootBalls(sf::Event &event, sf:: RenderWindow &window) {

	if (event.type == sf::Event::MouseButtonPressed && _gameState == "gameLoopState" && _ammo > 0) {

		for (auto it = _ammoList.begin(); it != _ammoList.end(); it++) {
			
			Ball* _currentAmmo = *it;

			if (_currentAmmo->CheckIfReadyToBeLaunched()) {

				_currentAmmo->SetLaunched(true);
				_currentAmmo->SetMoveDirection(CreateNormalizedVector(sf::Mouse::getPosition(window), _currentAmmo->GetPosition()));
				_currentAmmo->SetReadyToLaunch(false);
				_ammo--;

				break;
			}
		}
	}
}

void Level::StartTimer() {
	
	_HUDClock.restart();
}

void Level::HUDEvent(sf::Event &event) {

	if (event.type == sf::Event::KeyPressed && _gameState == "menuState") {

		if (event.key.code == sf::Keyboard::Space) {

			_levelHUD->SetHUDToInitialized(false);
			_gameState = "gameLoopState";
		}
	}
}

//Méthode d'affichage du HUD selon l'état du jeu
void Level::DrawHUD(sf::RenderWindow& window) {

	if (_gameState == "menuState") {

		if (!_levelHUD->CheckIfHUDIsInitialized()) {

			_levelHUD->InitializeMenu();
			_levelHUD->SetHUDToInitialized(true);
		}
		else {
			_levelHUD->DisplayMenuHUD();
		}

	}
	else if (_gameState == "gameLoopState") {

		if (!_levelHUD->CheckIfHUDIsInitialized()) {

			StartTimer();
			_levelHUD->InitializeGameLoopHUD(_ammo, _score, int(_HUDTimer.asSeconds()));
		}

		_HUDTimer += _HUDClock.getElapsedTime();
		_levelHUD->DisplayGameLoopHUD(_HUDTimer.asSeconds());
	}
	else if (_gameState == "winState") {

		if (!_levelHUD->CheckIfHUDIsInitialized()) {

			_levelHUD->InitializeGameEndHUD(true, _score, int(_HUDTimer.asSeconds()));
			_levelHUD->SetHUDToInitialized(true);
		}

		_levelHUD->DisplayGameEndHUD();
	}
	else if (_gameState == "loseState") {

		if (!_levelHUD->CheckIfHUDIsInitialized()) {

			_levelHUD->InitializeGameEndHUD(false, _score, int(_HUDTimer.asSeconds()));
			_levelHUD->SetHUDToInitialized(true);
		}
		_levelHUD->DisplayGameEndHUD();
	}
}