#include "Ball.h"

Ball::Ball(float ballRadius, sf::Vector2f startPosition) : Entity(_startPosition.x, _startPosition.y)
{
    _ballRadius = ballRadius;
    _shape = new sf::CircleShape(_ballRadius);
    _shape->setFillColor(sf::Color(0, 255, 255, 255)); //Pimp my ball
    _shape->setOrigin(_shape->getLocalBounds().width / 2, _shape->getLocalBounds().height);
    SetPosition(startPosition); //Méthode de la classe mère Entity !
    SetMoveSpeed(500);
    _isReadyToBeLaunched = true;
    
}