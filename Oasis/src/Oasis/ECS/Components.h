#pragma once

#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <entt.hpp>

#include <Oasis/Renderer/RuntimeCamera.h>
#include <Oasis/ECS/Entity.h>
#include <Oasis/ECS/EntityBehaviour.h>

namespace Oasis {

	struct NameComponent
	{
		std::string Name;

		NameComponent(const std::string& name)
			: Name(name)
		{
		}
	};

	struct TransformComponent
	{
		glm::vec3 Position;
		glm::vec3 Rotation;
		glm::vec3 Scale;

		TransformComponent()
			: Position(0.0f), Rotation(0.0f), Scale(1.0f)
		{
		}

		glm::mat4 GetTransformationMatrix()
		{
			glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)) *
				glm::rotate(glm::mat4(1.0f), glm::radians(Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)) *
				glm::rotate(glm::mat4(1.0f), glm::radians(Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

			return glm::translate(glm::mat4(1.0f), Position) * rotation * glm::scale(glm::mat4(1.0f), Scale);
		}
	};

	struct SpriteRendererComponent
	{
		glm::vec4 Color;
		std::string TexturePath;

		SpriteRendererComponent()
			: Color(1.0f, 1.0f, 1.0f, 1.0f), TexturePath("")
		{
		}
	};

	struct CameraComponent
	{
		bool Main;

		RuntimeCamera* CameraInstance;

		CameraComponent(bool main, bool perspective = true, float fov = 45, float zoom = 1.0f, float aspect = 1.0f, float near = 0.1f, float far = 1000.0f)
			: Main(main), CameraInstance(new RuntimeCamera(perspective, fov, zoom, aspect, near, far))
		{
		}
	};

	struct EntityBehaviourComponent
	{
		EntityBehaviour* ScriptInstance;

		EntityBehaviour* (*InstantiateScript)();
		void (*DestroyScript)(EntityBehaviourComponent* script);
		
		template<typename T>
		void Bind()
		{
			InstantiateScript = []() { return static_cast<EntityBehaviour*>(new T()); };
			DestroyScript = [](EntityBehaviourComponent* component) { delete component->ScriptInstance; component->ScriptInstance = nullptr; };
		}
	};

}