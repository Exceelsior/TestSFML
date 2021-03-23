#pragma once

static class Utils {

private:

	


public:

	int _width = 480;
	int _height = 720;

	float GetXR2P(float ERatioX) { return ERatioX * _width; }; //renvoie la position absolue de la position relative de l'entity 
	float GetXR2P(float ERatioY) { return ERatioY * _height; }; //idem avec Y
};