#include "ShaderProgram.h"
#include <fstream>
#include <iostream>

#include <glad/glad.h>

namespace RenderToy
{
	ShaderProgram::ShaderProgram()
	{
		m_ID = NULL;
	}

	ShaderProgram::ShaderProgram(const std::string& CombinedShaderPath)
	{
		m_ID = glCreateProgram();

		std::pair<uint32_t, uint32_t> shaders = ParseCombinedShader(CombinedShaderPath);

		glAttachShader(m_ID, shaders.first);
		glAttachShader(m_ID, shaders.second);
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
		int32_t uniformLocation = glGetUniformLocation(m_ID, name.c_str());
		glUniform4f(uniformLocation, x, y, z, w);
	}

	void ShaderProgram::setI1Uniform(const std::string& name, int32_t value)
	{
		int32_t uniformLocation = glGetUniformLocation(m_ID, name.c_str());
		glUniform1i(uniformLocation, value);
	}

	void ShaderProgram::setMat4Uniform(const std::string& name, int count, bool transpose, float* value)
	{
		int32_t uniformLocation = glGetUniformLocation(m_ID, name.c_str());
		glUniformMatrix4fv(uniformLocation, count, transpose, value);
	}

	ShaderProgram::~ShaderProgram()
	{
	}

	uint32_t ShaderProgram::GenerateShader(const char* shaderSource, uint32_t shaderType)
	{
		uint32_t id = glCreateShader(shaderType);
		glShaderSource(id, 1, &shaderSource, NULL);
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

	uint32_t ShaderProgram::ParseShader(const std::string& shaderPath, uint32_t shaderType)
	{
		std::string source;

		std::ifstream stream(shaderPath);
		std::string currentLine;
		while (getline(stream, currentLine))
		{
			source += currentLine + "\n";
		}

		const char* csource = source.c_str();

		return GenerateShader(csource, shaderType);
	}

	std::pair<uint32_t, uint32_t> ShaderProgram::ParseCombinedShader(const std::string& shaderPath)
	{
		std::string vertexSource;
		std::string fragmentSource;

		std::ifstream stream(shaderPath);
		std::string currentLine;

		bool uploadingVertexShader = false;

		while (getline(stream, currentLine))
		{
			if (currentLine == "#Vertex")
			{
				uploadingVertexShader = true;
				continue;
			}
			else if (currentLine == "#Fragment")
			{
				uploadingVertexShader = false;
				continue;
			}

			if (uploadingVertexShader) vertexSource += currentLine + "\n";
			if (!uploadingVertexShader) fragmentSource += currentLine + "\n";

		}

		const char* cVertexSource = vertexSource.c_str();
		const char* cFragmentSource = fragmentSource.c_str();

		std::pair<uint32_t, uint32_t> ids;

		ids.first = GenerateShader(cVertexSource, GL_VERTEX_SHADER);
		ids.second = GenerateShader(cFragmentSource, GL_FRAGMENT_SHADER);

		return ids;
	}
}

