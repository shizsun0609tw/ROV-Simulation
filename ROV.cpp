#include "ROV.h"

ROV::ROV()
{

}


ROV::~ROV()
{
}

void ROV::init() {
	center = glm::vec3(10.f, -20.f, 5.f);
	rotateAngle = glm::vec3(0.f);
	moveX = glm::vec3(1.f, 0.f, 0.f);
	moveY = glm::vec3(0.f, 1.f, 0.f);
	moveZ = glm::vec3(0.f, 0.f, 1.f);
	rotateMtx = glm::mat4(1.f);
	size = glm::vec3(4.5f , 4.5f, 7.5f);
	blade_angle = 0.f;
	myShader = shader("shader.vert", "shader.frag");

	glUseProgram(myShader.shaderProgram);
}

void ROV::draw() {
	update();

	glUniformMatrix4fv(glGetUniformLocation(myShader.shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(_var::myViewMatrix));
	glUniformMatrix4fv(glGetUniformLocation(myShader.shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(_var::myProjectionMatrix));

	// paint light
	static Light myLight;
	myLight.paint(myShader);

	modelMatrix.push(glm::mat4(1.f));	
	modelMatrix.top() = glm::translate(modelMatrix.top(), center);
	modelMatrix.top() = modelMatrix.top() * rotateMtx;
	// draw body
	modelMatrix.push(modelMatrix.top());
	modelMatrix.top() = glm::scale(modelMatrix.top(), glm::vec3(3.f, 2.5f, 15.f));
		// TODO draw sphere(body)
		draw::changeMaterial(perl,myShader);
		glUniformMatrix4fv(glGetUniformLocation(myShader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix.top()));
		glUniform4fv(glGetUniformLocation(myShader.shaderProgram, "color"), 1, glm::value_ptr(white));
		draw::drawCube();
	modelMatrix.pop();
	// draw front right propeller 
	modelMatrix.push(modelMatrix.top());
	modelMatrix.top() = glm::translate(modelMatrix.top(), glm::vec3(3.f, 0.f, -6.f));
	modelMatrix.push(modelMatrix.top());
	modelMatrix.top() = glm::scale(modelMatrix.top(), glm::vec3(3.f, 1.f, 1.f));
		draw::changeMaterial(ruby, myShader);
		glUniformMatrix4fv(glGetUniformLocation(myShader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix.top()));
		glUniform4fv(glGetUniformLocation(myShader.shaderProgram, "color"), 1, glm::value_ptr(red));
		draw::drawCube();
	modelMatrix.pop();
	modelMatrix.top() = glm::translate(modelMatrix.top(), glm::vec3(1.5f, 2.f, 0.f));
	modelMatrix.push(modelMatrix.top());
	modelMatrix.top() = glm::scale(modelMatrix.top(), glm::vec3(1.f, 5.f, 1.f));
		glUniformMatrix4fv(glGetUniformLocation(myShader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix.top()));
		glUniform4fv(glGetUniformLocation(myShader.shaderProgram, "color"), 1, glm::value_ptr(red));
		draw::drawCube();
	modelMatrix.pop();
	modelMatrix.top() = glm::translate(modelMatrix.top(), glm::vec3(0.f, 2.5f, 0.f));
		draw::changeMaterial(emerald, myShader);
		glUniformMatrix4fv(glGetUniformLocation(myShader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix.top()));
		glUniform4fv(glGetUniformLocation(myShader.shaderProgram, "color"), 1, glm::value_ptr(green));
		draw::drawCube();
		draw::changeMaterial(cyanPlastic, myShader);
	for (int i = 0; i < 6; i++) {
		modelMatrix.push(modelMatrix.top());
		modelMatrix.top() = glm::rotate(modelMatrix.top(), glm::radians(blade_angle + 60.f * i), glm::vec3(0.f, 1.f, 0.f));
		modelMatrix.top() = glm::scale(modelMatrix.top(), glm::vec3(3.f, 0.1f, 0.1f));
			glUniformMatrix4fv(glGetUniformLocation(myShader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix.top()));
			glUniform4fv(glGetUniformLocation(myShader.shaderProgram, "color"), 1, glm::value_ptr(green));
			draw::drawCube();
		modelMatrix.pop();
	}
	modelMatrix.pop();
	// draw front left propeller
	modelMatrix.push(modelMatrix.top());
	modelMatrix.top() = glm::translate(modelMatrix.top(), glm::vec3(-3.f, 0.f, -6.f));
	modelMatrix.push(modelMatrix.top());
	modelMatrix.top() = glm::scale(modelMatrix.top(), glm::vec3(3.f, 1.f, 1.f));
		draw::changeMaterial(ruby, myShader);
		glUniformMatrix4fv(glGetUniformLocation(myShader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix.top()));
		glUniform4fv(glGetUniformLocation(myShader.shaderProgram, "color"), 1, glm::value_ptr(red));
		draw::drawCube();
	modelMatrix.pop();
	modelMatrix.top() = glm::translate(modelMatrix.top(), glm::vec3(-1.5f, 2.f, 0.f));
	modelMatrix.push(modelMatrix.top());
	modelMatrix.top() = glm::scale(modelMatrix.top(), glm::vec3(1.f, 5.f, 1.f));
		glUniformMatrix4fv(glGetUniformLocation(myShader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix.top()));
		glUniform4fv(glGetUniformLocation(myShader.shaderProgram, "color"), 1, glm::value_ptr(red));
		draw::drawCube();
	modelMatrix.pop();
	modelMatrix.top() = glm::translate(modelMatrix.top(), glm::vec3(0.f, 2.5f, 0.f));
		draw::changeMaterial(emerald, myShader);
		glUniformMatrix4fv(glGetUniformLocation(myShader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix.top()));
		glUniform4fv(glGetUniformLocation(myShader.shaderProgram, "color"), 1, glm::value_ptr(green));
		draw::drawCube();
		draw::changeMaterial(cyanPlastic, myShader);
	for (int i = 0; i < 6; i++) {
		modelMatrix.push(modelMatrix.top());
		modelMatrix.top() = glm::rotate(modelMatrix.top(), glm::radians(blade_angle + 60.f * i), glm::vec3(0.f, 1.f, 0.f));
		modelMatrix.top() = glm::scale(modelMatrix.top(), glm::vec3(3.f, 0.1f, 0.1f));
			glUniformMatrix4fv(glGetUniformLocation(myShader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix.top()));
			glUniform4fv(glGetUniformLocation(myShader.shaderProgram, "color"), 1, glm::value_ptr(green));
			draw::drawCube();
		modelMatrix.pop();
	}
	modelMatrix.pop();
	// draw back left propeller
	modelMatrix.push(modelMatrix.top());
	modelMatrix.top() = glm::translate(modelMatrix.top(), glm::vec3(-3.f, 0.f, 6.f));
	modelMatrix.push(modelMatrix.top());
	modelMatrix.top() = glm::scale(modelMatrix.top(), glm::vec3(3.f, 1.f, -1.f));
		draw::changeMaterial(ruby, myShader);
		glUniformMatrix4fv(glGetUniformLocation(myShader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix.top()));
		glUniform4fv(glGetUniformLocation(myShader.shaderProgram, "color"), 1, glm::value_ptr(red));
		draw::drawCube();
	modelMatrix.pop();
	modelMatrix.top() = glm::translate(modelMatrix.top(), glm::vec3(-1.5f, 2.f, 0.f));
	modelMatrix.push(modelMatrix.top());
	modelMatrix.top() = glm::scale(modelMatrix.top(), glm::vec3(1.f, 5.f, 1.f));
		glUniformMatrix4fv(glGetUniformLocation(myShader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix.top()));
		glUniform4fv(glGetUniformLocation(myShader.shaderProgram, "color"), 1, glm::value_ptr(red));
		draw::drawCube();
	modelMatrix.pop();
	modelMatrix.top() = glm::translate(modelMatrix.top(), glm::vec3(0.f, 2.5f, 0.f));
		draw::changeMaterial(emerald, myShader);
		glUniformMatrix4fv(glGetUniformLocation(myShader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix.top()));
		glUniform4fv(glGetUniformLocation(myShader.shaderProgram, "color"), 1, glm::value_ptr(green));
		draw::drawCube();
		draw::changeMaterial(cyanPlastic, myShader);
	for (int i = 0; i < 6; i++) {
		modelMatrix.push(modelMatrix.top());
		modelMatrix.top() = glm::rotate(modelMatrix.top(), glm::radians(blade_angle + 60.f * i), glm::vec3(0.f, 1.f, 0.f));
		modelMatrix.top() = glm::scale(modelMatrix.top(), glm::vec3(3.f, 0.1f, 0.1f));
			glUniformMatrix4fv(glGetUniformLocation(myShader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix.top()));
			glUniform4fv(glGetUniformLocation(myShader.shaderProgram, "color"), 1, glm::value_ptr(green));
			draw::changeMaterial(emerald, myShader);
			draw::drawCube();
		modelMatrix.pop();
	}
	modelMatrix.pop();
	// draw back right propeller
	modelMatrix.push(modelMatrix.top());
	modelMatrix.top() = glm::translate(modelMatrix.top(), glm::vec3(3.f, 0.f, 6.f));
	modelMatrix.push(modelMatrix.top());
	modelMatrix.top() = glm::scale(modelMatrix.top(), glm::vec3(3.f, 1.f, -1.f));
		draw::changeMaterial(ruby, myShader);
		glUniformMatrix4fv(glGetUniformLocation(myShader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix.top()));
		glUniform4fv(glGetUniformLocation(myShader.shaderProgram, "color"), 1, glm::value_ptr(red));
		draw::drawCube();
	modelMatrix.pop();
	modelMatrix.top() = glm::translate(modelMatrix.top(), glm::vec3(1.5f, 2.f, 0.f));
	modelMatrix.push(modelMatrix.top());
	modelMatrix.top() = glm::scale(modelMatrix.top(), glm::vec3(1.f, 5.f, 1.f));
		glUniformMatrix4fv(glGetUniformLocation(myShader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix.top()));
		glUniform4fv(glGetUniformLocation(myShader.shaderProgram, "color"), 1, glm::value_ptr(red));
		draw::drawCube();
	modelMatrix.pop();
	modelMatrix.top() = glm::translate(modelMatrix.top(), glm::vec3(0.f, 2.5f, 0.f));
		draw::changeMaterial(emerald, myShader);
		glUniformMatrix4fv(glGetUniformLocation(myShader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix.top()));
		glUniform4fv(glGetUniformLocation(myShader.shaderProgram, "color"), 1, glm::value_ptr(green));
		draw::drawCube();
		draw::changeMaterial(cyanPlastic, myShader);
	for (int i = 0; i < 6; i++) {
		modelMatrix.push(modelMatrix.top());
		modelMatrix.top() = glm::rotate(modelMatrix.top(), glm::radians(blade_angle + 60.f * i), glm::vec3(0.f, 1.f, 0.f));
		modelMatrix.top() = glm::scale(modelMatrix.top(), glm::vec3(3.f, 0.1f, 0.1f));
			glUniformMatrix4fv(glGetUniformLocation(myShader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix.top()));
			glUniform4fv(glGetUniformLocation(myShader.shaderProgram, "color"), 1, glm::value_ptr(green));
			draw::drawCube();
		modelMatrix.pop();
	}
	modelMatrix.pop();
	// ROV light
	modelMatrix.push(modelMatrix.top());
	modelMatrix.top() = glm::translate(modelMatrix.top(), glm::vec3(0.f, -1.f, -5.f));
	modelMatrix.top() = glm::rotate(modelMatrix.top(), glm::radians(light_angle), glm::vec3(1.f, 0.f, 0.f));
	modelMatrix.top() = glm::scale(modelMatrix.top(), glm::vec3(0.25f, 1.f, 0.25f));
		draw::changeMaterial(obsidian, myShader);
		glUniformMatrix4fv(glGetUniformLocation(myShader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix.top()));
		glUniform4fv(glGetUniformLocation(myShader.shaderProgram, "color"), 1, glm::value_ptr(green));
		Light::setROVLight(modelMatrix.top(), rotateMtx, light_angle);
	modelMatrix.pop();
	
	modelMatrix.pop();
	modelMatrix.empty();
	draw::changeMaterial(no_mat, myShader);
}

// for keyboard translate
void ROV::translate(glm::vec3 vector) {
	if (vector == glm::vec3(1.f, 0.f, 0.f) || vector == glm::vec3(-1.f, 0.f, 0.f))center += moveX * vector.x;
	if (vector == glm::vec3(0.f, 1.f, 0.f) || vector == glm::vec3(0.f, -1.f, 0.f))center += moveY * vector.y;
	if (vector == glm::vec3(0.f, 0.f, 1.f) || vector == glm::vec3(0.f, 0.f, -1.f))center += moveZ * vector.z;
}

// for keyboard rotate 
void ROV::rotate(glm::vec3 axis, float angle) {
	// TODO rotate move vector
	if (axis == glm::vec3(1.f, 0.f, 0.f)) {
		rotateAngle.x += angle;
		rotateMtx = glm::rotate(rotateMtx, glm::radians(angle), glm::vec3(1.f, 0.f, 0.f));
	}
	else if (axis == glm::vec3(0.f, 1.f, 0.f)) {
		rotateAngle.y += angle;
		rotateMtx = glm::rotate(rotateMtx, glm::radians(angle), glm::vec3(0.f, 1.f, 0.f));
	}
	else if (axis == glm::vec3(0.f, 0.f, 1.f)) {
		rotateAngle.z += angle;
		rotateMtx = glm::rotate(rotateMtx, glm::radians(angle), glm::vec3(0.f, 0.f, 1.f));
	}

	moveX = glm::vec3(rotateMtx * glm::vec4(1.f, 0.f, 0.f, 0.f));
	moveY = glm::vec3(rotateMtx * glm::vec4(0.f, 1.f, 0.f, 0.f));
	moveZ = glm::vec3(rotateMtx * glm::vec4(0.f, 0.f, 1.f, 0.f));
}

void ROV::update() {
	blade_angle += 6.f;
	collisionDetect();
}

void ROV::setKey(int key) {
	this->key = key;
}

void ROV::collisionDetect() {
	if (center.x + size.x > terrainWidth * 0.5f || center.x - size.x < -terrainWidth * 0.5f
		|| center.y + size.y > terrainDepth || center.y - size.y < -terrainDepth
		|| center.z + size.z > terrainHeight * 0.5f || center.z - size.z < -terrainHeight * 0.5f) {
		switch (key)
		{
		case KEY_W:
			center += moveZ;
			break;
		case KEY_A:
			center += moveX;
			break;
		case KEY_S:
			center -= moveZ;
			break;
		case KEY_D:
			center -= moveX;
			break;
		case KEY_Q:
			center -= moveY;
			break;
		case KEY_E:
			center += moveY;
			break;
		default:
			break;
		}

		key = KEY_NULL;
		return;
	}


	for (int count = 0; count < OBSTACLE_NUM; count++) {
		glm::vec3 oPos = Scene::getObstaclePos(count);
		glm::vec3 oSize = Scene::getObstacleSize(count);

		if (((center.x + size.x <= oPos.x + oSize.x * 0.5f && center.x + size.x >= oPos.x - oSize.x * 0.5f)
				|| (center.x - size.x <= oPos.x + oSize.x * 0.5f && center.x - size.x >= oPos.x - oSize.x * 0.5f))
			&& ((center.y + size.y <= oPos.y + oSize.y * 0.5f && center.y + size.y >= oPos.y - oSize.y * 0.5f)
				|| (center.y - size.y <= oPos.y + oSize.y * 0.5f && center.y - size.y >= oPos.y - oSize.y * 0.5f))
			&& ((center.z + size.z <= oPos.z + oSize.z * 0.5f && center.z + size.z >= oPos.z - oSize.z * 0.5f)
				|| (center.z - size.z <= oPos.z + oSize.z * 0.5f && center.z - size.z >= oPos.z - oSize.z * 0.5f))) {
			switch (key)
			{
			case KEY_W:
				center += moveZ;
				break;
			case KEY_A:
				center += moveX;
				break;
			case KEY_S:
				center -= moveZ;
				break;
			case KEY_D:
				center -= moveX;
				break;
			case KEY_Q:
				center -= moveY;
				break;
			case KEY_E:
				center += moveY;
				break;
			default:
				break;
			}			

			key = KEY_NULL;
			return;
		}
	}
}