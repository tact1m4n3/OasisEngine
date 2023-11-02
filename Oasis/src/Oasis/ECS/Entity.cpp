#include <Oasis/ECS/Entity.h>

namespace Oasis {

	Entity::Entity(entt::entity entityId, Scene* scene)
		: m_EntityId(entityId), m_Scene(scene)
	{
	}

}