#include <Oasis/Renderer/Framebuffer.h>

#include <glad/glad.h>

namespace Oasis {

	Framebuffer::Framebuffer(int width, int height)
		: m_Width(width), m_Height(height)
	{
		m_ColorAttachment = new Texture(m_Width, m_Height);
		
		glGenFramebuffers(1, &m_RendererId);
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererId);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment->GetRendererId(), 0);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void Framebuffer::Bind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererId);
		glViewport(0, 0, m_Width, m_Height);
	}

	void Framebuffer::Unbind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void Framebuffer::Clear(const glm::vec4& color) const
	{
		glClearColor(color.r, color.g, color.b, color.a);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Framebuffer::Resize(int width, int height)
	{
		m_Width = width;
		m_Height = height;

		delete m_ColorAttachment;
		m_ColorAttachment = new Texture(m_Width, m_Height);

		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererId);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment->GetRendererId(), 0);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

}