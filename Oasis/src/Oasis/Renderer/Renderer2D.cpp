#include <Oasis/Renderer/Renderer2D.h>

#include <vector>
#include <cstring>
#include <glad/glad.h>

#include <glm/gtc/matrix_transform.hpp>

namespace Oasis {

	Renderer2D::RendererData Renderer2D::s_Data;

	void Renderer2D::Init()
	{
		s_Data.QuadVertices[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		s_Data.QuadVertices[1] = {  0.5f, -0.5f, 0.0f, 1.0f };
		s_Data.QuadVertices[2] = {  0.5f,  0.5f, 0.0f, 1.0f };
		s_Data.QuadVertices[3] = { -0.5f,  0.5f, 0.0f, 1.0f };

		glGenVertexArrays(1, &s_Data.VertexArray);
		glBindVertexArray(s_Data.VertexArray);

		glGenBuffers(1, &s_Data.IndexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_Data.IndexBuffer);

		uint32_t* indices = new uint32_t[RendererData::MaxIndices];
		int offset = 0;
		for (int i = 0; i < RendererData::MaxIndices; i += 6)
        {
            indices[i + 0] = offset + 0;
            indices[i + 1] = offset + 1;
            indices[i + 2] = offset + 2;

            indices[i + 3] = offset + 2;
            indices[i + 4] = offset + 3;
            indices[i + 5] = offset + 0;

            offset += 4;
        }

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, RendererData::MaxIndices * sizeof(uint32_t), (const void*)indices, GL_STATIC_DRAW);

		delete[] indices;

		glGenBuffers(1, &s_Data.VertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, s_Data.VertexBuffer);

		glBufferData(GL_ARRAY_BUFFER, RendererData::MaxVertices * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (const void*)0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (const void*)(3 * sizeof(float)));
		glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (const void*)(5 * sizeof(float)));
		glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (const void*)(9 * sizeof(float)));

		s_Data.VertexBufferDataBase = new Vertex[RendererData::MaxVertices];

		glBindVertexArray(0);

		s_Data.Shader = new Shader("internal/assets/shaders/textured_quad/vert.glsl", "internal/assets/shaders/textured_quad/frag.glsl");
		s_Data.Shader->Bind();

		for (int i = 0; i < RendererData::MaxTextureSlots; ++i)
		{
			std::string uName = "u_Textures[" + std::to_string(i) + "]";

			s_Data.Shader->SetUniform<int>(uName, i);
		}

		s_Data.Shader->Unbind();

		memset(s_Data.Textures, 0, sizeof(s_Data.Textures));
		s_Data.Textures[0] = new Texture(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		s_Data.Textures[0]->SetData((void*)&whiteTextureData);
	}

	void Renderer2D::Shutdown()
	{
		delete s_Data.Textures[0];
		delete s_Data.Shader;
		delete[] s_Data.VertexBufferDataBase;
		glDeleteVertexArrays(1, &s_Data.VertexArray);
	}

	void Renderer2D::Begin(Camera* camera, const glm::mat4& cameraTransformation)
	{
		InitBatch();

		s_Data.Shader->Bind();
		s_Data.Shader->SetUniform<glm::mat4>("u_ProjectionMatrix", camera->GetProjection());
		s_Data.Shader->SetUniform<glm::mat4>("u_ViewMatrix", cameraTransformation);
		s_Data.Shader->Unbind();
	}

	void Renderer2D::End()
	{
		Flush();
	}

	void Renderer2D::DrawSprite(const glm::vec3& position, float rotation, const glm::vec3& scale, const glm::vec4& color)
	{
		DrawSprite(position, rotation, scale, s_Data.Textures[0], color);
	}

	void Renderer2D::DrawSprite(const glm::vec3& position, float rotation, const glm::vec3& scale, Texture* texture)
	{
		DrawSprite(position, rotation, scale, texture, { 1.0f, 1.0f, 1.0f, 1.0f });
	}

	void Renderer2D::DrawSprite(const glm::vec3& position, float rotation, const glm::vec3& scale, Texture* texture, const glm::vec4& color)
	{
		glm::mat4 modelMat = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0, 0, 1)) * glm::scale(glm::mat4(1.0f), scale);
		
		DrawSprite(modelMat, texture, color);
	}

	void Renderer2D::DrawSprite(const glm::mat4& modelMat, Texture* texture)
	{
		DrawSprite(modelMat, texture, { 1.0f, 1.0f, 1.0f, 1.0f });
	}

	void Renderer2D::DrawSprite(const glm::mat4& modelMat, const glm::vec4& color)
	{
		DrawSprite(modelMat, s_Data.Textures[0], color);
	}

	void Renderer2D::DrawSprite(const glm::mat4& modelMat, Texture* texture, const glm::vec4& color)
	{
		int textureId = -1;
		for (uint32_t i = 0; i < s_Data.TextureIndex; ++i)
		{
			if (s_Data.Textures[i] == texture)
			{
				textureId = i;
				break;
			}
		}

		if (textureId == -1)
		{
			if (s_Data.TextureIndex >= RendererData::MaxTextureSlots)
			{
				Flush();
				InitBatch();
			}

			textureId = s_Data.TextureIndex;
			s_Data.Textures[s_Data.TextureIndex++] = texture;
		}

		if (s_Data.IndexCount >= RendererData::MaxIndices)
		{
			Flush();
			InitBatch();
		}

		s_Data.VertexBufferDataPtr->Position = modelMat * s_Data.QuadVertices[0];
		s_Data.VertexBufferDataPtr->TextureCoord = { 0.0f, 0.0f };
		s_Data.VertexBufferDataPtr->Color = color;
		s_Data.VertexBufferDataPtr->TextureID = (float)textureId;
		s_Data.VertexBufferDataPtr++;

		s_Data.VertexBufferDataPtr->Position = modelMat * s_Data.QuadVertices[1];
		s_Data.VertexBufferDataPtr->TextureCoord = { 1.0f, 0.0f };
		s_Data.VertexBufferDataPtr->Color = color;
		s_Data.VertexBufferDataPtr->TextureID = (float)textureId;
		s_Data.VertexBufferDataPtr++;

		s_Data.VertexBufferDataPtr->Position = modelMat * s_Data.QuadVertices[2];
		s_Data.VertexBufferDataPtr->TextureCoord = { 1.0f, 1.0f };
		s_Data.VertexBufferDataPtr->Color = color;
		s_Data.VertexBufferDataPtr->TextureID = (float)textureId;
		s_Data.VertexBufferDataPtr++;

		s_Data.VertexBufferDataPtr->Position = modelMat * s_Data.QuadVertices[3];
		s_Data.VertexBufferDataPtr->TextureCoord = { 0.0f, 1.0f };
		s_Data.VertexBufferDataPtr->Color = color;
		s_Data.VertexBufferDataPtr->TextureID = (float)textureId;
		s_Data.VertexBufferDataPtr++;

		s_Data.IndexCount += 6;
	}

	void Renderer2D::InitBatch()
	{
		s_Data.IndexCount = 0;
		s_Data.VertexBufferDataPtr = s_Data.VertexBufferDataBase;
		s_Data.TextureIndex = 1;
	}

	void Renderer2D::Flush()
	{
		if (!s_Data.IndexCount)
			return;

		uint32_t dataSize = (uint32_t)((uint8_t*)s_Data.VertexBufferDataPtr - (uint8_t*)s_Data.VertexBufferDataBase);
		glBindBuffer(GL_ARRAY_BUFFER, s_Data.VertexBuffer);
		glBufferSubData(GL_ARRAY_BUFFER, 0, dataSize, (const void*)s_Data.VertexBufferDataBase);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(s_Data.VertexArray);
		s_Data.Shader->Bind();

		for (uint32_t i = 0; i < s_Data.TextureIndex; ++i)
		{
			s_Data.Textures[i]->Bind(i);
		}

		glDrawElements(GL_TRIANGLES, s_Data.IndexCount, GL_UNSIGNED_INT, nullptr);

		s_Data.Shader->Unbind();
		glBindVertexArray(0);
	}

}