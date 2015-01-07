#include <queue>

#include <SOIL.h>

#include "Camera.h"
#include "Renderer.h"
#include "Service.h"
#include "Window.h"

CRenderer::CRenderer()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_COLOR);

	for (unsigned int i = 0; i < 10; ++i)
	{
		_batches.push_back(std::shared_ptr<CBatch>(new CBatch()));
		_numBatches++;
	}

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // wireframe, GL_FILL for normal
}

CRenderer::~CRenderer()
{
}

void CRenderer::addShaderProgram(std::string name, CShader program)
{
	_shaders.emplace(name, program);
}

void CRenderer::clear()
{
	static glm::mat4 projMatrix;
	static glm::mat4 viewMatrix;

	static GLint uniView;
	static GLint uniProj;

	//glfwMakeContextCurrent(_window);
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_shaders.at("basic").useProgram();

	projMatrix = glm::perspective(CService::getCamera()->getZoom(), (float)1280 / (float)720, 0.01f, 100.0f);
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
	glUniform1f(glGetUniformLocation(_shaders.at("basic").getProgram(), "light.constant"), 0.4f);
	glUniform1f(glGetUniformLocation(_shaders.at("basic").getProgram(), "light.linear"), 0.12f);
	glUniform1f(glGetUniformLocation(_shaders.at("basic").getProgram(), "light.quadratic"), 0.4f);

	glUniform1f(glGetUniformLocation(_shaders.at("basic").getProgram(), "diffuse"), 0);
	glActiveTexture(GL_TEXTURE0);
}

void CRenderer::emptyAllBatches()
{
	emptyBatch(_batches[0].get(), true);
}

void CRenderer::emptyBatch(CBatch* batchToEmpty, bool emptyAll)
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
		queue.pop();
	}

	if (!emptyAll)
	{
		batchToEmpty->render();
	}
}

GLuint CRenderer::loadTexture(const GLchar* path)
{
	GLuint texture;
	glGenTextures(1, &texture);

	int width, height;
	unsigned char* image;

	image = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGB);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);

	return texture;
}

void CRenderer::render(const std::vector<Vertex>& vertices, const BatchConfig& config)
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

void CRenderer::setModelMatrix(const glm::mat4& matrix)
{

	//static GLint uniModel;
	//uniModel = glGetUniformLocation(_shaders.at("basic").getProgram(), "model");
	//glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(matrix));
}

void CRenderer::swapBuffers()
{
	glfwSwapBuffers(CService::getWindow()->getHandle());
}
