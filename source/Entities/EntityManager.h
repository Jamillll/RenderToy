#include <glm/glm.hpp>
#include <vector>

namespace RenderToy
{
	// TODO: Complete this
	// The idea im going with right now- at like 6am so it might be dumb- Is to have an entity class
	// that all entities inherit, we'd have an object class (Just a model basically) a light class
	// and then a Camera class, just some ideas, and they'd all inherit from this Entity class
	// that has an overloaded move function and whatever other functions may be needed

	typedef unsigned int EntityHandle;

	class Entity
	{
	public:
		EntityHandle Handle = -1;
		glm::vec3 Position = glm::vec3(0, 0, 0);
	};

	class EntityManager
	{
	private:
		std::vector<Entity> m_Entities;

	public:
		EntityManager();
		~EntityManager();
	};
}