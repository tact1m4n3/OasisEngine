#pragma once

#include <string>

#include <Oasis/Resources/Resource.h>

namespace Oasis {

	class Texture : public Resource
	{
	private:
		float m_Width, m_Height;
		uint32_t m_RendererId;
	public:
		Texture(const std::string& path);
		Texture(float width, float height);
		~Texture();

		void Bind(uint32_t slot = 0) const;

		void SetData(void* data);

		inline uint32_t GetRendererId() const { return m_RendererId; }
		inline float GetWidth() const { return m_Width; }
		inline float GetHeight() const { return m_Height; }
	};

}