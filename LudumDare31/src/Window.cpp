#include <thread>
#include <queue>
#include <SOIL.h>
#include <ppl.h>
#include "Game.h"
#include "Window.h"
#include "Service.h"
#include "Camera.h"

int CWindow::counter;

CWindow::CWindow(std::string name, GLuint width, GLuint height) :
_name(name), _width(width), _height(height)
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

	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_COLOR);

	glfwSetKeyCallback(_window, CWindow::keyCallback);
	glfwSetCursorPosCallback(_window, CWindow::cursorPosCallback);
	glfwSetScrollCallback(_window, CWindow::scrollCallback);
	glfwSetMouseButtonCallback(_window, CWindow::mouseButtonCallback);
	glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	for (unsigned int i = 0; i < 10; ++i)
	{
		_batches.push_back(std::shared_ptr<CBatch>(new CBatch()));
	_numBatches++;
	}
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
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
	static glm::mat4 projMatrix = glm::perspective(CService::getCamera()->getZoom(), (float)1280 / (float)720, 0.01f, 100.0f);
	static glm::mat4 viewMatrix;
	
	static GLint uniView;
	static GLint uniProj;

	//glfwMakeContextCurrent(_window);
	glClearColor(0.f, 0.f, 0.f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_shaders.at("basic").useProgram();

	viewMatrix = CService::getCamera()->getViewMatrix();
	uniView = glGetUniformLocation(_shaders.at("basic").getProgram(), "view");
	uniProj = glGetUniformLocation(_shaders.at("basic").getProgram(), "proj");

	glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(projMatrix));

	//static GLfloat angle = 0;
	//angle += 1;
	// 5 * glm::sin(glm::radians(angle))
	glm::vec3 lightPos(0.0f, 0.0f, -1.5f);
	glUniform3f(glGetUniformLocation(_shaders.at("basic").getProgram(), "light.position"), lightPos.x, lightPos.y, lightPos.z);
	glUniform3f(glGetUniformLocation(_shaders.at("basic").getProgram(), "light.ambient"), 0.05f, 0.05f, 0.05f);
	glUniform3f(glGetUniformLocation(_shaders.at("basic").getProgram(), "light.diffuse"), 0.8f, 0.8f, 0.8f);
	glUniform3f(glGetUniformLocation(_shaders.at("basic").getProgram(), "light.specular"), 1.0f, 1.0f, 1.0f);
	glUniform1f(glGetUniformLocation(_shaders.at("basic").getProgram(), "light.constant"), 0.5f);
	glUniform1f(glGetUniformLocation(_shaders.at("basic").getProgram(), "light.linear"), 0.06f);
	glUniform1f(glGetUniformLocation(_shaders.at("basic").getProgram(), "light.quadratic"), 0.012f);
}

void CWindow::setModelMatrix(const glm::mat4& matrix)
{
	static GLint uniModel;
	uniModel = glGetUniformLocation(_shaders.at("basic").getProgram(), "model");
	glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(matrix));
}

void CWindow::render(const std::vector<Vertex>& vertices, const BatchConfig& config)
{
	CBatch* emptyBatchPtr = nullptr;
	CBatch* fullestBatch = _batches[0].get();

	for (unsigned int i = 0; i < _numBatches; ++i)
	{
		CBatch* batch = _batches[i].get();

		if (batch->matchesConfig(config))
		{
			if (!batch->isEnoughRoom(vertices.size()))
			{
				emptyBatch(batch);
			}

			batch->add(vertices);
			return;
		}

		if (emptyBatchPtr == nullptr && batch->isEmpty())
			emptyBatchPtr = batch;

		fullestBatch = batch->getFuller(fullestBatch);
	}

	if (emptyBatchPtr != nullptr)
	{
		emptyBatchPtr->add(vertices, config);
		return;
	}

	emptyBatch(fullestBatch);
	fullestBatch->add(vertices, config);
}

void CWindow::emptyAllBatches()
{
	emptyBatch(_batches[0].get(), true);
}

