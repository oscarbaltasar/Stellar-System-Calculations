#pragma once
#include "common.h"
#include "camera.h"
#include "../User.h"

class CameraUser: public Camera{
public:
	virtual void step() override;
	User* user;
	float pitch = 0, yaw = 0;
	CameraUser(glm::vec3 pos, glm::vec3 lookAt, cameraType_e type, User* user) :Camera(pos, lookAt, type) { this->user = user; user->CalculateScaledPositions(&this->position.x, &this->position.y, &this->position.z);};

};
