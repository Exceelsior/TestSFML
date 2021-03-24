#pragma once
#include "SFML/Graphics.hpp"

class Utils {

public:

	const static int _width = 480;
	const static int _height = 720;

	float GetXR2P(float ERatioX) { return ERatioX * _width; }; //renvoie la position absolue en pixels de la position relative (à l'écran) de l'entity 
	float GetYR2P(float ERatioY) { return ERatioY * _height; }; //idem avec Y
	
};