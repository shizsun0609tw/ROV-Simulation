#pragma once

#include "Definition.h"
#include "shader.h"
#include "_var.h"
#include "draw.h"
#include "light.h"
#include "Scene.h"
#include <stack>
#include <string>
#include <glm/gtc/type_ptr.hpp>

class ROV
{
public:
	ROV();
	~ROV();
	void init();
	void draw();
	void translate(glm::vec3 vector);
	void rotate(glm::vec3 axis, float angle);
	void setKey(int key);
private:
	glm::vec3 center, rotateAngle;
	glm::vec3 moveX, moveY, moveZ;
	glm::vec3 size;
	glm::mat4 rotateMtx;
	int key;
	stack<glm::mat4> modelMatrix;
	float blade_angle, light_angle;
	shader myShader;

	void update();
	void collisionDetect();
};

