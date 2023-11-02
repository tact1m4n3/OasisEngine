#include <Oasis/Resources/ResourceManager.h>

#include <Oasis/Debug/Log.h>
#include <Oasis/Renderer/Texture.h>
#include <Oasis/Renderer/Shader.h>

namespace Oasis {

	std::unordered_map<std::string, Resource*> ResourceManager::s_Resources;

	void ResourceManager::Init()
	{
	}

	void ResourceManager::Shutdown()
	{
		for (auto const& [path, res] : s_Resources)
			delete res;
	}

	template<>
	Resource* ResourceManager::Load<Texture>(const std::string& path)
	{
		Resource* res = (Resource*)new Texture(path);
		if (res->Failed())
		{
			OASIS_LOG_ERROR("Failed to load texture resource from '%s'...", path);
			delete res;
			return nullptr;
		}
		s_Resources[path] = res;
		return res;
	}

	template<>
	Resource* ResourceManager::Load<Shader>(const std::string& path)
	{
		Resource* res = (Resource*)new Shader(path + "/vert.glsl", path + "/frag.glsl");
		if (res->Failed())
		{
			OASIS_LOG_ERROR("Failed to load shader resource from '%s'...", path);
			delete res;
			return nullptr;
		}
		s_Resources[path] = res;
		return res;
	}

	Resource* ResourceManager::Get(const std::string& path)
	{
		if (!(s_Resources.find(path) != s_Resources.end()))
		{
			return nullptr;
		}

		return s_Resources[path];
	}

	void ResourceManager::Unload(const std::string& path)
	{
		if (!(s_Resources.find(path) != s_Resources.end()))
		{
			OASIS_LOG_ERROR("Resource with path '%s' cannot be found. Maybe you forgot to load it first...", path);
			return;
		}

		s_Resources.erase(path);
	}

}