#pragma once

#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "ROV.h"
#include "Scene.h"
#include "_var.h"
#include "draw.h"
#include "texture.h"
#include "Light.h"
#include "JellyFish.h"

class WindowManagement
{
public:
	WindowManagement();
	~WindowManagement();

	bool init(int w, int h);
	void setCallbackFunction();
	void mainLoop();
	void display();
private:
	static int displayMode;
	static int controlMode;
	static int lightMode;
	static Scene myScene;
	static ROV myROV;
	static JellyFish myJellyFish;
	GLFWwindow *window;

	void calViewProjcetMatrix();
	static void changeDisplayMode();
	static void error_callback(int error, const char * description);
	static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
};