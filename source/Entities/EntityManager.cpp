#include "EntityManager.h"
#include "Object.h"

namespace RenderToy
{
	std::vector<std::unique_ptr<Entity>> EntityManager::m_Entities;

	Entity::Entity()
	{
		Handle = 0;
		Type = EntityType::NULLENTITY;
	}

	Entity::Entity(EntityHandle handle, EntityType type)
		: Handle(handle), Type(type) {}

	void EntityManager::Initialise()
	{
		std::unique_ptr<Entity> nullEntity = std::make_unique<Entity>(0, EntityType::NULLENTITY);

		m_Entities.push_back(std::move(nullEntity));
	}

	void EntityManager::CreateObject(EntityType type, AssetHandle model)
	{
		std::unique_ptr<Entity> object = std::make_unique<Object>(model);
		object->Handle = m_Entities.size();
		object->Type = type;

		m_Entities.push_back(std::move(object));
	}

	size_t EntityManager::Size()
	{
		return m_Entities.size();
	}

	Entity* EntityManager::GetEntityByHandle(EntityHandle handleToGet)
	{
		return m_Entities[handleToGet].get();;
	}
	std::string EntityManager::GetNameOfType(EntityType type)
	{
		switch (type)
		{
		case RenderToy::NULLENTITY:
			return "Null Entity";

		case RenderToy::OBJECT:
			return "Object";
		}
	}
}