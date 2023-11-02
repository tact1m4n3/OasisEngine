#include <Oasis/Renderer/Texture.h>

#include <glad/glad.h>
#include <stb_image.h>

namespace Oasis {

	Texture::Texture(const std::string& path)
	{
		int width, height, channels;

		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		if (!data)
		{
			m_FailedFlag = true;
			return;
		}

		m_Width = (float)width;
		m_Height = (float)height;

		GLenum internalFormat = 0, dataFormat = 0;
		if (channels == 4)
		{
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if (channels == 3)
		{
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}

		if (!(internalFormat & dataFormat))
		{
			m_FailedFlag = true;
			return;
		}

		glGenTextures(1, &m_RendererId);
		
		glBindTexture(GL_TEXTURE_2D, m_RendererId);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, (int)m_Width, (int)m_Height, 0, dataFormat, GL_UNSIGNED_BYTE, data);

		glBindTexture(GL_TEXTURE_2D, 0);

		stbi_image_free(data);
	}

	Texture::Texture(float width, float height)
	{
		m_Width = width;
		m_Height = height;

		glGenTextures(1, &m_RendererId);
		
		glBindTexture(GL_TEXTURE_2D, m_RendererId);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, (int)m_Width, (int)m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &m_RendererId);
	}

	void Texture::Bind(uint32_t slot) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_RendererId);
	}

	void Texture::SetData(void* data)
	{
		glBindTexture(GL_TEXTURE_2D, m_RendererId);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, (int)m_Width, (int)m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

}