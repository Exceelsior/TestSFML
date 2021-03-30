#include "Ball.h"
#include <iostream>

Ball::Ball(float ballRadius, sf::Vector2f startPosition) : Entity(_startPosition.x, _startPosition.y)
{
    _ballRadius = ballRadius;
    _ballDamages = 1;
    _shape = new sf::CircleShape(_ballRadius);
    _shape->setFillColor(sf::Color(0, 255, 255, 255)); //Pimp my ball
    _startPosition = startPosition;
    _shape->setOrigin(_shape->getLocalBounds().width / 2, _shape->getLocalBounds().height);
    SetPosition(startPosition); //Méthode de la classe mère Entity !
    SetMoveSpeed(500);
    _isReadyToBeLaunched = true;

}

bool Ball::CheckWallCollision() {

    if (GetShape()->getGlobalBounds().left <= 0) {
        SetMoveDirection(sf::Vector2f(-GetMoveDirection().x, GetMoveDirection().y));
    }

    else if (GetShape()->getGlobalBounds().width + GetShape()->getGlobalBounds().left >= _windowWidth) {
        SetMoveDirection(sf::Vector2f(-GetMoveDirection().x, GetMoveDirection().y));
    }

    else if (GetShape()->getGlobalBounds().top <= 0) {
        SetMoveDirection(sf::Vector2f(GetMoveDirection().x, -GetMoveDirection().y));
    }

    else if (GetShape()->getGlobalBounds().height + GetShape()->getGlobalBounds().top > _windowHeight) {

        SetPosition(sf::Vector2f(GetStartPosition()));
        SetMoveDirection(sf::Vector2f(0, 0));
        return true;
    }
    return false;

}

void Ball::BrickCollision(Brick& brick) {

    sf::Shape* _brickShape = brick.GetShape();

    if (_shape->getGlobalBounds().intersects(_brickShape->getGlobalBounds())) {

        std::vector <float> _distances;

        float _topDistance = abs(_shape->getGlobalBounds().top + _shape->getGlobalBounds().height - _brickShape->getGlobalBounds().top);
        float _bottomDistance = abs(_shape->getGlobalBounds().top - (_brickShape->getGlobalBounds().height + _brickShape->getGlobalBounds().top));
        float _rightDistance = abs(_shape->getGlobalBounds().left - (_brickShape->getGlobalBounds().left + _brickShape->getGlobalBounds().width));
        float _leftDistance = abs(_shape->getGlobalBounds().left + _shape->getGlobalBounds().width - _brickShape->getGlobalBounds().left);

        _distances.push_back(_topDistance);
        _distances.push_back(_bottomDistance);
        _distances.push_back(_rightDistance);
        _distances.push_back(_leftDistance);

        float _shortestDistance = std::numeric_limits<float>::infinity();

        for (int i = 0; i < _distances.size(); i++) {
            if (_distances[i] <= _shortestDistance) {
                _shortestDistance = _distances[i];
            }
        }

        if (_shortestDistance == _topDistance || _shortestDistance == _bottomDistance) {
            SetMoveDirection(sf::Vector2f(GetMoveDirection().x, -GetMoveDirection().y));
        }
        else if (_shortestDistance == _leftDistance || _shortestDistance == _rightDistance) {
            SetMoveDirection(sf::Vector2f(-GetMoveDirection().x, GetMoveDirection().y));
        }

        brick.TakeDamages(_ballDamages);
   
    }
}