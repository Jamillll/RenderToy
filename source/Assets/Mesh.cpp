#include "Mesh.h"
#include <glad/glad.h>
#include <iostream>

namespace RenderToy
{
	Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture>& textures)
	{
		Vertices = vertices;
		Indices = indices;
		Textures = textures;

		SetupMesh();
	}

	void Mesh::Draw(ShaderProgram shader, Camera& camera)
	{
		unsigned int diffuseNr = 1;
		unsigned int specularNr = 1;

		shader.Use();

		glm::mat4 mvp = camera.GenerateMVPMatrix(glm::vec3(0, 0, 0));
		shader.setMat4Uniform("u_MVP", 1, false, glm::value_ptr(mvp));

		for (size_t i = 0; i < Textures.size(); i++)
		{
			glActiveTexture(GL_TEXTURE1 + i);

			std::string number;
			std::string name = Textures[i].Type;
			if (name == "texture_diffuse")
				number = std::to_string(diffuseNr++);
			else if (name == "texture_specular")
				number = std::to_string(specularNr++);

			shader.setI1Uniform((name + number), i + 1);
			glBindTexture(GL_TEXTURE_2D, Textures[i].GetID());
		}

		glActiveTexture(GL_TEXTURE0);

		//for (size_t i = 0; i < Vertices.size(); i++)
		//{
		//	std::cout << i << " = ";
		//	std::cout << "X: " << Vertices[i].position.x << ", ";
		//	std::cout << "Y: " << Vertices[i].position.y << ", ";
		//	std::cout << "Z: " << Vertices[i].position.z;
		//	std::cout << std::endl;
		//}

		m_VAO->Draw();
	}

	void Mesh::SetupMesh()
	{
		BufferLayout layout =
		{
			{"Position", ShaderDataType::Float3},
			{"Normals", ShaderDataType::Float3},
			{"TexCoords", ShaderDataType::Float2}
		};

		m_VAO = new VertexArray(layout);
		m_VAO->UploadVertexData(sizeof(Vertex) * Vertices.size(), Vertices.data(), Vertices.size());

		m_VAO->AddIndexBuffer();
		m_VAO->UploadIndexData(sizeof(unsigned int) * Indices.size(), Indices.data(), Indices.size());
	}
}