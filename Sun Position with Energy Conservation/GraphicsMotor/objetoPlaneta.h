#pragma once
#include "object.h"
#include "../Planet.h"
#include "../Satelite.h"
#include "../Sun.h"

class StellarObject : public Object {


public:


	StellarObject(std::string fileName, std::string textureFileName) :Object(fileName, textureFileName) { typeObject = CUBE_OBJ; };
	virtual void step() override;
	Planet* referencePlanet;
	Satelite* referenceSatelite;
	Sun* referenceSun;
	void setupReferencePlanet(Planet* planet);
	void setupReferenceSatelite(Satelite* satelite);
	void setupReferenceSun(Sun* sun);
};

