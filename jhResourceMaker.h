#pragma once

namespace jh
{
	class ResourceMaker final
	{
	public:
		
		static ResourceMaker& GetInstance()
		{
			static ResourceMaker instance;
			return instance;
		}

		ResourceMaker(const ResourceMaker& other) = delete;
		ResourceMaker& operator=(const ResourceMaker& other) = delete;

		void Initialize();
		void createMeshs();
		void createShaders();
		void createTextures();
		void createMaterial();

	private:
		ResourceMaker();
		~ResourceMaker() = default;
	};
}

