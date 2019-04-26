#pragma once

#include "Eye.h"
#include "Definition.h"

class _var
{
public:
	_var();
	~_var();
	static Eye myEye;
	static glm::mat4 myViewMatrix;
	static glm::mat4 myProjectionMatrix;
	static int width, height;
	static void init();
};