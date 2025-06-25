#pragma once
#include <string>
#include <vector>
#include <memory>

#include "../Renderer/Renderer.h"
#include "../Renderer/Mesh.h"

#include <assimp/scene.h>

namespace RenderToy
{
	class Model : public Asset
	{
	private:
		std::vector<Mesh> m_Meshes;
		std::vector<std::shared_ptr<Texture>> m_LoadedTextures;
		std::string m_Directory;

	public:
		Model(std::string path);
		void Draw(ShaderProgram shader, Camera& camera, TransformData transform);

	private:
		void LoadModel(std::string path);
		void ProcessNode(aiNode* node, const aiScene* scene);
		Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
		std::vector<std::shared_ptr<Texture>> LoadMaterialTextures(aiMaterial* material, aiTextureType type, std::string typeName);
	};
}