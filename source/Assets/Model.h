#pragma once
#include <string>
#include <vector>
#include "../Renderer/ShaderProgram.h"
#include "Mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace RenderToy
{
	class Model
	{
	private:
		std::vector<Mesh> m_Meshes;
		std::vector<Texture> m_LoadedTextures;
		std::string m_Directory;

	public:
		Model(std::string path);
		void Draw(ShaderProgram shader, Camera& camera);

	private:
		void LoadModel(std::string path);
		void ProcessNode(aiNode* node, const aiScene* scene);
		Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
		std::vector<StrippedTexture> LoadMaterialTextures(aiMaterial* material, aiTextureType type, std::string typeName);
	};
}