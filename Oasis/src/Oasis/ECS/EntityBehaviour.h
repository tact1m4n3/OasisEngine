#pragma once

#include <Oasis/ECS/Entity.h>

namespace Oasis {
	
	class Scene;

	class EntityBehaviour
	{
		friend class Scene;
	private:
		Entity m_Entity;
	public:
		virtual void OnAwake() {}
		virtual void OnUpdate() {}
		virtual void OnDestroy() {}
	};

}