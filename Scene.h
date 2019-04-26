#pragma once

#include "Definition.h"
#include "Light.h"
#include "shader.h"
#include "_var.h"
#include "draw.h"
#include "Billboard.h"
#include "texture.h"
#include <glm/gtc/type_ptr.hpp>
#include <stack>

class Scene
{
public:
	Scene();
	~Scene();
	void init();
	void draw();
	static glm::vec3 getObstaclePos(int i);
	static glm::vec3 getObstacleSize(int i);
private:
	stack<glm::mat4> modelMatrix;
	shader myShader;
	const static glm::vec3 obstaclePosition[3];
	const static glm::vec3 obstacleSize[3];
	const static glm::vec3 lampPosition;
	const static glm::vec3 lampSize;
};

