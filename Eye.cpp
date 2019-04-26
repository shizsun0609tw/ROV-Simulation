#include "Eye.h"

Eye::Eye() {

}

Eye::Eye(float eye_theta, float eye_fi, float d, float fovy, glm::vec3 pos)
{
	this->eye_theta = eye_theta;
	this->eye_fi = eye_fi;
	this->d = d;
	this->fovy = fovy;
	this->pos = pos;
	enable = true;

	myShader = shader("shader.vert", "shader.frag");
	glUseProgram(myShader.shaderProgram);
}


Eye::~Eye()
{
}

void Eye::changeMode() {
	enable = (enable == true ? false : true);
}

void Eye::draw(glm::mat4 myViewMatrix, glm::mat4 myProjectionMatrix, float windowWidth, float windowHeight) {
	update(windowWidth, windowHeight);
	
	if (enable == false) return;

	float ratio = windowWidth / windowHeight;
	draw::changeMaterial(perl, myShader);
	glUniformMatrix4fv(glGetUniformLocation(myShader.shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(myViewMatrix));
	glUniformMatrix4fv(glGetUniformLocation(myShader.shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(myProjectionMatrix));
	glUniform4fv(glGetUniformLocation(myShader.shaderProgram, "color"), 1, glm::value_ptr(red));
	glUniform3fv(glGetUniformLocation(myShader.shaderProgram, "myMaterial.emission"), 1, glm::value_ptr(glm::vec3(0.5f)));

	modelMatrix.push(glm::mat4(1.f));
	modelMatrix.top() = glm::translate(modelMatrix.top(), pos);
	glUniformMatrix4fv(glGetUniformLocation(myShader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix.top()));
	draw::drawSphere();
	glUniform4fv(glGetUniformLocation(myShader.shaderProgram, "color"), 1, glm::value_ptr(white));
	draw::drawLine(glm::vec3(0.f), LTF);
	draw::drawLine(glm::vec3(0.f), LBF);
	draw::drawLine(glm::vec3(0.f), RTF);
	draw::drawLine(glm::vec3(0.f), RBF);
	draw::drawLine(LTF, LBF);
	draw::drawLine(LBF, RBF);
	draw::drawLine(RBF, RTF);
	draw::drawLine(RTF, LTF);
	modelMatrix.pop();
	modelMatrix.empty();
	glUniform3fv(glGetUniformLocation(myShader.shaderProgram, "myMaterial.emission"), 1, glm::value_ptr(glm::vec3(0.f)));
}

void Eye::update(int windowWidth, int windowHeight) {
	glm::mat4 translate(1.f);
	float ratio = (float)windowWidth / windowHeight;

	w = glm::normalize(pos);
	u = glm::normalize(glm::cross(glm::vec3(0.f, 1.f, 0.f), w));
	v = glm::normalize(glm::cross(w, u));
	
	translate = glm::translate(translate, -w * viewVolumnNear);
	translate = glm::translate(translate, v * viewVolumnNear * (float)tan(fovy / 2 * PI / 180));
	translate = glm::translate(translate, u * viewVolumnNear * (float)tan(fovy / 2 * ratio * PI / 180));
	RTN = translate * glm::vec4(0.f, 0.f, 0.f, 1.f);
	RTF = RTN * (viewVolumnFar / viewVolumnNear);
	translate = glm::mat4(1.f);

	translate = glm::translate(translate, -w * viewVolumnNear);
	translate = glm::translate(translate, -v * viewVolumnNear * (float)tan(fovy / 2 * PI / 180));
	translate = glm::translate(translate, u * viewVolumnNear * (float)tan(fovy / 2 * ratio * PI / 180));
	RBN = translate * glm::vec4(0.f, 0.f, 0.f, 1.f);
	RBF = RBN * (viewVolumnFar / viewVolumnNear);
	translate = glm::mat4(1.f);

	translate = glm::translate(translate, -w * viewVolumnNear);
	translate = glm::translate(translate, v * viewVolumnNear * (float)tan(fovy / 2 * PI / 180));
	translate = glm::translate(translate, -u * viewVolumnNear * (float)tan(fovy / 2 * ratio * PI / 180));
	LTN = translate * glm::vec4(0.f, 0.f, 0.f, 1.f);
	LTF = LTN * (viewVolumnFar / viewVolumnNear);
	translate = glm::mat4(1.f);

	translate = glm::translate(translate, -w * viewVolumnNear);
	translate = glm::translate(translate, -v * viewVolumnNear * (float)tan(fovy / 2 * PI / 180));
	translate = glm::translate(translate, -u * viewVolumnNear * (float)tan(fovy / 2 * ratio * PI / 180));
	LBN = translate * glm::vec4(0.f, 0.f, 0.f, 1.f);
	LBF = LBN * (viewVolumnFar / viewVolumnNear);
	translate = glm::mat4(1.f);

	glm::vec3 v1, v2;
	v1 = RBN - LBN; v2 = LTN - LBN;
	planeNormal[0] = glm::normalize(glm::cross(v1, v2));
	v1 = LTF - RTF; v2 = RTN - RTF;
	planeNormal[1] = glm::normalize(glm::cross(v1, v2));
	v1 = LBF - LTF; v2 = LTN - LTF;
	planeNormal[2] = glm::normalize(glm::cross(v1, v2));
	v1 = RBF - LBF; v2 = LBN - LBF;
	planeNormal[3] = glm::normalize(glm::cross(v1, v2));
	v1 = RTN - RTF; v2 = RBF - RTF;
	planeNormal[4] = glm::normalize(glm::cross(v1, v2));
	v1 = RTF - LTF; v2 = LBF - LTF;
	planeNormal[5] = glm::normalize(glm::cross(v1, v2));

	checkPoint[0] = pos + LTN;
	checkPoint[1] = pos + LTN;
	checkPoint[2] = pos + LTN;
	checkPoint[3] = pos + LBN;
	checkPoint[4] = pos + RTN;
	checkPoint[5] = pos + RTF;
}