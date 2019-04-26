#include "Light.h"



Light::Light()
{
	myLight[DIRECIONAL_LIGHT].ambient = glm::vec3(0.35f, 0.35f, 0.35f);
	myLight[DIRECIONAL_LIGHT].diffuse = glm::vec3(0.35f, 0.35f, 0.35f);
	myLight[DIRECIONAL_LIGHT].specular = glm::vec3(0.f, 0.f, 0.f);
	myLight[DIRECIONAL_LIGHT].direction = glm::vec3(0.f, -1.f, 0.f);
	myLight[DIRECIONAL_LIGHT].light_theta = 0.f;
	myLight[DIRECIONAL_LIGHT].light_fi = 0.f;
	myLight[DIRECIONAL_LIGHT].exponent = 8.f;
	myLight[DIRECIONAL_LIGHT].cutoff = 180.f;
	myLight[DIRECIONAL_LIGHT].mode = LIGHT_OFF;

	myLight[POINT_LIGHT].ambient = glm::vec3(0.95f, 0.95f, 0.95f);
	myLight[POINT_LIGHT].diffuse = glm::vec3(0.55f, 0.55f, 0.55f);
	myLight[POINT_LIGHT].specular = glm::vec3(0.f, 0.f, 0.f);
	myLight[POINT_LIGHT].position = glm::vec3(20.f, 10.f, 20.f);
	myLight[POINT_LIGHT].direction = glm::vec3(0.f, 0.f, 0.f);
	myLight[POINT_LIGHT].light_theta = 0.f;
	myLight[POINT_LIGHT].light_fi = 0.f;
	myLight[POINT_LIGHT].exponent = 8.f;
	myLight[POINT_LIGHT].cutoff = 180.f;
	myLight[POINT_LIGHT].mode = LIGHT_OFF;

	myLight[ROV_LIGHT].ambient = glm::vec3(0.05f, 0.05f, 0.05f);
	myLight[ROV_LIGHT].diffuse = glm::vec3(0.95f, 0.95f, 0.95f);
	myLight[ROV_LIGHT].specular = glm::vec3(0.05f, 0.05f, 0.05f);
	myLight[ROV_LIGHT].position = glm::vec3(0.f, 0.f, 0.f);
	myLight[ROV_LIGHT].direction = glm::vec3(0.f, -1.f, -1.f);
	myLight[ROV_LIGHT].light_theta = 0.f;
	myLight[ROV_LIGHT].light_fi = 0.f;
	myLight[ROV_LIGHT].exponent = 10.f;
	myLight[ROV_LIGHT].cutoff = 30.f;
	myLight[ROV_LIGHT].outerCutoff = 50.f;
	myLight[ROV_LIGHT].mode = LIGHT_OFF;
}


Light::~Light()
{
}

light Light::myLight[3];

