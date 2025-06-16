#include "Object.h"

namespace RenderToy
{
	Object::Object(AssetHandle model)
		: m_Model(model)
	{}

	TransformData* Object::GetTransformData()
	{
		return &m_Transform;
	}

	AssetHandle Object::GetModel()
	{
		return m_Model;
	}

	Object::~Object()
	{
	}
}