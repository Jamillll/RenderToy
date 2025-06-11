#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <vector>

#include "../Renderer/ShaderProgram.h"
#include "Texture.h"
#include "../Renderer/Camera.h"
#include "../Renderer/VertexArray.h"

namespace RenderToy
{
	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 textureCoords;
	};

	class Mesh
	{
	private:
		VertexArray* m_VAO = nullptr;
		uint32_t m_VBO;
		uint32_t m_EBO;

	public:
		std::vector<Vertex> Vertices;
		std::vector<unsigned int> Indices;
		std::vector<Texture> Textures;

		Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture>& textures);
		void Draw(ShaderProgram shader, Camera& camera);

	private:
		void SetupMesh();
	};
}