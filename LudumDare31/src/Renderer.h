#pragma once
#include <map>
#include <memory>
#include <string>
#include <vector>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Batch.h"

class CRenderer
{
public:
	CRenderer();
	~CRenderer();

	void addShaderProgram(std::string name, CShader program);
	void clear();
	void emptyAllBatches();
	GLuint loadTexture(const GLchar* path);
	void render(const std::vector<Vertex>& vVertices, const BatchConfig& config);
	void setModelMatrix(const glm::mat4& matrix);
	void swapBuffers();

private:
	void emptyBatch(CBatch* batchToEmpty, bool emptyAll = false);

	std::map<std::string, CShader> _shaders;
	std::vector<std::shared_ptr<CBatch>> _batches;
	GLuint _numBatches;
	GLuint _maxNumVerticesPerBatch;
};