void CWindow::swapBuffers()
{
	glfwSwapBuffers(_window);
	//std::cout << "numBatches: " << counter << std::endl;
	counter = 0;
}

void CWindow::emptyBatch(CBatch* batchToEmpty, bool emptyAll)
{
	std::priority_queue<CBatch*, std::vector<CBatch*>, CompareBatch> queue;

	for (unsigned int i = 0; i < _numBatches; i++)
	{
		if (!_batches[i]->isEmpty())
		{
			if (emptyAll)
				queue.push(_batches[i].get());
			else if (_batches[i]->getPriority() < batchToEmpty->getPriority())
				queue.push(_batches[i].get());
		}
	}

	while (!queue.empty())
	{
		CBatch* batch = queue.top();
		batch->render();
		counter++;
		queue.pop();
	}

	if (!emptyAll)
	{
		counter++;
		batchToEmpty->render();
	}
}

void CWindow::keyCallback(GLFWwindow* handle, int key, int scancode, int action, int mods)
{
	CGame *game = static_cast<CGame*>(glfwGetWindowUserPointer(handle));

	game->handleInput(key, action);

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(handle, GL_TRUE);
	else if (key == GLFW_KEY_F1 && action == GLFW_PRESS)
		SOIL_save_screenshot("screenshot.bmp", SOIL_SAVE_TYPE_BMP, 0, 0, 1280, 720);
	else if (key == GLFW_KEY_W && action == GLFW_PRESS)
		CService::getCamera()->move(FORWARD);
	else if (key == GLFW_KEY_S && action == GLFW_PRESS)
		CService::getCamera()->move(BACKWARD);
	else if (key == GLFW_KEY_A && action == GLFW_PRESS)
		CService::getCamera()->move(LEFT);
	else if (key == GLFW_KEY_D && action == GLFW_PRESS)
		CService::getCamera()->move(RIGHT);
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

	static GLboolean firstMouse = true;
	static GLfloat lastX, lastY;
	 
	if (firstMouse)
	{
		lastX = (GLfloat)x;
		lastY = (GLfloat)y;
		firstMouse = false;
	}

	GLfloat xOffset = (GLfloat)(x - lastX);
	GLfloat yOffset = (GLfloat)(lastY - y);

	lastX = (GLfloat)x;
	lastY = (GLfloat)y;

	CService::getCamera()->lookAround(xOffset, yOffset);
}

void CWindow::scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	CService::getCamera()->zoom((GLfloat)yoffset);
}

/*void CWindow::drawObject(GLfloat* vertices, GLint size, glm::vec4 color, GLint mode, std::string program)
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

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	//glBindFragDataLocation(_shaders.at("basic").getProgram(), 0, "outColor");
	_shaders.at("basic").useProgram();

	glm::mat4 viewMatrix;
	viewMatrix = CService::getCamera()->getViewMatrix();
	//glm::mat4 projMatrix = glm::ortho<float>(0, 1280, 0, 720);
	glm::mat4 projMatrix = glm::perspective(30.0f, (float)1280 / (float)720, 0.01f, 100.0f);

	GLint uniModel = glGetUniformLocation(_shaders.at("basic").getProgram(), "model");
	GLint uniView = glGetUniformLocation(_shaders.at("basic").getProgram(), "view");
	GLint uniProj = glGetUniformLocation(_shaders.at("basic").getProgram(), "proj");
	GLint uniColor = glGetUniformLocation(_shaders.at("basic").getProgram(), "color");

	glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(projMatrix));
	glUniform4f(uniColor, color.r, color.g, color.b, color.a);

	glm::mat4 modelMatrix;
	//modelMatrix = glm::rotate(modelMatrix, (GLfloat)(glfwGetTime()*100.0), glm::vec3(0.0f, 0.0f, 1.0f));
	glBindVertexArray(vao);

	glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	glDrawArrays(mode, 0, numberOfElements);

	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
	glBindVertexArray(0);
}
*/