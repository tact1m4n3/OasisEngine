#pragma once

#include <glm/glm.hpp>

#include <Oasis/Renderer/Texture.h>

namespace Oasis {

	class Framebuffer
	{
	private:
		uint32_t m_RendererId = 0;

		Texture* m_ColorAttachment = nullptr;

		int m_Width;
		int m_Height;
	public:
		Framebuffer(int width, int height);
		~Framebuffer() = default;

		void Bind() const;
		void Unbind() const;

		void Clear(const glm::vec4& color) const;

		void Resize(int width, int height);

		inline int GetWidth() const { return m_Width; }
		inline int GetHeight() const { return m_Height; }
		inline Texture* GetColorAttachment() const { return m_ColorAttachment; }
	};

}
