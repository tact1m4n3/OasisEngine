#pragma once

#include <entt.hpp>

#include <Oasis/Debug/Assert.h>
#include <Oasis/ECS/Scene.h>

namespace Oasis {

	class Entity
	{
		friend class Scene;
	private:
		entt::entity m_EntityId = (entt::entity)-1;
		Scene* m_Scene;
	public:
		Entity() = default;
		Entity(entt::entity entityId, Scene* scene);
		~Entity() = default;

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			OASIS_ASSERT(!HasComponent<T>(), "Entity already has component...");

			return m_Scene->m_Registry.emplace<T>(m_EntityId, std::forward<Args>(args)...);
		}

		template<typename T>
		T& GetComponent()
		{
			OASIS_ASSERT(HasComponent<T>(), "Entity does not have component...");

			return m_Scene->m_Registry.get<T>(m_EntityId);
		}

		template <typename T>
		void RemoveComponent()
		{
			OASIS_ASSERT(HasComponent<T>(), "Entity does not have component...");

			m_Scene->m_Registry.remove<T>(m_EntityId);
		}

		template<typename T>
		bool HasComponent()
		{
			return m_Scene->m_Registry.has<T>(m_EntityId);
		}

		inline operator bool() { return m_EntityId != (entt::entity)-1; }
		inline operator entt::entity() { return m_EntityId; }
		inline operator uint32_t() { return (uint32_t)m_EntityId; }
		inline bool operator==(const Entity& other) { return m_EntityId == other.m_EntityId && m_Scene == other.m_Scene; }

		inline Scene& GetScene() const { return *m_Scene; }
	};

}
