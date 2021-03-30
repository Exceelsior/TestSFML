#include "Brick.h"

void Brick::ActualizeColors() {

    switch (_life) {
    case(1):
        _shape->setFillColor(sf::Color::White);
        break;
    case(2):
        _shape->setFillColor(sf::Color::Yellow);
        break;
    case(3):
        _shape->setFillColor(sf::Color(255, 165, 0, 255));
        break;
    default:
        _shape->setFillColor(sf::Color::Red);
        break;
    }
}



Brick::Brick(sf::Vector2f position, sf::Vector2f size, int life) : Entity(position.x, position.y) {

    _size = size;
    _life = life;
    _shape = new sf::RectangleShape(_size);
    ActualizeColors();
    _shape->setOutlineThickness(2);
    _shape->setOutlineColor(sf::Color::Black);
    _shape->setOrigin(0, 0);
    SetPosition(position); //Méthode de la classe mère Entity

}


void Brick::TakeDamages(float damages) {
    
    _life -= damages;
    ActualizeColors();
    if (_life <= 0) {
        _hasBeenDestroyed = true;
    }
}