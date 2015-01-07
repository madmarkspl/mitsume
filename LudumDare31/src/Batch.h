#pragma once

#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>

struct Vertex
{
	glm::vec3 _position;
	glm::vec3 _normal;
	glm::vec4 _color;
	glm::vec2 _texture;
	glm::vec3 _transform;

	Vertex() {}

	Vertex(glm::vec3 position, glm::vec3 transform, glm::vec3 _normal, glm::vec4 color, glm::vec2 texture = glm::vec2()) :
		_position(position), _transform(transform), _color(color), _texture(texture) {}
};

struct BatchConfig
{
	GLuint _renderType;
	GLint _priority;
	GLuint _textureID;
	glm::mat4 _transformMatrix;

	BatchConfig() {}

	BatchConfig(GLuint renderType, GLint priority, GLuint textureId) :
		_renderType(renderType), _priority(priority), _textureID(textureId) {}

	bool operator==(const BatchConfig& other) const
	{
		if (_renderType != other._renderType ||
			_priority != other._priority ||
			_textureID != other._textureID ||
			_transformMatrix != other._transformMatrix)
		{
			return false;
		}

		return true;
	}

	bool operator!=(const BatchConfig& other) const
	{
		return !(*this == other);
	}
};

class CBatch final
{
public:
	CBatch(GLuint maxVertices = 1000);
	~CBatch();

	bool matchesConfig(const BatchConfig& config) const;
	bool isEmpty() const;
	bool isEnoughRoom(GLuint numVertices);
	CBatch* getFuller(CBatch* batch);
	GLint getPriority() const;

	void add(const std::vector<Vertex>& vertices, const BatchConfig& config);
	void add(const std::vector<Vertex>& vertices);
	void render();

private:
	CBatch(const CBatch& batch);
	CBatch& operator=(const CBatch& batch);

	void cleanUp();

	GLuint _maxNumVertices;
	GLuint _numUsedVertices;
	GLuint _vao;
	GLuint _vbo;
	BatchConfig _config;
	Vertex _lastVertex;
};

struct CompareBatch
{
	bool operator() (const CBatch* batchA, const CBatch* batchB) const
	{
		return (batchA->getPriority() > batchB->getPriority());
	}
};