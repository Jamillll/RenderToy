#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <vector>
#include <memory>

#include "Renderer.h"
#include "../Assets/Texture.h"

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
		std::unique_ptr<VertexArray> m_VAO = nullptr;
		uint32_t m_VBO;
		uint32_t m_EBO;

	public:
		std::vector<Vertex> Vertices;
		std::vector<unsigned int> Indices;
		std::vector<Texture> Textures;

		Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture>& textures);
		void Draw(ShaderProgram shader, Camera& camera, TransformData transform);

	private:
		void SetupMesh();
	};
}