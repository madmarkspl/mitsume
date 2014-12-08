#include "Game.h"
#include "Window.h"
#include "Service.h"
#include "Camera.h"

CWindow::CWindow(std::string name, GLuint width, GLuint height) : _name(name), _width(width), _height(height)
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	_window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);

	glfwMakeContextCurrent(_window);

	glewExperimental = GL_TRUE;
	glewInit();

	printf("Vendor: %s\n", glGetString(GL_VENDOR));
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("Version: %s\n", glGetString(GL_VERSION));
	printf("GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	printf("GLFW: %s \n", glfwGetVersionString());

	glfwSetKeyCallback(_window, CWindow::keyCallback);
	glfwSetCursorPosCallback(_window, CWindow::cursorPosCallback);
	glfwSetScrollCallback(_window, CWindow::scrollCallback);
	glfwSetMouseButtonCallback(_window, CWindow::mouseButtonCallback);
	glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

CWindow::~CWindow()
{
}

void CWindow::addShaderProgram(std::string name, CShader program)
{
	_shaders.emplace(name, program);
}

void CWindow::attachCallbackPointer(void* game)
{
	glfwSetWindowUserPointer(_window, game);
}

void CWindow::clear()
{
	glfwMakeContextCurrent(_window);
	glClearColor(0.f, 0.f, 0.f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void CWindow::drawObject(GLfloat* vertices, GLint size, glm::vec4 color, GLint mode, std::string program)
{
	int numberOfElements;

	if (mode == GL_TRIANGLES)
		numberOfElements = 6;
	else if (mode == GL_TRIANGLE_FAN)
		numberOfElements = 4;
	else if (mode == GL_LINE_LOOP)
		numberOfElements = 4;

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint vbo;
	glGenBuffers(1, &vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	//glBindFragDataLocation(_shaders.at("basic").getProgram(), 0, "outColor");
	_shaders.at("basic").useProgram();

	glm::mat4 viewMatrix;
	glm::mat4 projMatrix = glm::ortho<float>(0, 1280, 0, 720);

	GLint uniModel = glGetUniformLocation(_shaders.at("basic").getProgram(), "model");
	GLint uniView = glGetUniformLocation(_shaders.at("basic").getProgram(), "view");
	GLint uniProj = glGetUniformLocation(_shaders.at("basic").getProgram(), "proj");
	GLint uniColor = glGetUniformLocation(_shaders.at("basic").getProgram(), "color");

	glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(projMatrix));
	glUniform4f(uniColor, color.r, color.g, color.b, color.a);

	glm::mat4 modelMatrix;
	glBindVertexArray(vao);

	//modelMatrix = glm::translate(modelMatrix, glm::vec3(640, 360, 0));

	glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	glDrawArrays(mode, 0, numberOfElements);

	glBindVertexArray(0);
}

void CWindow::drawRect(GLfloat* vertices, GLint size, glm::vec4 color)
{
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint vbo;
	glGenBuffers(1, &vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//glBindFragDataLocation(_shaders.at("basic").getProgram(), 0, "outColor");
	_shaders.at("basic").useProgram();

	glm::mat4 viewMatrix;
	glm::mat4 projMatrix = glm::ortho<float>(0, 1280, 0, 720);

	GLint uniModel = glGetUniformLocation(_shaders.at("basic").getProgram(), "model");
	GLint uniView = glGetUniformLocation(_shaders.at("basic").getProgram(), "view");
	GLint uniProj = glGetUniformLocation(_shaders.at("basic").getProgram(), "proj");
	GLint uniColor = glGetUniformLocation(_shaders.at("basic").getProgram(), "color");

	glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(projMatrix));
	glUniform4f(uniColor, color.r, color.g, color.b, color.a);

	glm::mat4 modelMatrix;
	glBindVertexArray(vao);

	//modelMatrix = glm::translate(modelMatrix, glm::vec3(640, 360, 0));

	glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	glDrawArrays(GL_LINE_LOOP, 0, 4);

	glBindVertexArray(0);
}

void CWindow::render()
{
	glfwSwapBuffers(_window);
}

void CWindow::keyCallback(GLFWwindow* handle, int key, int scancode, int action, int mods)
{
	CGame *game = static_cast<CGame*>(glfwGetWindowUserPointer(handle));

	game->handleInput(key, action);

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(handle, GL_TRUE);
}

void CWindow::mouseButtonCallback(GLFWwindow* handle, int buton, int action, int mods)
{
	CGame *game = static_cast<CGame*>(glfwGetWindowUserPointer(handle));

	game->handleInput(buton, action);
}

void CWindow::cursorPosCallback(GLFWwindow* handle, double x, double y)
{
	CGame *game = static_cast<CGame*>(glfwGetWindowUserPointer(handle));

	game->handleInput(x, y);
}

void CWindow::scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	//std::cout << "scroll!" << std::endl;
}