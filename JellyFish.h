#pragma once
#include "Definition.h"
#include "shader.h"
#include "_var.h"
#include "draw.h"
#include "Light.h"
#include "texture.h"
#include "Scene.h"
#include <glm/gtc/type_ptr.hpp>
#include <stack>
#include <chrono>
#include <cmath>

#define MOVE 0
#define REST 1
#define COLLISION 2
#define PI 3.14159265

class JellyFish
{
public:
	JellyFish();
	~JellyFish();
	void init();
	void draw();
private:
	stack<glm::mat4> modelMatrix;
	shader myShader;
	int num;
	int state[JELLYFISH_NUM];
	glm::vec3 position[JELLYFISH_NUM];
	glm::vec4 color[JELLYFISH_NUM];
	glm::vec3 originSize[JELLYFISH_NUM];
	glm::vec3 size[JELLYFISH_NUM];
	glm::vec3 angle[JELLYFISH_NUM];
	glm::mat4 rotate[JELLYFISH_NUM];
	bool isEmission[JELLYFISH_NUM];
	chrono::steady_clock::time_point animStart[JELLYFISH_NUM];
	chrono::duration<float> animDuration[JELLYFISH_NUM];

	void update(int i);
	void updateState(int i);
	void updateColor(int i);
	void updateAnim(int i);
	void updatePos(int i);
	void updateCollision(int i);
	void updateRotate(int i);
};