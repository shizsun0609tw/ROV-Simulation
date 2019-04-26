#include "_var.h"


_var::_var()
{
}


_var::~_var()
{
}

glm::mat4 _var::myViewMatrix;
glm::mat4 _var::myProjectionMatrix;
Eye _var::myEye;
int _var::width;
int _var::height;

void _var::init() {
	myEye = Eye(0.f, 45.f, 40.f, 45.f, glm::vec3());
}