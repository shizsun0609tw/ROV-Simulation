#include "WindowManagement.h"

WindowManagement::WindowManagement()
{
}

WindowManagement::~WindowManagement()
{
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

int WindowManagement::displayMode;
int WindowManagement::controlMode;	
int WindowManagement::lightMode;
Scene WindowManagement::myScene;
ROV WindowManagement::myROV;
JellyFish WindowManagement::myJellyFish;

bool WindowManagement::init(int w, int h) {
	// glfw init
	GLuint err = glfwInit();
	if (err != GLFW_TRUE) {
		cout << err << endl;
		getchar();
		return false;
	}
	// window init
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	_var::width = w; _var::height = h;
	window = glfwCreateWindow(_var::width, _var::height, "ROV simulation", NULL, NULL);
	glfwMakeContextCurrent(window);
	// glew init
	glewExperimental = GL_TRUE;
	err = glewInit();
	if (err != GLEW_OK) {
		cout << glewGetErrorString(err) << endl;
		getchar();
		return false;
	}

	draw::init();
	texture::init();
	_var::init();

	myROV.init();
	myScene.init();
	myJellyFish.init();


	displayMode = DISPLAY_MODE0;
	controlMode = CONTROL_EYE;
	lightMode = DIRECIONAL_LIGHT;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	return (window == NULL ? false : true);
}

void WindowManagement::setCallbackFunction() {
	glfwSetErrorCallback(error_callback);
	glfwSetKeyCallback(window, key_callback);
}

void WindowManagement::mainLoop() {
	while (!glfwWindowShouldClose(window)) {
		glfwGetFramebufferSize(window, &_var::width, &_var::height);
		glClearColor(0.0f, 0.0f, 0.0f, 0.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		display();

		glfwPollEvents();
		glfwSwapBuffers(window);
	}
}

void WindowManagement::error_callback(int error, const char * description)
{
	cout << "Error: " << description << endl;
}

void WindowManagement::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
	if (action == GLFW_RELEASE) return;
	switch (controlMode) {
	case CONTROL_EYE:
		switch (key) {
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, GLFW_TRUE);
			break;
		case GLFW_KEY_W:
			_var::myEye.eye_fi += (_var::myEye.eye_fi <= 84.f ? 5.f : 0.f);
			break;
		case GLFW_KEY_A:
			_var::myEye.eye_theta -= (_var::myEye.eye_theta >= -360.f ? 5.f : 0.f);
			break;
		case GLFW_KEY_S:
			_var::myEye.eye_fi -= (_var::myEye.eye_fi >= 5.f ? 5.f : 0.f);
			break;
		case GLFW_KEY_D:
			_var::myEye.eye_theta += (_var::myEye.eye_theta <= 360.f ? 5.f : 0.f);
			break;
		case GLFW_KEY_Q:
			_var::myEye.d += (_var::myEye.d <= 300.f ? 5.f : 0.f);
			break;
		case GLFW_KEY_E:
			_var::myEye.d -= (_var::myEye.d >= 6.f ? 5.f : 0.f);
			break;
		case GLFW_KEY_2:
			controlMode = CONTROL_ROV;
			cout << "Control Mode Change: ROV" << endl;
			break;
		case GLFW_KEY_3:
			controlMode = CONTROL_LIGHT;
			cout << "Control Mode Change: LIGHT" << endl;
			break;
		case GLFW_KEY_M:
			changeDisplayMode();
			break;
		case GLFW_KEY_V:
			_var::myEye.changeMode();
			break;
		default:
			break;
		}
		break;
	case CONTROL_ROV:
		switch (key) {
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, GLFW_TRUE);
			break;
		case GLFW_KEY_W:
			myROV.translate(glm::vec3(0.f, 0.f, -1.f));
			myROV.setKey(KEY_W);
			break;
		case GLFW_KEY_A:
			myROV.translate(glm::vec3(-1.f, 0.f, 0.f));
			myROV.setKey(KEY_A);
			break;
		case GLFW_KEY_S:
			myROV.translate(glm::vec3(0.f, 0.f, 1.f));
			myROV.setKey(KEY_S);
			break;
		case GLFW_KEY_D:
			myROV.translate(glm::vec3(1.f, 0.f, 0.f));
			myROV.setKey(KEY_D);
			break;
		case GLFW_KEY_Q:
			myROV.translate(glm::vec3(0.f, 1.f, 0.f));
			myROV.setKey(KEY_Q);
			break;
		case GLFW_KEY_E:
			myROV.translate(glm::vec3(0.f, -1.f, 0.f));
			myROV.setKey(KEY_E);
			break;
		case GLFW_KEY_R:
			myROV.rotate(glm::vec3(0.f, 0.f, 1.f), (mods == GLFW_MOD_SHIFT ? 5.f : -5.f));
			break;
		case GLFW_KEY_Y:
			myROV.rotate(glm::vec3(0.f, 1.f, 0.f), (mods == GLFW_MOD_SHIFT ? 5.f : -5.f));		
			break;
		case GLFW_KEY_P:
			myROV.rotate(glm::vec3(1.f, 0.f, 0.f), (mods == GLFW_MOD_SHIFT ? -5.f : 5.f));	
			break;
		case GLFW_KEY_1:
			controlMode = CONTROL_EYE;
			cout << "Control Mode Change: EYE" << endl;
			break;
		case GLFW_KEY_3:
			controlMode = CONTROL_LIGHT;
			cout << "Control Mode Change: LIGHT" << endl;
			break;
		case GLFW_KEY_M:
			changeDisplayMode();
			break;
		case GLFW_KEY_V:
			_var::myEye.changeMode();
			break;
		default:
			break;
		}
		break;
	case CONTROL_LIGHT:
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, GLFW_TRUE);
			break;
		case GLFW_KEY_D:
			lightMode = DIRECIONAL_LIGHT;
			cout << "    Directional Light selected" << endl;
			break;
		case GLFW_KEY_S:
			lightMode = ROV_LIGHT;
			cout << "    Spot Light selected" << endl;
			break;
		case GLFW_KEY_P:
			lightMode = POINT_LIGHT;
			cout << "    Point Light selected" << endl;
			break;
		case GLFW_KEY_R:
			Light::changeLightColor(lightMode, red);
			break;
		case GLFW_KEY_G:
			Light::changeLightColor(lightMode, green);
			break;
		case GLFW_KEY_B:
			Light::changeLightColor(lightMode, blue);
			break;
		case GLFW_KEY_W:
			Light::changeLightColor(lightMode, white);
			break;
		case GLFW_KEY_KP_0:
			Light::changeLightState(lightMode); 
			break;
		case GLFW_KEY_1:
			controlMode = CONTROL_EYE;
			cout << "Control Mode Change: EYE" << endl;
			break;
		case GLFW_KEY_2:
			controlMode = CONTROL_ROV;
			cout << "Control Mode Change: ROV" << endl;
			break;
		case GLFW_KEY_M:
			changeDisplayMode();
			break;
		case GLFW_KEY_V:
			_var::myEye.changeMode();
			break;
		default:
			break;
		}
	default:
		break;
	}
}

