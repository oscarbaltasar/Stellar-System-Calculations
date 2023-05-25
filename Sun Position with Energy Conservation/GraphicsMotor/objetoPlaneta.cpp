#include "objetoPlaneta.h"

void StellarObject::step()
{
	if (referencePlanet != nullptr) {
		//Calculate position
		referencePlanet->CalculateScaledPositions(&this->position.x, &this->position.y, &this->position.z);
	}
	else if (referenceSatelite != nullptr){
		//Calculate position
		referenceSatelite->CalculateScaledPositions(&this->position.x, &this->position.y, &this->position.z);
	}
	else if (referenceSun != nullptr) {
	}

}

void StellarObject::setupReferencePlanet(Planet* planet)
{
	this->referencePlanet = planet;
	double scaledSize = planet->CalculateScaledRadius();
	this->scale = glm::vec3(scaledSize, scaledSize, scaledSize);
}

void StellarObject::setupReferenceSatelite(Satelite* satelite)
{
	this->referenceSatelite = satelite;
	double scaledSize = satelite->CalculateScaledRadius();
	this->scale = glm::vec3(scaledSize, scaledSize, scaledSize);
}

void StellarObject::setupReferenceSun(Sun* sun)
{
	this->referenceSun = sun;
	double scaledSize = sun->CalculateScaledRadius();
	this->scale = glm::vec3(scaledSize, scaledSize, scaledSize);
}
