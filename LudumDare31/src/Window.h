#pragma once
#include <string>
#include <map>
#include <memory>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Batch.h"

class CWindow
{
public:
	CWindow(std::string name, GLuint width, GLuint height);
	~CWindow();

	void attachCallbackPointer(void*);
	int closeCondition() { return glfwWindowShouldClose(_window); }
	GLFWwindow* getHandle() { return _window; }

private:
	static void keyCallback(GLFWwindow* handle, int key, int scancode, int action, int mods);
	static void mouseButtonCallback(GLFWwindow* handle, int buton, int action, int mods);
	static void cursorPosCallback(GLFWwindow* handle, double x, double y);
	static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	
	GLFWwindow* _window;
	GLuint _width;
	GLuint _height;
	std::string _name;
};
