#pragma once
#include "object.h"

class Background: public Object{

	
public:
	glm::vec2 scroll = glm::vec2(0,0);

	Background():Object(){};
        Background(std::string fileName, std::string textureFileName):Object(fileName, textureFileName){typeObject=BACKGROUND_OBJ;};
	virtual void step() override;
};

