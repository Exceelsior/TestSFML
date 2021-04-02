#include "Ball.h"

Ball::Ball(float ballRadius, sf::Vector2f startPosition, bool shotFromCanon) : Entity(_startPosition.x, _startPosition.y)
{
    _shotFromCanon = shotFromCanon;
    _ballRadius = ballRadius;
    _ballDamages = 1;
    _shape = new sf::CircleShape(_ballRadius);
    _shape->setFillColor(sf::Color(0, 255, 255, 255)); //Pimp my ball
    _startPosition = startPosition;
    _shape->setOrigin(_shape->getLocalBounds().width / 2, _shape->getLocalBounds().height);
    SetPosition(startPosition); //Méthode de la classe mère Entity !
    SetMoveSpeed(1000);
    _isReadyToBeLaunched = true;
    _hasBeenDestroyed = false;

}

bool Ball::CheckIfCollidedWithWall(char wall) {
    if (std::find(_wallsCollided.begin(), _wallsCollided.end(), wall) != _wallsCollided.end()) {
        return true;
    }
    else {
        return false;
    }
}

bool Ball::CheckIfCollidedWithBrick(Brick* brick) {
    if (std::find(_bricksCollided.begin(), _bricksCollided.end(), brick) != _bricksCollided.end()) {
        return true;
    }
    else {
        return false;
    }
}

void Ball::ResetWallsCollisions() {
    _wallsCollided.clear();
    _hasCollidedWithWall = false;
}

bool Ball::WallCollisions() {


    if (GetShape()->getGlobalBounds().left <= 0 && !_hasCollidedWithWall && !CheckIfCollidedWithWall('w')) {
        _hasCollidedWithWall = true;
        _wallsCollided.push_back('w');
        SetMoveDirection(sf::Vector2f(-GetMoveDirection().x, GetMoveDirection().y));
    }

    else if (GetShape()->getGlobalBounds().width + GetShape()->getGlobalBounds().left >= _windowWidth &&
        !_hasCollidedWithWall && !CheckIfCollidedWithWall('e')) {

        _hasCollidedWithWall = true;
        _wallsCollided.push_back('e');
        SetMoveDirection(sf::Vector2f(-GetMoveDirection().x, GetMoveDirection().y));
    }

    else if (GetShape()->getGlobalBounds().top <= 0 && !_hasCollidedWithWall && !CheckIfCollidedWithWall('n')) {
        _hasCollidedWithWall = true;
        _wallsCollided.push_back('n');
        SetMoveDirection(sf::Vector2f(GetMoveDirection().x, -GetMoveDirection().y));
    }

    else if (GetShape()->getGlobalBounds().height + GetShape()->getGlobalBounds().top > _windowHeight &&
        !_hasCollidedWithWall && !CheckIfCollidedWithWall('s')) {

        _hasCollidedWithWall = true;
        _wallsCollided.push_back('s');
        SetPosition(sf::Vector2f(GetStartPosition()));
        SetMoveDirection(sf::Vector2f(0, 0));
        return true;
    }
    else {
        ResetWallsCollisions();
    }
    return false;

}

//Méthode de collision avec toutes les briques du niveau
void Ball::BrickCollision(Brick* brick) {


    sf::FloatRect _brickBounds = brick->GetShape()->getGlobalBounds();
    sf::FloatRect _ballBounds = _shape->getGlobalBounds();


    if (_ballBounds.intersects(_brickBounds) && !_hasCollidedWithBrick && !CheckIfCollidedWithBrick(brick)) {

        float _topDistance = abs(_ballBounds.top + _ballBounds.height - _brickBounds.top);
        float _bottomDistance = abs(_ballBounds.top - (_brickBounds.height + _brickBounds.top));
        float _rightDistance = abs(_ballBounds.left - (_brickBounds.left + _brickBounds.width));
        float _leftDistance = abs(_ballBounds.left + _ballBounds.width - _brickBounds.left);

        float _shortestDistance = std::min({ _topDistance, _bottomDistance, _leftDistance, _rightDistance });

        if (_shortestDistance == _topDistance || _shortestDistance == _bottomDistance) {
            SetMoveDirection(sf::Vector2f(GetMoveDirection().x, -GetMoveDirection().y));
        }
        else if (_shortestDistance == _leftDistance || _shortestDistance == _rightDistance) {
            SetMoveDirection(sf::Vector2f(-GetMoveDirection().x, GetMoveDirection().y));
        }

        _hasCollidedWithBrick = true;
        _bricksCollided.push_back(brick);

        brick->TakeDamages(_ballDamages);
   
    }

}

void Ball::ResetBricksCollisions() {

    _hasCollidedWithBrick = false;
    _bricksCollided.clear();
}