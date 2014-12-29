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

	int closeCondition() { return glfwWindowShouldClose(_window); }

	void addShaderProgram(std::string name, CShader program);
	void attachCallbackPointer(void*);

	void clear();
	void setModelMatrix(const glm::mat4& matrix);
	void render(const std::vector<Vertex>& vVertices, const BatchConfig& config);
	void emptyAllBatches();
	void swapBuffers();

private:
	void emptyBatch(CBatch* batchToEmpty, bool emptyAll = false);
	static void keyCallback(GLFWwindow* handle, int key, int scancode, int action, int mods);
	static void mouseButtonCallback(GLFWwindow* handle, int buton, int action, int mods);
	static void cursorPosCallback(GLFWwindow* handle, double x, double y);
	static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	static int counter;
	
	GLFWwindow* _window;
	GLuint _width;
	GLuint _height;
	std::string _name;

	std::map<std::string, CShader> _shaders;
	std::vector<std::shared_ptr<CBatch>> _batches;
	GLuint _numBatches;
	GLuint _maxNumVerticesPerBatch;
};
