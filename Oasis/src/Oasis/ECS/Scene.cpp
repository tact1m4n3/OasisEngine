#include <Oasis/ECS/Scene.h>

#include <iostream>

#include <glm/gtc/matrix_transform.hpp>

#include <Oasis/Core/Application.h>
#include <Oasis/Renderer/RuntimeCamera.h>
#include <Oasis/Renderer/Renderer2D.h>
#include <Oasis/ECS/Entity.h>
#include <Oasis/ECS/Components.h>
#include <Oasis/Resources/ResourceManager.h>

namespace Oasis {

	Entity Scene::CreateEntity(const std::string& name, const std::string& tag)
	{
		Entity entity(m_Registry.create(), this);
		
		entity.AddComponent<TransformComponent>();
		entity.AddComponent<NameComponent>(name);

		return entity;
	}

	void Scene::DestroyEntity(Entity entity)
	{
		m_Registry.destroy(entity);
	}

	void Scene::OnStartRuntime()
	{
		m_Registry.view<EntityBehaviourComponent>().each([=](auto& entityId, auto& component)
			{
				component.ScriptInstance = component.InstantiateScript();
				component.ScriptInstance->m_Entity = Entity(entityId, this);
				component.ScriptInstance->OnAwake();
			});
	}

	void Scene::OnUpdateRuntime(float deltaTime)
	{
		m_Registry.view<EntityBehaviourComponent>().each([=](auto& entityId, auto& component)
		{
			component.ScriptInstance->OnUpdate();
		});
	}

	void Scene::OnRenderRuntime(float viewportAspect)
	{
		glm::mat4 cameraTransformation(1.0f);
		RuntimeCamera* runtimeCamera = nullptr;

		auto& cameraView = m_Registry.view<CameraComponent>();
		for (auto& entityId : cameraView)
		{
			Entity entity(entityId, this);
			TransformComponent& transform = entity.GetComponent<TransformComponent>();
			CameraComponent& camera = entity.GetComponent<CameraComponent>();
			if (camera.Main && !runtimeCamera)
			{
				cameraTransformation = transform.GetTransformationMatrix();
				runtimeCamera = camera.CameraInstance;
			}
		};

		if (!runtimeCamera)
			return;

		runtimeCamera->SetAspect(viewportAspect);
		runtimeCamera->CalculateProjection();

		Renderer2D::Begin((Camera*)runtimeCamera, glm::inverse(cameraTransformation));

		auto& renderingView = m_Registry.view<TransformComponent, SpriteRendererComponent>();
		for (auto& entityId : renderingView)
		{
			Entity entity(entityId, this);
			TransformComponent& transform = entity.GetComponent<TransformComponent>();
			SpriteRendererComponent& spriteRenderer = entity.GetComponent<SpriteRendererComponent>();

			Texture* tex = (Texture*)ResourceManager::Get(spriteRenderer.TexturePath);
			if (!tex)
				Renderer2D::DrawSprite(transform.GetTransformationMatrix(), spriteRenderer.Color);
			else
				Renderer2D::DrawSprite(transform.GetTransformationMatrix(), tex, spriteRenderer.Color);
		}

		Renderer2D::End();
	}

	void Scene::OnEndRuntime()
	{
		m_Registry.view<EntityBehaviourComponent>().each([=](auto& entityId, auto& component)
			{
				component.ScriptInstance->OnDestroy();
				component.DestroyScript(&component);
			});
	}

	void Scene::OnRenderEditor(EditorCamera* editorCamera)
	{
		Renderer2D::Begin(editorCamera, editorCamera->GetCameraTransformation());

		auto& view = m_Registry.view<TransformComponent, SpriteRendererComponent>();
		for (auto& entityId : view)
		{
			Entity entity(entityId, this);
			TransformComponent& transform = entity.GetComponent<TransformComponent>();
			SpriteRendererComponent& spriteRenderer = entity.GetComponent<SpriteRendererComponent>();

			Texture* tex = (Texture*)ResourceManager::Get(spriteRenderer.TexturePath);
			if (!tex)
				Renderer2D::DrawSprite(transform.GetTransformationMatrix(), spriteRenderer.Color);
			else
				Renderer2D::DrawSprite(transform.GetTransformationMatrix(), tex, spriteRenderer.Color);
		}

		Renderer2D::End();
	}

}
