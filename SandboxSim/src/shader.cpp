#include "shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glad/glad.h>

std::string readShaderSource(const char* shaderPath);
unsigned int compileShader(const char* source, unsigned int type);

void Shader::use() {
	glUseProgram(ID);
}

void Shader::remove() {
	glDeleteProgram(ID);
}

void Shader::setBool(const std::string& name, bool value) const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const {
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setMat4(const std::string& name, glm::mat4 value) const {
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

float Shader::getFloat(const std::string& name) const {
	float buffer;
	glGetUniformfv(ID, glGetUniformLocation(ID, name.c_str()), &buffer);
	return buffer;
}

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
	std::string vertexCode = readShaderSource(vertexPath);
	std::string fragmentCode = readShaderSource(fragmentPath);

	// converting strings into c style char arrays
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	unsigned int vertex = compileShader(vShaderCode, GL_VERTEX_SHADER);
	unsigned int fragment = compileShader(fShaderCode, GL_FRAGMENT_SHADER);

	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);

	int success;
	char infoLog[512];
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED" << std::endl << infoLog << std::endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

// reads shader source code from file to const char
// ------------------------------------------------ 
std::string readShaderSource(const char* shaderPath) {
	std::string code;
	std::ifstream shaderFile;
	// setting for throwing exceptions when failure or badbit
	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		shaderFile.open(shaderPath);
		std::stringstream shaderStream;
		shaderStream << shaderFile.rdbuf();
		shaderFile.close();
		code = shaderStream.str();
	}
	catch (std::ifstream::failure& e) {
		std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << e.what() << std::endl;
	}

	return code;
}

// comiples single shader file
// ---------------------------
unsigned int compileShader(const char* source, unsigned int type) {
	unsigned int shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);

	int success;
	char infoLog[512];

	glGetProgramiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::" << type << "::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	return shader;
}