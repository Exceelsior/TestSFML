#include "Canon.h"

Canon::Canon(sf::Vector2f position, sf::Vector2f size) : Entity(position.x, position.y) {

    _size = size;
    _shape = new sf::RectangleShape(_size);
    _shape->setFillColor(sf::Color(0, 165, 255, 255)); //Pimp my canon
    _shape->setOrigin(_shape->getLocalBounds().width / 2, _shape->getLocalBounds().height / 2);
    SetPosition(position); //Méthode de la classe mère Entity !

}