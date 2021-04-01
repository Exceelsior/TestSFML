#include "Ball.h"
#include <iostream>

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

bool Ball::CheckIfCollidedWithWall(char &wall) {
    if (std::find(_wallsCollided.begin(), _wallsCollided.end(), wall) != _wallsCollided.end()) {
        return true;
    }
    else {
        return false;
    }
}


bool Ball::WallCollisions() {

    bool _hasCollidedIntoWall = false;

    if (GetShape()->getGlobalBounds().left <= 0 && !_hasCollidedIntoWall) {
        _hasCollidedIntoWall = true;
        SetMoveDirection(sf::Vector2f(-GetMoveDirection().x, GetMoveDirection().y));
    }

    else if (GetShape()->getGlobalBounds().width + GetShape()->getGlobalBounds().left >= _windowWidth && !_hasCollidedIntoWall) {
        _hasCollidedIntoWall = true;
        SetMoveDirection(sf::Vector2f(-GetMoveDirection().x, GetMoveDirection().y));
    }

    else if (GetShape()->getGlobalBounds().top <= 0 && !_hasCollidedIntoWall) {
        _hasCollidedIntoWall = true;
        SetMoveDirection(sf::Vector2f(GetMoveDirection().x, -GetMoveDirection().y));
    }

    else if (GetShape()->getGlobalBounds().height + GetShape()->getGlobalBounds().top > _windowHeight && !_hasCollidedIntoWall) {
        _hasCollidedIntoWall = true;
        SetPosition(sf::Vector2f(GetStartPosition()));
        SetMoveDirection(sf::Vector2f(0, 0));
        return true;
    }
    return false;

}

void Ball::BrickCollision(Brick* brick) {


    sf::FloatRect _brickBounds = brick->GetShape()->getGlobalBounds();
    sf::FloatRect _ballBounds = _shape->getGlobalBounds();

    bool _hasCollidedIntoBrick = false;

    if (_ballBounds.intersects(_brickBounds) && !_hasCollidedIntoBrick) {

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

        _hasCollidedIntoBrick = true;

        brick->TakeDamages(_ballDamages);
   
    }
}