#pragma once

#include <glm/glm.hpp>

#include <Oasis/Renderer/Shader.h>
#include <Oasis/Renderer/Texture.h>
#include <Oasis/Renderer/Camera.h>

namespace Oasis {

	class Renderer2D
	{
	private:
		struct Vertex
		{
			glm::vec3 Position;
			glm::vec2 TextureCoord;
			glm::vec4 Color;
			float TextureID;
		};

		struct RendererData
		{
			static const uint32_t MaxQuads = 1000;
			static const uint32_t MaxVertices = MaxQuads * 4;
			static const uint32_t MaxIndices = MaxQuads * 6;
			static const uint32_t MaxTextureSlots = 16;

			glm::vec4 QuadVertices[4];

			uint32_t IndexBuffer;
			uint32_t IndexCount;

			uint32_t VertexBuffer;
			Vertex* VertexBufferDataBase;
			Vertex* VertexBufferDataPtr;

			uint32_t VertexArray;

			Shader* Shader;
			Texture* Textures[MaxTextureSlots];
			uint32_t TextureIndex;
		};

		static RendererData s_Data;
	public:
		static void Init();
		static void Shutdown();
		
		static void Begin(Camera* camera, const glm::mat4& cameraTransformation);
		static void End();
		
		static void DrawSprite(const glm::vec3& position, float rotation, const glm::vec3& scale, const glm::vec4& color);
		static void DrawSprite(const glm::vec3& position, float rotation, const glm::vec3& scale, Texture* texture);
		static void DrawSprite(const glm::vec3& position, float rotation, const glm::vec3& scale, Texture* texture, const glm::vec4& color);
		static void DrawSprite(const glm::mat4& modelMat, Texture* texture);
		static void DrawSprite(const glm::mat4& modelMat, const glm::vec4& color);
		static void DrawSprite(const glm::mat4& modelMat, Texture* texture, const glm::vec4& color);
	private:
		static void InitBatch();
		static void Flush();
	};

}
