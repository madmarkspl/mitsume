#include "Window.h"


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

	glfwSetKeyCallback(_window, key_callback);
	glfwSetCursorPosCallback(_window, mouse_callback);
	glfwSetScrollCallback(_window, scroll_callback);
	glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

CWindow::~CWindow()
{
}

void CWindow::addShaderProgram(std::string name, CShader program)
{
	_shaders.emplace(name, program);
}

void CWindow::clear()
{
	glfwMakeContextCurrent(_window);
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void CWindow::drawObject()
{
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Create a Vertex Buffer Object and copy the vertex data to it
	GLuint vbo;
	glGenBuffers(1, &vbo);

	GLfloat vertices[] = {
			0.0f, 0.5f, // Vertex 1 (X, Y)
			0.5f, -0.5f, // Vertex 2 (X, Y)
			-0.5f, -0.5f  // Vertex 3 (X, Y)
	};

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//glBindFragDataLocation(_shaders.at("basic").getProgram(), 0, "outColor");
	_shaders.at("basic").useProgram();

	GLint posAttrib = glGetAttribLocation(_shaders.at("basic").getProgram(), "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void CWindow::render()
{
	glfwSwapBuffers(_window);
}