#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>

class CShader
{
public:
	CShader(const GLchar* vertexPath, const GLchar* fragmentPath)
	{
			std::string vertexCode;
			std::string fragmentCode;
			try
			{
					std::ifstream vShaderFile(vertexPath);
					std::ifstream fShaderFile(fragmentPath);
					std::stringstream vShaderStream, fShaderStream;

					vShaderStream << vShaderFile.rdbuf();
					fShaderStream << fShaderFile.rdbuf();
	
					vShaderFile.close();
					fShaderFile.close();

					vertexCode = vShaderStream.str();
					fragmentCode = fShaderStream.str();
			}
			catch (std::exception e)
			{
					std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
			}
			const GLchar* vShaderCode = vertexCode.c_str();
			const GLchar * fShaderCode = fragmentCode.c_str();
			// 2. Compile shaders
			GLuint vertex, fragment;
			GLint success;
			GLchar infoLog[512];
			// Vertex Shader
			vertex = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(vertex, 1, &vShaderCode, NULL);
			glCompileShader(vertex);
			// Print compile errors if any
			glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
			if (!success)
			{
					glGetShaderInfoLog(vertex, 512, NULL, infoLog);
					std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
			}
			// Fragment Shader
			fragment = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(fragment, 1, &fShaderCode, NULL);
			glCompileShader(fragment);
			// Print compile errors if any
			glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
			if (!success)
			{
					glGetShaderInfoLog(fragment, 512, NULL, infoLog);
					std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
			}
			// Shader Program
			_program = glCreateProgram();
			glAttachShader(_program, vertex);
			glAttachShader(_program, fragment);
			glLinkProgram(_program);
			// Print linking errors if any
			glGetProgramiv(_program, GL_LINK_STATUS, &success);
			if (!success)
			{
					glGetProgramInfoLog(_program, 512, NULL, infoLog);
					std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
			}
			// Delete the shaders as they're linked into our program now and no longer necessery
			glDeleteShader(vertex);
			glDeleteShader(fragment);

	}
	// Uses the current shader
	void useProgram() { glUseProgram(_program); }

	GLuint getProgram() { return _program; }

private:
	GLuint _program;
};