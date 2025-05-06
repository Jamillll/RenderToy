#include "ShaderProgram.h"
#include <fstream>
#include <iostream>

#include <glad/glad.h>

ShaderProgram::ShaderProgram()
{
	m_ID = NULL;
}

ShaderProgram::ShaderProgram(const std::string& VertexShaderPath, const std::string& FragmentShaderPath)
{
	InitialiseShaders(VertexShaderPath, FragmentShaderPath);
}

void ShaderProgram::InitialiseShaders(const std::string& VertexShaderPath, const std::string& FragmentShaderPath)
{
	m_ID = glCreateProgram();
	glAttachShader(m_ID, ParseShader(VertexShaderPath, GL_VERTEX_SHADER));
	glAttachShader(m_ID, ParseShader(FragmentShaderPath, GL_FRAGMENT_SHADER));
	glLinkProgram(m_ID);

	int success;
	glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetProgramInfoLog(m_ID, 512, NULL, infoLog);
		std::cout << "ERROR: SHADER PROGRAM FAILED TO LINK" << std::endl << infoLog << std::endl;
	}
}

uint32_t ShaderProgram::GetID()
{
	return m_ID;
}

void ShaderProgram::Use()
{
	if (m_ID == NULL)
	{
		std::cout << "Cannot Use shader that hasn't been initialised" << std::endl;
		return;
	}

	glUseProgram(m_ID);
}

void ShaderProgram::setF4Uniform(const std::string& name, float x, float y, float z, float w)
{
}

void ShaderProgram::setI1Uniform(const std::string& name, int v0)
{
}

void ShaderProgram::setMat4Uniform(const std::string& name, int count, bool transpose, float* value)
{
}

ShaderProgram::~ShaderProgram()
{
}

uint32_t ShaderProgram::ParseShader(const std::string& shaderPath, int shaderType)
{
	std::string source;

	std::ifstream stream(shaderPath);
	std::string currentLine;
	while (getline(stream, currentLine))
	{
		source += currentLine + "\n";
	}

	const char* csource = source.c_str();

	uint32_t id = glCreateShader(shaderType);
	glShaderSource(id, 1, &csource, NULL);
	glCompileShader(id);

	int success;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(id, 512, NULL, infoLog);
		std::cout << "ERROR: SHADER FAILED TO COMPILE" << std::endl << infoLog << std::endl;
	}

	return id;
}
