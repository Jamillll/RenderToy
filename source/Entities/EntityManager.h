#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <string>

#include "../Assets/AssetManager.h"

namespace RenderToy
{
	// TODO: Complete this
	// The idea im going with right now- at like 6am so it might be dumb- Is to have an entity class
	// that all entities inherit, we'd have an object class (Just a model basically) a light class
	// and then a Camera class, just some ideas, and they'd all inherit from this Entity class
	// that has an overloaded move function and whatever other functions may be needed

	typedef unsigned int EntityHandle;

	enum EntityType
	{
		NULLENTITY = 0,
		OBJECT = 1,
	};

	class Entity
	{
	public:
		EntityHandle Handle = -1;
		EntityType Type = EntityType::NULLENTITY;

		Entity();
		Entity(EntityHandle handle, EntityType type);
	};

	class EntityManager
	{
	private:
		static std::vector<std::unique_ptr<Entity>> m_Entities;

	public:
		
		static void Initialise();

		static void CreateObject(EntityType type, AssetHandle model);
		// Create alternate functions as needed
		//static void CreateObject(EntityType type, Model* model);

		static size_t Size();
		static Entity* GetEntityByHandle(EntityHandle handleToGet);
		static std::string GetNameOfType(EntityType type);
	};
}