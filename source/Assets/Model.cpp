#include "Model.h"
#include <iostream>

namespace RenderToy
{
	Model::Model(std::string path)
	{
		LoadModel(path);
	}

	void Model::Draw(ShaderProgram shader, Camera& camera)
	{
		for (size_t i = 0; i < m_Meshes.size(); i++)
		{
			m_Meshes[i].Draw(shader, camera);
		}
	}

	void Model::LoadModel(std::string path)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
			return;
		}

		m_Directory = path.substr(0, path.find_last_of('/'));
		std::cout << m_Directory << std::endl;

		ProcessNode(scene->mRootNode, scene);
	}

	void Model::ProcessNode(aiNode* node, const aiScene* scene)
	{
		for (size_t i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			m_Meshes.push_back(ProcessMesh(mesh, scene));
		}
		for (size_t i = 0; i < node->mNumChildren; i++)
		{
			ProcessNode(node->mChildren[i], scene);
		}
	}

	Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
	{
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<Texture> textures;

		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex vertex;

			vertex.position = glm::vec3(
				mesh->mVertices[i].x,
				mesh->mVertices[i].y,
				mesh->mVertices[i].z);

			vertex.normal = glm::vec3(
				mesh->mNormals[i].x,
				mesh->mNormals[i].y,
				mesh->mNormals[i].z
			);

			if (mesh->mTextureCoords[0]) // if it has texture coords
			{
				vertex.textureCoords = glm::vec2(
					mesh->mTextureCoords[0][i].x,
					mesh->mTextureCoords[0][i].y
				);
			}
			else vertex.textureCoords = glm::vec2(0.0f, 0.0f);

			vertices.push_back(vertex);
		}

		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++)
			{
				indices.push_back(face.mIndices[j]);
			}
		}

		if (mesh->mMaterialIndex >= 0)
		{
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

			std::vector<Texture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
			textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

			std::vector<Texture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
			textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		}

		return Mesh(vertices, indices, textures);
	}

	std::vector<Texture> Model::LoadMaterialTextures(aiMaterial* material, aiTextureType type, std::string typeName)
	{
		std::vector<Texture> textures;

		for (unsigned int i = 0; i < material->GetTextureCount(type); i++)
		{
			aiString materialTexture;
			material->GetTexture(type, i, &materialTexture);

			bool skip = false;
			for (unsigned int j = 0; j < m_LoadedTextures.size(); j++)
			{
				if (m_LoadedTextures[j].Path == materialTexture.C_Str())
				{
					skip = true;
					break;
				}
			}

			if (skip) continue;

			Texture texture(m_Directory + "/" + materialTexture.C_Str());
			texture.Type = typeName;
			texture.Path = materialTexture.C_Str();
			textures.push_back(texture);

			m_LoadedTextures.push_back(texture);
		}

		return textures;
	}

}