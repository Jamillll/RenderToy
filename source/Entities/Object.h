#pragma once
#include "EntityManager.h"
#include "../Assets/AssetManager.h"
#include "../Renderer/Camera.h"

namespace RenderToy
{
	class Object : public Entity
	{
	private:
		AssetHandle m_Model = 0;
		TransformData m_Transform;

	public:
		Object(AssetHandle model);

		TransformData* GetTransformData();
		AssetHandle GetModel();

		~Object();
	};
}