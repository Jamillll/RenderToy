#include "Renderer.h"
#include <glad/glad.h>

#include "../Assets/Model.h"

namespace RenderToy
{
	std::unique_ptr<Framebuffer> Renderer::m_Framebuffer = nullptr;
	std::unique_ptr<Camera> Renderer::m_Camera = nullptr;

	void Renderer::Initialise(float windowWidth, float windowHeight)
	{
		m_Camera = std::make_unique<Camera>(windowWidth, windowHeight);
		m_Framebuffer = std::make_unique<Framebuffer>(windowWidth, windowHeight);
	}

	void Renderer::Submit(AssetHandle assethandle, ShaderProgram shaders, TransformData transform)
	{
		Asset* asset = AssetManager::GetAssetByHandle(assethandle);

		switch (asset->assetType)
		{
		case AssetType::NULLASSET:
			return;

		case AssetType::MODEL:
			Model* model = (Model*)asset;
			model->Draw(shaders, *m_Camera, transform);
		}
	}

	void Renderer::Submit(VertexArray& vao, ShaderProgram shaders, TransformData transform)
	{
		shaders.Use();

		glm::mat4 mvp = m_Camera->GenerateMVPMatrix(transform);
		shaders.setMat4Uniform("u_MVP", 1, false, glm::value_ptr(mvp));
		vao.Draw();
	}

	Camera* Renderer::GetCamera()
	{
		return m_Camera.get();
	}

	uint32_t Renderer::GetFramebufferTextureID()
	{
		return m_Framebuffer->GetFramebufferTextureID();
	}

	void Renderer::StartFrame()
	{
		glEnable(GL_DEPTH_TEST);
		m_Framebuffer->Bind();
		m_Framebuffer->Clear();
	}

	void Renderer::EndFrame()
	{
		m_Framebuffer->Unbind();
		glDisable(GL_DEPTH_TEST);
	}

}