void Light::paint(shader s) {
	if (myLight[DIRECIONAL_LIGHT].mode == LIGHT_ON) {
		glUniform3fv(glGetUniformLocation(s.shaderProgram, "myDiretionLight.ambient"), 1, glm::value_ptr(myLight[DIRECIONAL_LIGHT].ambient));
		glUniform3fv(glGetUniformLocation(s.shaderProgram, "myDiretionLight.diffuse"), 1, glm::value_ptr(myLight[DIRECIONAL_LIGHT].diffuse));
		glUniform3fv(glGetUniformLocation(s.shaderProgram, "myDiretionLight.specular"), 1, glm::value_ptr(myLight[DIRECIONAL_LIGHT].specular));
		glUniform3fv(glGetUniformLocation(s.shaderProgram, "myDiretionLight.direction"), 1, glm::value_ptr(myLight[DIRECIONAL_LIGHT].direction));
	}
	else {
		glUniform3fv(glGetUniformLocation(s.shaderProgram, "myDiretionLight.ambient"), 1, glm::value_ptr(myLight[DIRECIONAL_LIGHT].ambient));
		glUniform3fv(glGetUniformLocation(s.shaderProgram, "myDiretionLight.diffuse"), 1, glm::value_ptr(noLight));
		glUniform3fv(glGetUniformLocation(s.shaderProgram, "myDiretionLight.specular"), 1, glm::value_ptr(noLight));
		glUniform3fv(glGetUniformLocation(s.shaderProgram, "myDiretionLight.direction"), 1, glm::value_ptr(myLight[DIRECIONAL_LIGHT].direction));
	}
	if (myLight[POINT_LIGHT].mode == LIGHT_ON) {
		glUniform3fv(glGetUniformLocation(s.shaderProgram, "myPointLight.ambient"), 1, glm::value_ptr(myLight[POINT_LIGHT].ambient));
		glUniform3fv(glGetUniformLocation(s.shaderProgram, "myPointLight.diffuse"), 1, glm::value_ptr(myLight[POINT_LIGHT].diffuse));
		glUniform3fv(glGetUniformLocation(s.shaderProgram, "myPointLight.specular"), 1, glm::value_ptr(myLight[POINT_LIGHT].specular));
		glUniform3fv(glGetUniformLocation(s.shaderProgram, "myPointLight.position"), 1, glm::value_ptr(myLight[POINT_LIGHT].position));
		glUniform1f(glGetUniformLocation(s.shaderProgram, "myPointLight.constant"), 1.0f);
		glUniform1f(glGetUniformLocation(s.shaderProgram, "myPointLight.linear"), 0.09f);
	}
	else {
		glUniform3fv(glGetUniformLocation(s.shaderProgram, "myPointLight.ambient"), 1, glm::value_ptr(noLight));
		glUniform3fv(glGetUniformLocation(s.shaderProgram, "myPointLight.diffuse"), 1, glm::value_ptr(noLight));
		glUniform3fv(glGetUniformLocation(s.shaderProgram, "myPointLight.specular"), 1, glm::value_ptr(noLight));	
		glUniform3fv(glGetUniformLocation(s.shaderProgram, "myPointLight.position"), 1, glm::value_ptr(myLight[POINT_LIGHT].position));
		glUniform1f(glGetUniformLocation(s.shaderProgram, "myPointLight.constant"), 1.0f);
		glUniform1f(glGetUniformLocation(s.shaderProgram, "myPointLight.linear"), 0.09f);
	}
	if (myLight[ROV_LIGHT].mode == LIGHT_ON) {
		glUniform3fv(glGetUniformLocation(s.shaderProgram, "mySpotLight.ambient"), 1, glm::value_ptr(myLight[ROV_LIGHT].ambient));
		glUniform3fv(glGetUniformLocation(s.shaderProgram, "mySpotLight.diffuse"), 1, glm::value_ptr(myLight[ROV_LIGHT].diffuse));
		glUniform3fv(glGetUniformLocation(s.shaderProgram, "mySpotLight.specular"), 1, glm::value_ptr(myLight[ROV_LIGHT].specular));
		glUniform3fv(glGetUniformLocation(s.shaderProgram, "mySpotLight.position"), 1, glm::value_ptr(myLight[ROV_LIGHT].position));
		glUniform3fv(glGetUniformLocation(s.shaderProgram, "mySpotLight.direction"), 1, glm::value_ptr(myLight[ROV_LIGHT].direction));
		glUniform1f(glGetUniformLocation(s.shaderProgram, "mySpotLight.cutOff"), glm::cos(glm::radians(20.f)));
		glUniform1f(glGetUniformLocation(s.shaderProgram, "mySpotLight.outerCutOff"), glm::cos(glm::radians(30.f)));
		glUniform1f(glGetUniformLocation(s.shaderProgram, "mySpotLight.constant"), 1.0f);
		glUniform1f(glGetUniformLocation(s.shaderProgram, "mySpotLight.linear"), 0.09f);
	}
	else {
		glUniform3fv(glGetUniformLocation(s.shaderProgram, "mySpotLight.ambient"), 1, glm::value_ptr(noLight));
		glUniform3fv(glGetUniformLocation(s.shaderProgram, "mySpotLight.diffuse"), 1, glm::value_ptr(noLight));
		glUniform3fv(glGetUniformLocation(s.shaderProgram, "mySpotLight.specular"), 1, glm::value_ptr(noLight));
		glUniform3fv(glGetUniformLocation(s.shaderProgram, "mySpotLight.position"), 1, glm::value_ptr(myLight[ROV_LIGHT].position));
		glUniform3fv(glGetUniformLocation(s.shaderProgram, "mySpotLight.direction"), 1, glm::value_ptr(myLight[ROV_LIGHT].direction));
		glUniform1f(glGetUniformLocation(s.shaderProgram, "mySpotLight.cutOff"), glm::cos(glm::radians(10.f)));
		glUniform1f(glGetUniformLocation(s.shaderProgram, "mySpotLight.outerCutOff"), glm::cos(glm::radians(15.f)));
		glUniform1f(glGetUniformLocation(s.shaderProgram, "mySpotLight.constant"), 1.0f);
		glUniform1f(glGetUniformLocation(s.shaderProgram, "mySpotLight.linear"), 0.09f);
	}

	glUniform3fv(glGetUniformLocation(s.shaderProgram, "eyePos"), 1, glm::value_ptr(_var::myEye.pos));
}

void Light::setROVLight(glm::mat4 model, glm::mat4 rotate, float angle) {
	myLight[ROV_LIGHT].position = model * glm::vec4(0.f, 0.f, 0.f, 1.f);
	myLight[ROV_LIGHT].direction = rotate * glm::vec4(0.f, -1.f, -1.f, 1.f);
}

void Light::changeLightColor(int light, glm::vec3 color) {
	myLight[light].diffuse = color;
}

void Light::changeLightState(int light) {
	myLight[light].mode = (myLight[light].mode == LIGHT_ON ? LIGHT_OFF : LIGHT_ON);
}

glm::vec3 Light::getPointLightColor() {
	return myLight[POINT_LIGHT].diffuse;
}

bool Light::getPointLightState() {
	return myLight[POINT_LIGHT].mode;
}