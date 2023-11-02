#pragma once

#include <unordered_map>

#include <Oasis/Resources/Resource.h>

namespace Oasis {

	class ResourceManager
	{
	private:
		static std::unordered_map<std::string, Resource*> s_Resources;
	public:
		static void Init();
		static void Shutdown();

		template<typename T>
		static Resource* Load(const std::string& path);
		static Resource* Get(const std::string& path);
		static void Unload(const std::string& path);
	};

}