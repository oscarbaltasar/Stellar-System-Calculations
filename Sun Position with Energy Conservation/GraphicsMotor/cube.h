#pragma once
#include "object.h"


class Cube: public Object{
public:
	Cube(std::string fileName, std::string textureFileName):Object(fileName, textureFileName){typeObject=CUBE_OBJ;};
	virtual void step() override;
};
