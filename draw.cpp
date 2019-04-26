#include "draw.h"

draw::draw()
{
}


draw::~draw()
{
}

GLuint draw::VAO[VAO_NUM];
GLuint draw::cubeEBO;
GLuint draw::cubeVBO[VBO_NUM];
GLuint draw::sphereEBO;
GLuint draw::sphereVBO[VBO_NUM];
Icosphere draw::sphere;
GLuint draw::lineEBO;
GLuint draw::lineVBO;

void draw::init() {
	glGenVertexArrays(VAO_NUM, &VAO[0]);

	/*cube
		  v12	v11
			-----
		 v13| T |v10v9
	  v0-----------------v8
		| L | F | R | B |
	  v1-----------------v7
		  v2| B |v5 v6  
			-----
		   v3   v4
	*/
	GLfloat cubePos[] = {
		-0.5f, 0.5f, -0.5f,	// v0
		-0.5f, -0.5f, -0.5f,// v1
		-0.5f, -0.5f, 0.5f,	// v2
		-0.5f, -0.5f, -0.5f,// v3
		0.5f, -0.5f, -0.5f, // v4
		0.5f, -0.5f, 0.5f,  // v5
		0.5f, -0.5f, -0.5f,	// v6
		-0.5f, -0.5f, -0.5f,// v7
		-0.5f, 0.5f, -0.5f,	// v8
		0.5f, 0.5f, -0.5f,	// v9
		0.5f, 0.5f, 0.5f,	// v10
		0.5f, 0.5f, -0.5f,	// v11
		-0.5f, 0.5f, -0.5f,	// v12
		-0.5f, 0.5f, 0.5f	// v13
	};
	GLuint  cubeIndices[] = {
		13, 10, 12,  12, 10, 11,	// top
		13,  2,  5,  13,  5, 10,	// front
		10,  5,  6,  10,  6,  9,	// right
		 9,  6,  7,   9,  7,  8,	// back
		 0,  1,  2,	  0,  2, 13,	// left
		 2,  3,  4,   2,  4,  5		// bottom
	};
	GLfloat cubeTex_skybox[] = {
	     0.f, 0.667f,		// v0
		 0.f, 0.333f,		// v1
       0.25f, 0.333f,		// v2
	   0.25f,    0.f,		// v3
		0.5f,    0.f,		// v4
		0.5f, 0.333f,		// v5
	   0.75f, 0.333f,		// v6
		 1.f, 0.333f,		// v7
		 1.f, 0.667f,		// v8
	   0.75f, 0.667f,		// v9
	    0.5f, 0.667f,		// v10
		0.5f,	 1.f,		// v11
	   0.25f,	 1.f,		// v12
	   0.25f, 0.667f,		// v13
	};
	GLfloat cubeTex_general[] = {
		1.f, 1.f,	// v0
		1.f, 0.f,	// v1
		0.f, 0.f,	// v2
		0.f, 1.f,	// v3
		1.f, 1.f,	// v4
		1.f, 0.f,	// v5
		0.f, 0.f,	// v6
		1.f, 0.f,	// v7
		1.f, 1.f,	// v8
		0.f, 1.f,	// v9
		1.f, 1.f,	// v10
		1.f, 0.f,	// v11
		0.f, 0.f,	// v12
		0.f, 1.f	// v13
	};
	GLfloat cubeNormal[] = {
		-0.577f,  0.577f, -0.577f,
		-0.577f, -0.577f, -0.577f,
		-0.577f, -0.577f,  0.577f,
		-0.577f, -0.577f, -0.577f,
		 0.577f, -0.577f, -0.577f,
		 0.577f, -0.577f,  0.577f,
		 0.577f, -0.577f, -0.577f,
		-0.577f, -0.577f, -0.577f,
		-0.577f,  0.577f, -0.577f,
	 	 0.577f,  0.577f, -0.577f,
		 0.577f,  0.577f,  0.577f,
		 0.577f,  0.577f, -0.577f,
		-0.577f,  0.577f, -0.577f,
		-0.577f,  0.577f,  0.577f
	};
	glBindVertexArray(VAO[CUBE]);

	glGenBuffers(1, &cubeEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);

	glGenBuffers(VBO_NUM, &cubeVBO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO[VERTEX]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubePos), cubePos, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO[TEXTURE]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeTex_general), cubeTex_general, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (GLvoid*)0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO[NORMAL]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeNormal), cubeNormal, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)0);
	glEnableVertexAttribArray(2);

	
	// Icosphere
	sphere = Icosphere(1.f, 3, true);

	glBindVertexArray(VAO[SPHERE]);

	glGenBuffers(1, &sphereEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sphereEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sphere.getIndexSize(), sphere.getIndices(), GL_STATIC_DRAW);

	glGenBuffers(VBO_NUM, &sphereVBO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, sphereVBO[VERTEX]);
	glBufferData(GL_ARRAY_BUFFER, sphere.getVertexSize(), sphere.getVertices(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, sphereVBO[TEXTURE]);
	glBufferData(GL_ARRAY_BUFFER, sphere.getTexCoordSize(), sphere.getTexCoords(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (GLvoid*)0);
	glEnableVertexAttribArray(1);
	
	glBindBuffer(GL_ARRAY_BUFFER, sphereVBO[NORMAL]);
	glBufferData(GL_ARRAY_BUFFER, sphere.getNormalSize(), sphere.getNormals(), GL_STATIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)0);
	glEnableVertexAttribArray(2);
	

	GLfloat linePos[] = {0.f, 0.f, 0.f, 
						 1.f, 0.f, 0.f};
	GLuint lineIndices[] = { 0, 1 };
	glBindVertexArray(VAO[LINE]);
	
	glGenBuffers(1, &lineEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lineEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(lineIndices), lineIndices, GL_STATIC_DRAW);

	glGenBuffers(VBO_NUM, &lineVBO);
	glBindBuffer(GL_ARRAY_BUFFER, lineVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(linePos), linePos, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

void draw::drawCube() {
	glBindVertexArray(VAO[CUBE]);
	glDrawElements(GL_TRIANGLES, 3 * 2 * 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void draw::drawSphere() {
	glBindVertexArray(VAO[SPHERE]);
	glDrawElements(GL_TRIANGLES, sphere.getIndexCount(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void draw::drawLine(glm::vec3 v1, glm::vec3 v2) {
	GLfloat v[] = { v1.x, v1.y, v1.z, v2.x, v2.y, v2.z };
	
	glLineWidth(3);
	glBindVertexArray(VAO[LINE]);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(v), v);
	glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void draw::changeMaterial(material m, shader s) {
	glUniform3fv(glGetUniformLocation(s.shaderProgram, "myMaterial.ambient"), 1, glm::value_ptr(m.ambient));
	glUniform3fv(glGetUniformLocation(s.shaderProgram, "myMaterial.diffuse"), 1, glm::value_ptr(m.diffuse));
	glUniform3fv(glGetUniformLocation(s.shaderProgram, "myMaterial.specular"), 1, glm::value_ptr(m.specular));
	glUniform1f(glGetUniformLocation(s.shaderProgram, "myMaterial.shininess"), m.shininess);
}