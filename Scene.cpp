#include "Scene.h"



Scene::Scene()
{
}


Scene::~Scene()
{
}

void Scene::init() {
	myShader = shader("shader.vert", "shader.frag");
	glUseProgram(myShader.shaderProgram);
}

void Scene::draw() {
	glUniformMatrix4fv(glGetUniformLocation(myShader.shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(_var::myViewMatrix));
	glUniformMatrix4fv(glGetUniformLocation(myShader.shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(_var::myProjectionMatrix));
	glUniform1f(glGetUniformLocation(myShader.shaderProgram, "useTexture"), 1.f);
	
	// paint light
	static Light myLight;
	myLight.paint(myShader);

	// ground
	draw::changeMaterial(whitePlastic, myShader);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture::myTexture[1]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	modelMatrix.push(glm::mat4(1.f));
	modelMatrix.top() = glm::translate(modelMatrix.top(), glm::vec3(0.f, -terrainDepth, 0.f));
	modelMatrix.top() = glm::translate(modelMatrix.top(), glm::vec3(-terrainHeight / 2, 0.f, -terrainWidth / 2));
	for (int i = 0; i <= terrainHeight / 5; i++) {
		for (int j = 0; j <= terrainWidth / 5; j++) {
			modelMatrix.push(modelMatrix.top());
			modelMatrix.top() = glm::translate(modelMatrix.top(), glm::vec3(i * 5.f, 0.f, j * 5.f));
			modelMatrix.top() = glm::scale(modelMatrix.top(), glm::vec3(4.9f, 0.1f, 4.9f));
				glUniformMatrix4fv(glGetUniformLocation(myShader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix.top()));
				glUniform4fv(glGetUniformLocation(myShader.shaderProgram, "color"), 1, glm::value_ptr(yellow));
				draw::drawCube();
			modelMatrix.pop();
		}
	}
	modelMatrix.pop();
	modelMatrix.empty();
	draw::changeMaterial(no_mat, myShader);

	// obstacle
	draw::changeMaterial(whitePlastic, myShader);
	glBindTexture(GL_TEXTURE_2D, texture::myTexture[0]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	for (int i = 0; i < OBSTACLE_NUM; i++) {
		modelMatrix.push(glm::mat4(1.f));
		modelMatrix.top() = glm::translate(modelMatrix.top(), obstaclePosition[i]);
		modelMatrix.top() = glm::scale(modelMatrix.top(),	obstacleSize[i]);
			glUniformMatrix4fv(glGetUniformLocation(myShader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix.top()));
			glUniform4fv(glGetUniformLocation(myShader.shaderProgram, "color"), 1, glm::value_ptr(rock));
			draw::drawCube();
		modelMatrix.pop();
	}
	modelMatrix.empty();
	draw::changeMaterial(no_mat, myShader);

	// billboard
	static Billboard myBillboard;
	myBillboard.draw();
	
	// lamp
	draw::changeMaterial(silver, myShader);
	glBindTexture(GL_TEXTURE_2D, texture::myTexture[2]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	modelMatrix.push(glm::mat4(1.f));
	modelMatrix.top() = glm::translate(modelMatrix.top(), lampPosition);
	modelMatrix.push(modelMatrix.top());
	modelMatrix.top() = glm::scale(modelMatrix.top(), lampSize);
		glUniformMatrix4fv(glGetUniformLocation(myShader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix.top()));
		draw::drawCube();
	modelMatrix.pop();
	modelMatrix.top() = glm::translate(modelMatrix.top(), glm::vec3(0.f, 20.f, 0.f));
	modelMatrix.top() = glm::scale(modelMatrix.top(), glm::vec3(4.f, 4.f, 4.f));
	glBindTexture(GL_TEXTURE_2D, texture::myTexture[3]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		draw::changeMaterial(brass, myShader);
		glUniformMatrix4fv(glGetUniformLocation(myShader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix.top()));
		if (Light::getPointLightState() == LIGHT_ON) {
			glUniform3fv(glGetUniformLocation(myShader.shaderProgram, "myMaterial.emission"), 1, glm::value_ptr(Light::getPointLightColor()));
		}
		else {
			glUniform3fv(glGetUniformLocation(myShader.shaderProgram, "myMaterial.emission"), 1, glm::value_ptr(glm::vec3(0.f)));
		}
		draw::drawCube();
		glUniform3fv(glGetUniformLocation(myShader.shaderProgram, "myMaterial.emission"), 1, glm::value_ptr(glm::vec3(0.f)));
	modelMatrix.pop();
	modelMatrix.empty();

	// draw view volumn
	_var::myEye.draw(_var::myViewMatrix, _var::myProjectionMatrix, _var::width, _var::height);

	glDisable(GL_TEXTURE_2D);
	glUniform1f(glGetUniformLocation(myShader.shaderProgram, "useTexture"), 0.f);
	draw::changeMaterial(no_mat, myShader);
}

glm::vec3 Scene::getObstaclePos(int i) {
	return obstaclePosition[i];
}

glm::vec3 Scene::getObstacleSize(int i) {
	return obstacleSize[i];
}

const glm::vec3 Scene::obstaclePosition[3] = { 
	glm::vec3(15.f, -20.f, -25.f), 
	glm::vec3(-30.f, -20.f, 50.f), 
	glm::vec3(-35.f, 0.f, -20.f) 
};
const glm::vec3 Scene::obstacleSize[3] = { 
	glm::vec3(10.f, 20.f, 20.f),
	glm::vec3(20.f, 20.f, 40.f), 
	glm::vec3(40.f, 60.f, 50.f)
};
const glm::vec3 Scene::lampPosition(20.f, -10.f, 20.f);
const glm::vec3 Scene::lampSize(1.f, 40.f, 1.f);