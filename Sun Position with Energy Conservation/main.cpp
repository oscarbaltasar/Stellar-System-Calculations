#include <iostream>
#include "GraphicsMotor/common.h"
#include <vector>
#include "GraphicsMotor/mesh.h"
#include "GraphicsMotor/render.h"
#include "GraphicsMotor/object.h"
#include "GraphicsMotor/scene.h"
#include "GraphicsMotor/inputManager.h"
#include "GraphicsMotor/system.h"

#include "GraphicsMotor/cameraUser.h"
#include "GraphicsMotor/objetoPlaneta.h"
#include "GraphicsMotor/cube.h"
#include "GraphicsMotor/background.h"
#include "GraphicsMotor/light.h"
#include "SystemCenter.h"
#include "SystemSimulation.h"



bool renderfps(double framerate)
{
	static double currentTime = 0;
	static double lastTime = 0;

	currentTime = glfwGetTime();
	if (currentTime - lastTime >= 1.0 / framerate)
	{
		lastTime = currentTime;
		return true;
	}
	return false;
}

void stelarSimulationThreaded() {

}

int main(int argc, char** argv)
{
	//Iniciado de simulación estelar
	std::cout << "Iniciando valores\n";
	Satelite* moon = new Satelite("moon", 3.844, 4, 1.7374, 3, 5.14, 6.68, 2358720, 2358720, 0, 0, 0);
	Planet* earth = new Planet("earth", 1.496, 7, 6.378, 3, 0, 23.44, 31558118.4, 86400, 0, 14860800, 0);
	earth->AddSatelite(moon);
	Sun* sun = new Sun(6.9634, 5);
	SystemCenter systemcenter = SystemCenter(0, 0, sun);
	//User* user = new User(-4.064501728800064, 40.71010524106721, 100000000.091, earth);
	User* user = new User(-4.064501728800064, 40.71010524106721, 10000.2, earth);
	SystemSimulation systemSimulation(earth, &systemcenter, user);

	std::cout << "Iniciando simulacion\n";
	systemSimulation.run();


	//std::thread stelarThread(stelarSimulationThreaded);



	int glfwState = glfwInit();
	if (!glfwState)
		std::cout << "ERROR iniciando glfw\n";

	GLFWwindow* window = glfwCreateWindow(1920, 1080, "Prueba 1 GLFW", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);


	int glewState = glewInit();

	if (glewState != GLEW_OK)
		std::cout << "ERROR iniciando glew\n";

	InputManager::init(window);
	Object* sun1 = new StellarObject("GraphicsMotor/sphere.obj", "GraphicsMotor/data/red.png");
	((StellarObject*)(sun1))->setupReferenceSun(sun);
	sun1->position = glm::vec3(0, 0, 0);

	Object* planet1 = new StellarObject("GraphicsMotor/sphere.obj", "GraphicsMotor/data/green.png");
	((StellarObject*)(planet1))->setupReferencePlanet(earth);
	//planet1->scale = glm::vec3(0.1f, 0.1f, 0.1f);

	Object* satelite1 = new StellarObject("GraphicsMotor/sphere.obj", "GraphicsMotor/data/top.png");
	((StellarObject*)(satelite1))->setupReferenceSatelite(moon);
	//satelite1->scale = glm::vec3(50.f, 50.f, 50.f);


	Render* render = new Render();
	Scene* scene = new Scene();
	System::scene = scene;
	//scene->setCamera(new Camera(glm::vec3(0,0,0.5),glm::vec3(0,0,0),perspective));
	Camera* userCamera = new CameraUser(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), perspective, user);
	scene->addLight(new Light(glm::vec4(0, 0, 0, 1), glm::vec4(0, 0, 0, 1)));
	scene->addLight(new Light(glm::vec4(0, 0, 0, 1), glm::vec4(0, 0, 0, 1)));
	scene->setCamera(userCamera);


	scene->addObject(sun1);
	render->setupObject(sun1);
	scene->addObject(planet1);
	render->setupObject(planet1);
	scene->addObject(satelite1);
	render->setupObject(satelite1);

	while (!glfwWindowShouldClose(window))
	{

		if (renderfps(60.0f)) {
			systemSimulation.run();
			scene->step(0.0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			render->drawScene(scene);
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}

	//delete triangle;
	return 0;

}