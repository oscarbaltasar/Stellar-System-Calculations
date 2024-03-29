#pragma once
#include "common.h"

typedef enum cameraType_e{
	perspective, ortho
}cameraType_e;

class Camera{
protected:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 lookAt;
private:
	glm::mat4 viewMatrix;
	glm::mat4 projMatrix;
	cameraType_e type;
public:
	Camera(glm::vec3 pos, glm::vec3 lookAt, cameraType_e type);
	virtual void step();
	void computeMatrix();
	glm::mat4 getMatrix();
	glm::mat4 getProjectionMatrix();
	glm::vec4 camPos();

};
