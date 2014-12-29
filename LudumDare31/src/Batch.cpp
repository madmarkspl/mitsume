#include <exception>
#include "Batch.h"
#include "Service.h"
#include "Window.h"

CBatch::CBatch(GLuint maxVertices) :
_maxNumVertices(maxVertices), _numUsedVertices(0),
	_vao(0), _vbo(0), _config(GL_TRIANGLE_STRIP, 0, 0),
	_lastVertex(glm::vec3(), glm::vec3(), glm::vec4())
{
	glGetError();

	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, _maxNumVertices * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

	GLuint offset = 0;

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(offset));
	glEnableVertexAttribArray(0);
	offset += sizeof(glm::vec3);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(offset));
	glEnableVertexAttribArray(1);
	offset += sizeof(glm::vec3);

	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(offset));
	glEnableVertexAttribArray(2);
	offset += sizeof(glm::vec4);

	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(offset));
	glEnableVertexAttribArray(3);

	glBindVertexArray(0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	if (GL_NO_ERROR != glGetError())
	{
		cleanUp();
		throw new std::exception(std::string(__FUNCTION__ + std::string(" failed to create batch")).c_str());
	}
}

CBatch::~CBatch()
{
	cleanUp();
}

bool CBatch::matchesConfig(const BatchConfig& config) const
{
	return (config == _config);
}

bool CBatch::isEmpty() const
{
	return (0 == _numUsedVertices);
}

bool CBatch::isEnoughRoom(GLuint numVertices)
{
	GLuint numExtraVertices = (GL_TRIANGLE_STRIP == _config._renderType && _numUsedVertices > 0 ? 2 : 0);

	return (_numUsedVertices + numExtraVertices + numVertices <= _maxNumVertices);
}

CBatch* CBatch::getFuller(CBatch* batch)
{
	return (_numUsedVertices > batch->_numUsedVertices? this : batch);
}

GLint CBatch::getPriority() const
{
	return _config._priority;
}

void CBatch::add(const std::vector<Vertex>& vertices, const BatchConfig& config)
{
	_config = config;
	add(vertices);
}

void CBatch::add(const std::vector<Vertex>& vertices)
{
	GLuint numExtraVertices = (GL_TRIANGLE_STRIP == _config._renderType && _numUsedVertices > 0 ? 2 : 0);

	if (numExtraVertices + vertices.size() > _maxNumVertices - _numUsedVertices)
		throw new std::exception(std::string(__FUNCTION__ + std::string(" not enough room for vertices.")).c_str());

	if (vertices.size() > _maxNumVertices)
		throw new std::exception(std::string(__FUNCTION__ + std::string(" vertex array too big.")).c_str());

	if (vertices.empty())
		throw new std::exception(std::string(__FUNCTION__ + std::string(" vertex array empty!")).c_str());

	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);

	if (numExtraVertices > 0)
	{
		glBufferSubData(GL_ARRAY_BUFFER, _numUsedVertices * sizeof(Vertex), sizeof(Vertex), &_lastVertex);
		glBufferSubData(GL_ARRAY_BUFFER, (_numUsedVertices + 1) * sizeof(Vertex), sizeof(Vertex), &vertices[0]);
	}

	glBufferSubData(GL_ARRAY_BUFFER, (_numUsedVertices + numExtraVertices) * sizeof(Vertex), vertices.size() * sizeof(Vertex), &vertices[0]);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	_numUsedVertices += vertices.size() + numExtraVertices;
	_lastVertex = vertices[vertices.size() - 1];
}

void CBatch::render()
{
	if (_numUsedVertices == 0)
		return;

	CService::getGraphics()->setModelMatrix(_config._transformMatrix);

	glBindVertexArray(_vao);
	glDrawArrays(_config._renderType, 0, _numUsedVertices);
	glBindVertexArray(0);

	_numUsedVertices = 0;
	_config._priority = 0;
}

void CBatch::cleanUp()
{
	if (_vbo != 0)
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDeleteBuffers(1, &_vbo);
		_vbo = 0;
	}

	if (_vao != 0)
	{
		glBindVertexArray(0);
		glDeleteVertexArrays(1, &_vao);
		_vao = 0;
	}
}