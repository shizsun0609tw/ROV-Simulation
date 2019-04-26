#include "Billboard.h"


Billboard::Billboard() {
	float rand_Fpos[FISH_NUM][3], rand_Gpos[GRASS_NUM][3];
	for (int i = 0; i < FISH_NUM; i++) {
		rand_Fpos[i][0] = rand() % ((int)terrainWidth / 2) - rand() % ((int)terrainWidth / 2);
		rand_Fpos[i][1] = rand() % (int)terrainDepth - rand() % (int)terrainDepth;
		rand_Fpos[i][2] = rand() % ((int)terrainHeight / 2)- rand() % ((int)terrainHeight / 2);
		fish[i] = calBillboard(rand_Fpos[i], 10.f, 10.f);
	}
	for (int i = 0; i < GRASS_NUM; i++) {
		rand_Gpos[i][0] = rand() % ((int)terrainWidth / 2) - rand() % ((int)terrainWidth / 2);
		rand_Gpos[i][1] = -15.f;
		rand_Gpos[i][2] = rand() % ((int)terrainHeight / 2) - rand() % ((int)terrainHeight / 2);
		grass[i] = calBillboard(rand_Gpos[i], 10.f, rand() % 40 + 20);
	}
	myShader = shader("shader.vert", "shader.frag");
	glUseProgram(myShader.shaderProgram);
}


Billboard::~Billboard()
{
}

billboard Billboard::calBillboard(float pos[], float w, float h)
{
	float mtx[] = { 
			_var::myViewMatrix[0][0], _var::myViewMatrix[1][0], _var::myViewMatrix[2][0], _var::myViewMatrix[3][0],
			_var::myViewMatrix[0][1], _var::myViewMatrix[1][1], _var::myViewMatrix[2][1], _var::myViewMatrix[3][1], 
			_var::myViewMatrix[0][2], _var::myViewMatrix[1][2], _var::myViewMatrix[2][2], _var::myViewMatrix[3][2], 
			_var::myViewMatrix[0][3], _var::myViewMatrix[1][3], _var::myViewMatrix[2][3], _var::myViewMatrix[3][3] };

	billboard temp;
	temp.pos[0] = pos[0];
	temp.pos[1] = pos[1];
	temp.pos[2] = pos[2];

	float w0 = mtx[2], w2 = mtx[10];
	float len = sqrt(w0 * w0 + w2 * w2);

	temp.axisA[0] = w2 / len;
	temp.axisA[1] = 0.0;
	temp.axisA[2] = -w0 / len;

	temp.axisB[0] = 0.0;
	temp.axisB[1] = 1.0;
	temp.axisB[2] = 0.0;

	temp.axisC[0] = mtx[2];
	temp.axisC[1] = mtx[6];
	temp.axisC[2] = mtx[10];

	temp.w = w;
	temp.h = h;
	// correct?
	temp.vec[0][0] = pos[0] - (w / 2) * temp.axisA[0];
	temp.vec[0][1] = pos[1];
	temp.vec[0][2] = pos[2] - (w / 2) * temp.axisA[2];

	temp.vec[1][0] = pos[0] + (w / 2) * temp.axisA[0];
	temp.vec[1][1] = pos[1];
	temp.vec[1][2] = pos[2] + (w / 2) * temp.axisA[2];

	temp.vec[2][0] = pos[0] + (w / 2) * temp.axisA[0];
	temp.vec[2][1] = pos[1] + h;
	temp.vec[2][2] = pos[2] + (w / 2) * temp.axisA[2];
	
	temp.vec[3][0] = pos[0] - (w / 2) * temp.axisA[0];
	temp.vec[3][1] = pos[1] + h;
	temp.vec[3][2] = pos[2] - (w / 2) * temp.axisA[2];

	return temp;
}

void Billboard::move() {
	static int flag = 0;
	static int rnd = rand() % 50;
	if (flag > rnd) {
		for (int i = 0; i < FISH_NUM; i++) {
			fish[i].pos[0] += ((float)rand() / (RAND_MAX + 1.f) - (float)rand() / (RAND_MAX + 1.f)) / 5;
			fish[i].pos[1] += ((float)rand() / (RAND_MAX + 1.f) - (float)rand() / (RAND_MAX + 1.f)) / 5;
			fish[i].pos[2] += ((float)rand() / (RAND_MAX + 1.f) - (float)rand() / (RAND_MAX + 1.f)) / 5;
			flag = 0;
			rnd = rand() % 50;
		}
	}
	flag++;
}

void Billboard::draw() {
	draw::changeMaterial(perl, myShader);
	glUniformMatrix4fv(glGetUniformLocation(myShader.shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(_var::myViewMatrix));
	glUniformMatrix4fv(glGetUniformLocation(myShader.shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(_var::myProjectionMatrix));
	glUniform1f(glGetUniformLocation(myShader.shaderProgram, "useTexture"), 1.f);

	for (int i = 0; i < FISH_NUM; i++) {
		fish[i] = calBillboard(fish[i].pos, fish[i].w, fish[i].h);
	}
	for (int i = 0; i < GRASS_NUM; i++) {
		grass[i] = calBillboard(grass[i].pos, grass[i].w, grass[i].h);
	}
	/* draw grass */
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, texture::myTexture[13]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.3f);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	for (int i = 0; i < GRASS_NUM; i++) {
		modelMatrix.push(glm::mat4(1.f));
		modelMatrix.top() = glm::translate(modelMatrix.top(), glm::vec3(grass[i].pos[0], grass[i].pos[1], grass[i].pos[2]));
		modelMatrix.top() = glm::rotate(modelMatrix.top(), glm::radians(_var::myEye.eye_theta), glm::vec3(0.f, 1.f, 0.f));
		modelMatrix.top() = glm::scale(modelMatrix.top(), glm::vec3(0.00001f, grass[i].h, grass[i].w));
		glUniformMatrix4fv(glGetUniformLocation(myShader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix.top()));
		draw::drawCube();
		modelMatrix.pop();
	}
	modelMatrix.empty();

	/* draw fish */
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, texture::myTexture[5]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.3f);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	for (int i = 0; i < FISH_NUM; i++) {
		modelMatrix.push(glm::mat4(1.f));
		modelMatrix.top() = glm::translate(modelMatrix.top(), glm::vec3(fish[i].pos[0], fish[i].pos[1], fish[i].pos[2]));
		modelMatrix.top() = glm::rotate(modelMatrix.top(), glm::radians(_var::myEye.eye_theta), glm::vec3(0.f, 1.f, 0.f));
		modelMatrix.top() = glm::scale(modelMatrix.top(), glm::vec3(0.00001f, fish[i].h, fish[i].w));
		glUniformMatrix4fv(glGetUniformLocation(myShader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix.top()));
		draw::drawCube();
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