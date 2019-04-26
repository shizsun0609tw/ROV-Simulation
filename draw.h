#pragma once
#include "Definition.h"
#include "shader.h"
#include "Icosphere.h"
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#define VBO_NUM 3
#define VAO_NUM 5

#define CUBE 0
#define SPHERE 1
#define LINE 2

#define VERTEX 0
#define TEXTURE 1
#define NORMAL 2

class draw
{
public:
	draw();
	~draw();
	static void init();
	static void drawCube();
	static void drawSphere();
	static void drawLine(glm::vec3 v1, glm::vec3 v2);
	static void changeMaterial(material m, shader s);
private:
	static GLuint VAO[VAO_NUM];
	static GLuint cubeVBO[VBO_NUM];
	static GLuint cubeEBO;
	static GLuint sphereVBO[VBO_NUM];
	static GLuint sphereEBO;
	static GLuint lineVBO;
	static GLuint lineEBO;
	static Icosphere sphere;
};
