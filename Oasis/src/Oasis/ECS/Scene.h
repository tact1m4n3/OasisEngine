#pragma once

#include <string>

#include <glm/glm.hpp>

#include <entt.hpp>

#include <Oasis/Renderer/EditorCamera.h>

namespace Oasis {

	class Entity;

	class Scene
	{
		friend class Entity;
	private:
		entt::registry m_Registry;
	public:
		Scene() = default;
		~Scene() = default;

		Entity CreateEntity(const std::string& name, const std::string& tag = "Default");
		void DestroyEntity(Entity entity);

		void OnStartRuntime();
		void OnUpdateRuntime(float deltaTime);
		void OnRenderRuntime(float viewportAspect);
		void OnEndRuntime();

		void OnRenderEditor(EditorCamera* editorCamera);

		inline const entt::registry& GetRegistry() const { return m_Registry; }
	};

}