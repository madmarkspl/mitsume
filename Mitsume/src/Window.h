#pragma once
#include <string>
#include <map>
#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "Shader.h"

class CWindow
{
public:
		CWindow(std::string name, GLuint width, GLuint height);
		~CWindow();

		int closeCondition() { return glfwWindowShouldClose(_window); }

		void addShaderProgram(std::string name, CShader program);

		void clear();
		void drawObject();
		void render();

private:
		GLFWwindow* _window;
		GLuint _width;
		GLuint _height;
		std::string _name;

		std::map<std::string, CShader> _shaders;
};
