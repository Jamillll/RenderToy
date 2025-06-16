#include "Renderer.h"
#include <glad/glad.h>

#include "../Assets/Model.h"
#include "../Entities/Object.h"

namespace RenderToy
{
	std::unique_ptr<Framebuffer> Renderer::m_Framebuffer = nullptr;
	std::unique_ptr<Camera> Renderer::m_Camera = nullptr;

	ShaderProgram* Renderer::temp_ModelShader;

	void Renderer::Initialise(float windowWidth, float windowHeight)
	{
		m_Camera = std::make_unique<Camera>(windowWidth, windowHeight);
		m_Framebuffer = std::make_unique<Framebuffer>(windowWidth, windowHeight);

		temp_ModelShader = new ShaderProgram(RESOURCES_PATH "shaders/modelCombined.shader");
	}

	void Renderer::Submit(EntityHandle entityHandle)
	{
		Entity* entity = EntityManager::GetEntityByHandle(entityHandle);

		switch (entity->Type)
		{
		case EntityType::NULLENTITY:
			break;

		case EntityType::OBJECT:
			{
				Object* object = (Object*)entity;

				Model* model = (Model*)AssetManager::GetAssetByHandle(object->GetModel());
				model->Draw(*temp_ModelShader, *m_Camera, *object->GetTransformData());
			}
			break;

		default:
			break;
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