void WindowManagement::changeDisplayMode() {
	switch (displayMode) {
	case DISPLAY_MODE0:
		displayMode = DISPLAY_MODE1;
		break;
	case DISPLAY_MODE1:
		displayMode = DISPLAY_MODE2;
		break;
	case DISPLAY_MODE2:
		displayMode = DISPLAY_MODE3;
		break;
	case DISPLAY_MODE3:
		displayMode = DISPLAY_MODE4;
		break;
	case DISPLAY_MODE4:
		displayMode = DISPLAY_MODE0;
		break;
	default:
		break;
	}
}

void WindowManagement::display() {
	float wRation, hRation;
	int width = _var::width, height = _var::height;
	if (width > height) {
		wRation = 1;
		hRation = (float)height / width;
	}
	else {
		hRation = 1;
		wRation = (float)width / height;
	}

	calViewProjcetMatrix();	// Cal View Projection matrix and update eye position

	switch (displayMode) {
	case DISPLAY_MODE0:
		// LB window
		glViewport(0, 0, width / 2, height / 2);
		_var::myViewMatrix = glm::lookAt(glm::vec3(terrainWidth, 0.f, 0.f), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
		_var::myProjectionMatrix = glm::ortho(-terrainWidth / 2 * wRation, terrainWidth / 2 * wRation, 
												-100 * hRation, 100 * hRation, 0.f, 2 * terrainHeight);
		myROV.draw();
		myJellyFish.draw();
		myScene.draw();
		// RB window
		glViewport(width / 2, 0, width / 2, height / 2);
		_var::myViewMatrix = glm::lookAt(glm::vec3(0, 100.f, 0.f), glm::vec3(0, 0, 0), glm::vec3(-1, 0, 0));
		_var::myProjectionMatrix = glm::ortho(-terrainWidth * wRation, terrainWidth * wRation, 
												-terrainHeight * hRation, terrainHeight * hRation, 0.f, 100 + terrainDepth);
		myROV.draw();
		myJellyFish.draw();
		myScene.draw();
		// LT window
		glViewport(0, height / 2, width / 2, height / 2);
		_var::myViewMatrix = glm::lookAt(glm::vec3(0, 0, terrainHeight), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
		_var::myProjectionMatrix = glm::ortho(-terrainWidth / 2 * wRation, terrainWidth / 2 * wRation,
												-100 * hRation, 100 * hRation, 0.f, 2 * terrainHeight);
		myROV.draw();
		myJellyFish.draw();
		myScene.draw();
		// RT window
		glViewport(width / 2, height / 2, width / 2, height / 2);
		calViewProjcetMatrix();
		myROV.draw();
		myJellyFish.draw();
		myScene.draw();

		break;
	case DISPLAY_MODE1:
		glViewport(0, 0, width, height);
		_var::myViewMatrix = glm::lookAt(glm::vec3(terrainWidth, 0.f, 0.f), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
		_var::myProjectionMatrix = glm::ortho(-terrainWidth / 2 * wRation, terrainWidth / 2 * wRation, 
												-100 * hRation, 100 * hRation, 0.f, 2 * terrainHeight);
		myROV.draw();
		myJellyFish.draw();
		myScene.draw();
		break;
	case DISPLAY_MODE2:
		glViewport(0, 0, width, height);
		_var::myViewMatrix = glm::lookAt(glm::vec3(0, 100.f, 0.f), glm::vec3(0, 0, 0), glm::vec3(-1, 0, 0));
		_var::myProjectionMatrix = glm::ortho(-terrainWidth * wRation, terrainWidth * wRation, 
												-terrainHeight * hRation, terrainHeight * hRation, 0.f, 100 + terrainDepth);
		myROV.draw();
		myJellyFish.draw();
		myScene.draw();
		break;
	case DISPLAY_MODE3:
		glViewport(0, 0, width, height);
		_var::myViewMatrix = glm::lookAt(glm::vec3(0, 0, terrainHeight), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
		_var::myProjectionMatrix = glm::ortho(-terrainWidth / 2 * wRation, terrainWidth / 2 * wRation, 
												-100 * hRation, 100 * hRation, 0.f, 2 * terrainHeight);
		myROV.draw();
		myJellyFish.draw();
		myScene.draw();
		break;
	case DISPLAY_MODE4:
		glViewport(0, 0, width, height);
		calViewProjcetMatrix();
		myROV.draw();
		myJellyFish.draw();
		myScene.draw();
		break;
	default:
		break;
	}
}

void WindowManagement::calViewProjcetMatrix() {
	glm::mat4 transform = glm::mat4(1.f);
	glm::vec4 eye_position = glm::vec4(0.f, 0.f, 0.f, 1.f);

	transform = glm::rotate(transform, glm::radians(_var::myEye.eye_theta), glm::vec3(0.f, 1.f, 0.f));
	transform = glm::rotate(transform, glm::radians(_var::myEye.eye_fi), glm::vec3(0.f, 0.f, 1.f));
	transform = glm::translate(transform, glm::vec3(_var::myEye.d, 0.f, 0.f));
	_var::myEye.pos = transform * eye_position;

	_var::myViewMatrix = glm::lookAt(_var::myEye.pos, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	_var::myProjectionMatrix = glm::perspective(glm::radians(_var::myEye.fovy), (float)_var::width / (float)_var::height, 
												viewVolumnNear, viewVolumnFar);
}