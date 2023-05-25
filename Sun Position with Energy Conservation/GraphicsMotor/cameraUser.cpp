#include "cameraUser.h"
#include "inputManager.h"

void CameraUser::step()
{
	user->CalculateScaledPositions(&this->position.x, &this->position.y, &this->position.z);
	if (InputManager::keys['F'])
	{
		user->addLatitude(-1.f);
	}

	if (InputManager::keys['H'])
	{
		user->addLatitude(1.f);
	}
	if (InputManager::keys['T'])
	{
		user->addLongitude(1.f);
	}

	if (InputManager::keys['G'])
	{
		user->addLongitude(-1.f);
	}
	if (InputManager::keys['D'])
	{
		pitch -= 1.f;
		if (pitch == 0) pitch = 360;
	}

	if (InputManager::keys['A'])
	{
		pitch += 1.f;
		if (pitch == 360) pitch = 0;
	}
	if (InputManager::keys['S'])
	{
		yaw += 1.f;
		if (yaw == 360) yaw = 0;
	}

	if (InputManager::keys['W'])
	{
		yaw -= 1.f;
		if (yaw == 0) yaw = 360;
	}
	SciNumber auxposX, auxposY, auxposZ;
	SciNumber auxRadius;
	auxRadius.number = 1;
	auxRadius.number_SciPow = 0;
	CommonData::CalculatePositionOnSphere(pitch, yaw, &auxRadius, 0, -1, &auxposX, &auxposY, &auxposZ);
	this->lookAt = glm::vec3(auxposX.number * pow(10, auxposX.number_SciPow) + this->position.x, auxposY.number * pow(10, auxposY.number_SciPow) + this->position.y, auxposZ.number * pow(10, auxposZ.number_SciPow) + this->position.z);
}
