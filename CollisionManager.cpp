#include "CollisionManager.h"

CollisionManager::CollisionManager(float bordersWidth, float bordersHeight) {
	
	_bordersWidth = bordersWidth;
	_bordersHeight = bordersHeight;
}

bool CollisionManager::ManageCollision(std::vector <Entity>& entities) {

	for (int i = 0; entities.size(); i++) {

		if (entities[i].GetPosition().x - entities[i].GetShape()->getGlobalBounds().width/2 < 0) {
			entities[i].SetSpeedDirection(sf::Vector2f(-entities[i].GetSpeedDirection().x, entities[i].GetSpeedDirection().y));
		}

		if (entities[i].GetPosition().x + entities[i].GetShape()->getGlobalBounds().width/2 > _bordersWidth) {
			entities[i].SetSpeedDirection(sf::Vector2f(-entities[i].GetSpeedDirection().x, entities[i].GetSpeedDirection().y));
		}

		if (entities[i].GetPosition().y - entities[i].GetShape()->getGlobalBounds().height/2 < 0) {
			entities[i].SetSpeedDirection(sf::Vector2f(-entities[i].GetSpeedDirection().x, entities[i].GetSpeedDirection().y));
		}

		if (entities[i].GetPosition().y > _bordersHeight) {
			entities[i].SetPosition(sf::Vector2f(_bordersWidth / 2, _bordersHeight));
			return true;
		}
	}

	return false;
}