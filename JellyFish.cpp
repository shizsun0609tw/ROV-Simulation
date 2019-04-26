#include "JellyFish.h"



JellyFish::JellyFish()
{
}


JellyFish::~JellyFish()
{
}

void JellyFish::init() {
	for (int i = 0; i < JELLYFISH_NUM; i++) {
		position[i] = glm::vec3(rand() % ((int)(terrainWidth - 10) / 2) - rand() % ((int)(terrainWidth - 10) / 2),
			rand() % (int)(terrainDepth - 3) - rand() % (int)(terrainDepth - 3),
			rand() % ((int)(terrainHeight - 10) / 2) - rand() % ((int)(terrainHeight - 10) / 2));
		originSize[i] = glm::vec3((double)rand() * 3 / RAND_MAX + 2);
		size[i] = originSize[i];
		color[i] = blue;
		animStart[i] = chrono::steady_clock::now();
		animDuration[i] = chrono::duration<float>((float)(rand() % (5 * 1000) + 5 * 1000) / 1000);
		state[i] = (rand() % 2 == 0 ? MOVE : REST);
		angle[i] = glm::vec3(rand() % 360, rand() % 360, rand() % 360);
		updateRotate(i);
		updateCollision(i);
		if (state[i] == COLLISION)i--;	// if init position is collision obstacle, it will re-init
		isEmission[i] = false;
	
	}

	myShader = shader("shader.vert", "shader.frag");
	glUseProgram(myShader.shaderProgram);
}

