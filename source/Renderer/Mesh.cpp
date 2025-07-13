#include "Mesh.h"
#include <glad/glad.h>
#include <iostream>

namespace RenderToy
{
	Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<std::shared_ptr<Texture>>& textures)
	{
		Vertices = vertices;
		Indices = indices;
		Textures = textures;

		SetupMesh();
	}

	void Mesh::Draw(ShaderProgram shader, Camera& camera, TransformData transform)
	{
		unsigned int diffuseNr = 1;
		unsigned int specularNr = 1;
		unsigned int normalNr = 1;

		shader.Use();

		glm::mat4 mvp = camera.GenerateMVPMatrix(transform);
		shader.setMat4Uniform("u_MVP", 1, false, glm::value_ptr(mvp));

		for (size_t i = 0; i < Textures.size(); i++)
		{
			glActiveTexture(GL_TEXTURE1 + i);

			std::string number;
			std::string name = Textures[i]->Type;
			if (name == "texture_diffuse")
				number = std::to_string(diffuseNr++);
			else if (name == "texture_specular")
				number = std::to_string(specularNr++);
			else if (name == "texture_normal")
				number = std::to_string(normalNr++);


			shader.setI1Uniform((name + number), i + 1);
			glBindTexture(GL_TEXTURE_2D, Textures[i]->GetID());
		}

		//for (size_t i = 0; i < Vertices.size(); i++)
		//{
		//	std::cout << i << " = ";
		//	std::cout << "X: " << Vertices[i].position.x << ", ";
		//	std::cout << "Y: " << Vertices[i].position.y << ", ";
		//	std::cout << "Z: " << Vertices[i].position.z;
		//	std::cout << std::endl;
		//}

		m_VAO->Draw();

		for (size_t i = 0; i < Textures.size(); i++)
		{
			glActiveTexture(GL_TEXTURE1 + i);

			std::string number;
			std::string name = Textures[i]->Type;
			if (name == "texture_diffuse")
				number = std::to_string(diffuseNr++);
			else if (name == "texture_specular")
				number = std::to_string(specularNr++);
			else if (name == "texture_normal")
				number = std::to_string(normalNr++);

			shader.setI1Uniform((name + number), 0);

			glBindTexture(GL_TEXTURE_2D, 0);
		}
		glActiveTexture(GL_TEXTURE0);
	}

	void Mesh::SetupMesh()
	{
		BufferLayout layout =
		{
			{"Position", ShaderDataType::Float3},
			{"Normals", ShaderDataType::Float3},
			{"TexCoords", ShaderDataType::Float2}
		};

		m_VAO = std::make_unique<VertexArray>(layout);

		m_VAO->UploadVertexData(sizeof(Vertex) * Vertices.size(), Vertices.data(), Vertices.size());

		m_VAO->AddIndexBuffer();
		m_VAO->UploadIndexData(sizeof(unsigned int) * Indices.size(), Indices.data(), Indices.size());
	}
}