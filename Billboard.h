#pragma once

#include "texture.h"
#include "Definition.h"
#include "_var.h"
#include "draw.h"
#include "shader.h"
#include <cmath>
#include <stack>
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

struct billboard {
	float w;
	float h;
	float pos[3];
	float axisA[3];
	float axisB[3];
	float axisC[3];

	float vec[4][3];
};

class Billboard
{
public:
	Billboard();
	~Billboard();
	void draw();
	void move();
private:
	stack<glm::mat4>modelMatrix;
	billboard fish[FISH_NUM], grass[GRASS_NUM];
	billboard calBillboard(float pos[], float w, float h);
	shader myShader;
};

