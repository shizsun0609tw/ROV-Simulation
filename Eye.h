#pragma once

#include "draw.h"
#include "Shader.h"
#include "Definition.h"
#include <stack>
#include <cmath>
#include <glm/gtc/type_ptr.hpp>

#define PI 3.1415926

class Eye
{
public:
	Eye();
	Eye(float eye_theta, float eye_fi, float d, float fovy, glm::vec3 pos);
	~Eye();
	float eye_theta;
	float eye_fi;
	float d;
	float fovy;
	glm::vec3 LTN, LBN, RBN, RTN, LTF, LBF, RBF, RTF; // view volumn vertex
	glm::vec3 planeNormal[6]; // F, T, L, B, R, B(ack) plane normal 
	glm::vec3 checkPoint[6];  // for cal distance
	glm::vec3 pos;
	glm::vec3 u, v, w;

	void changeMode();
	void draw(glm::mat4 viewMatrix,	glm::mat4 projectionMatrix, float windowWidth, float windowHeight);
private:
	stack<glm::mat4> modelMatrix;
	shader myShader;
	bool enable;

	void update(int windowWidth, int windowHeight);
};

