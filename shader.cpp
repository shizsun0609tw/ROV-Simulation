#include "shader.h"



shader::shader()
{
}

shader::shader(string VertexShaderName, string FragmentShaderName) {
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	GLint isCompiled = 0;
	ifstream vertexShaderFile, fragmentShaderFile;
	string vertexShaderCode, fragmentShaderCode;
	char ch;

	shaderProgram = glCreateProgram();
	
	vertexShaderFile.open(VertexShaderName);
	fragmentShaderFile.open(FragmentShaderName);
	if (!vertexShaderFile) cout << VertexShaderName << " open failed!" << endl;
	else {
		while (!vertexShaderFile.eof()) {
			vertexShaderFile.get(ch);
			vertexShaderCode += ch;
		}
		GLchar* vertexContext[] = { &vertexShaderCode[0] };
		glShaderSource(vertexShader, 1, vertexContext, NULL);
		glCompileShader(vertexShader);
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		
		if (isCompiled == GL_FALSE) {
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);
			vector<GLchar> errorLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &errorLog[0]);
			for (int i = 0; i < errorLog.size(); i++) cout << errorLog[i];
			glDeleteShader(vertexShader);
			return;
		}
		
		glAttachShader(shaderProgram, vertexShader);
	}
	if (!fragmentShaderFile) cout << FragmentShaderName << " open failed!" << endl;
	else {
		while (!fragmentShaderFile.eof()) {
			fragmentShaderFile.get(ch);
			fragmentShaderCode += ch;
		}
		GLchar* fragmentContext[] = { &fragmentShaderCode[0] };
		glShaderSource(fragmentShader, 1, fragmentContext, NULL);
		glCompileShader(fragmentShader);
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);

		if (isCompiled == GL_FALSE) {
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);
			vector<GLchar> errorLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &errorLog[0]);
			for (int i = 0; i < errorLog.size(); i++) cout << errorLog[i];
			glDeleteShader(vertexShader);
			return;
		}
		glAttachShader(shaderProgram, fragmentShader);
	}
	glLinkProgram(shaderProgram);

	vertexShaderFile.close();
	fragmentShaderFile.close();
}

shader::~shader()
{
}