void JellyFish::draw() {
	// paint light
	static Light myLight;
	myLight.paint(myShader);

	draw::changeMaterial(perl, myShader);
	glUniformMatrix4fv(glGetUniformLocation(myShader.shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(_var::myViewMatrix));
	glUniformMatrix4fv(glGetUniformLocation(myShader.shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(_var::myProjectionMatrix));
	glUniform1f(glGetUniformLocation(myShader.shaderProgram, "useTexture"), 0.7f);

	/* draw fish */
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, texture::myTexture[82]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.3f);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	for (int i = 0; i < JELLYFISH_NUM; i++) {
		update(i);

		modelMatrix.push(glm::mat4(1.f));
		modelMatrix.top() = glm::translate(modelMatrix.top(), position[i]);
		modelMatrix.top() = modelMatrix.top() * rotate[i];
		modelMatrix.top() = glm::scale(modelMatrix.top(), size[i]);
		if (isEmission[i] == true) {
			glUniform3fv(glGetUniformLocation(myShader.shaderProgram, "myMaterial.emission"), 1, glm::value_ptr(color[i] * 0.75f));
		}
		isEmission[i] = false;
		glUniformMatrix4fv(glGetUniformLocation(myShader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix.top()));
		glUniform4fv(glGetUniformLocation(myShader.shaderProgram, "color"), 1, glm::value_ptr(color[i]));
		draw::drawSphere();
		glUniform3fv(glGetUniformLocation(myShader.shaderProgram, "myMaterial.emission"), 1, glm::value_ptr(glm::vec3(0.f)));
		modelMatrix.pop();
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	modelMatrix.empty();
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glUniform1f(glGetUniformLocation(myShader.shaderProgram, "useTexture"), 0.f);
	draw::changeMaterial(no_mat, myShader);
}

void JellyFish::update(int i) {
	updateState(i);
	updatePos(i);
	updateAnim(i);
	updateColor(i);
	updateCollision(i);
}

void JellyFish::updateColor(int i) {
	float distance;
	int label = 0;
	for (int num = 0; num < 6; num++) {
		distance = glm::dot(_var::myEye.planeNormal[num], (position[i] - _var::myEye.checkPoint[num]));
		if (distance > originSize[i].x) {
			label = 1;
			break;
		}
		else if (distance <= originSize[i].x / 2 && distance >= -originSize[i].x / 2) {
			label = 2;
		}
	}

	if (label == 0) color[i] = blue;		// Inside
	else if (label == 1) color[i] = red;	// Outside
	else if (label == 2) color[i] = green;	// Intersect
}

void JellyFish::updateAnim(int i) {
	chrono::duration<float> time = chrono::duration_cast<chrono::duration<float>>(chrono::steady_clock::now() - animStart[i]);

	size[i].x = (sin((time.count() / (animDuration[i].count()) / 180) * PI / 180) + 1) * originSize[i].x;
	size[i].y = size[i].x;
	size[i].z = (cos((time.count() / (animDuration[i].count() / 180) - 90) * PI / 180) + 1) * originSize[i].z;
}

void JellyFish::updateState(int i) {
	chrono::duration<float> time = chrono::duration_cast<chrono::duration<float>>(chrono::steady_clock::now() - animStart[i]);

	if (time.count() > animDuration[i].count()) {
		animStart[i] = chrono::steady_clock::now();
		animDuration[i] = chrono::duration<float>((float)(rand() % (10 * 1000) + 5 * 1000) / 1000);
	}

	if (state[i] == COLLISION) {
		return;
	}
	else if (time.count() * 2 > animDuration[i].count()) {
		state[i] = REST;
	}
	else {
		state[i] = MOVE;
	}
}

void JellyFish::updatePos(int i) {
	switch (state[i])
	{
	case MOVE:
		position[i] += glm::vec3(rotate[i] * glm::vec4(0.f, 0.f, -1.f, 0.f)) * 0.2f;
		break;
	case REST:
		position[i] += glm::vec3(rotate[i] * glm::vec4(0.f, 0.f, -1.f, 0.f)) * 0.05f;
		break;
	case COLLISION:
		position[i] -= glm::vec3(rotate[i] * glm::vec4(0.f, 0.f, -1.f, 0.f)) * 0.5f;
		angle[i].y += 180;
		updateRotate(i);
		position[i] += glm::vec3(rotate[i] * glm::vec4(0.f, 0.f, -1.f, 0.f)) * 0.5f;
		break;
	default:
		break;
	}
}

void JellyFish::updateCollision(int i) {
	// if collision another jelly fish, it will emission
	for (int count = i + 1; count < JELLYFISH_NUM; count++) {
		if (glm::distance(position[i], position[count]) < size[i].x + size[count].x) {
			isEmission[i] = true;
			isEmission[count] = true;
		}
	}

	if (position[i].x + size[i].x > terrainWidth * 0.5f || position[i].x - size[i].x < -terrainWidth * 0.5f
		|| position[i].y + size[i].y > terrainDepth || position[i].y - size[i].y < -terrainDepth
		|| position[i].z + size[i].z > terrainHeight * 0.5f || position[i].z - size[i].z < -terrainHeight * 0.5f) {
		state[i] = COLLISION;
		return;
	}

	for (int count = 0; count < OBSTACLE_NUM; count++) {
		glm::vec3 oPos = Scene::getObstaclePos(count);
		glm::vec3 oSize = Scene::getObstacleSize(count);

		if (((position[i].x + size[i].x <= oPos.x + oSize.x * 0.5f && position[i].x + size[i].x >= oPos.x - oSize.x * 0.5f)
				|| (position[i].x - size[i].x <= oPos.x + oSize.x * 0.5f && position[i].x - size[i].x >= oPos.x - oSize.x * 0.5f))
			&& ((position[i].y + size[i].y <= oPos.y + oSize.y * 0.5f && position[i].y + size[i].y >= oPos.y - oSize.y * 0.5f)
				|| (position[i].y - size[i].y <= oPos.y + oSize.y * 0.5f && position[i].y - size[i].y >= oPos.y - oSize.y * 0.5f))
			&& ((position[i].z + size[i].z <= oPos.z + oSize.z * 0.5f && position[i].z + size[i].z >= oPos.z - oSize.z * 0.5f) 
				|| (position[i].z - size[i].z <= oPos.z + oSize.z * 0.5f && position[i].z - size[i].z >= oPos.z - oSize.z * 0.5f))){
			state[i] = COLLISION;
			return;
		}
	}

	state[i] = REST;
}

void JellyFish::updateRotate(int i) {
	glm::mat4 temp(1.f);
	temp = glm::rotate(temp, glm::radians(angle[i].x), glm::vec3(1.f, 0.f, 0.f));
	temp = glm::rotate(temp, glm::radians(angle[i].y), glm::vec3(0.f, 1.f, 0.f));
	temp = glm::rotate(temp, glm::radians(angle[i].z), glm::vec3(0.f, 0.f, 1.f));
	rotate[i] = temp;
}
