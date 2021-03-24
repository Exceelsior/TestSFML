#pragma once
#include <vector>
#include "Entity.h"
#include "Utils.h"

class CollisionManager {

private:

	float _bordersWidth;
	float _bordersHeight;


public:
	
	//Constructeur
	CollisionManager(float bordersWidth, float bordersHeight);

	bool ManageCollision(std::vector <Entity>& entities);
};