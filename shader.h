#pragma once
#include <gl/glew.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class shader
{
public:
	shader();
	shader(string VertexShaderName, string FragmentShaderName);
	~shader();
	GLuint shaderProgram;
};

