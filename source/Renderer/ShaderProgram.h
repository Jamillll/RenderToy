#pragma once
#include <string>

class ShaderProgram
{
private:
	uint32_t m_ID;

public:
	ShaderProgram();
	ShaderProgram(const std::string& VertexShaderPath, const std::string& FragmentShaderPath);

	void InitialiseShaders(const std::string& VertexShaderPath, const std::string& FragmentShaderPath);

	uint32_t GetID();

	void Use();

	void setF4Uniform(const std::string& name, float x, float y, float z, float w);
	void setI1Uniform(const std::string& name, int v0);
	void setMat4Uniform(const std::string& name, int count, bool transpose, float* value);

	~ShaderProgram();

private:
	uint32_t ParseShader(const std::string& shaderPath, int shaderType);
};