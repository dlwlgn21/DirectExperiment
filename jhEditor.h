#pragma once

#include "jhGraphics.h"

namespace jh
{
	class DebugObject;
	class Editor final
	{
	public:
		static Editor& GetInstance()
		{
			static Editor instance;
			return instance;
		}

		Editor(const Editor& other) = delete;
		Editor& operator=(const Editor& other) = delete;

		void Initalize();
		void Run();

		void Update();
		void FixedUpdate();
		void Render();
		void Release();
		void DebugRender(const DebugMesh& mesh);

	private:
		Editor() = default;
		~Editor() = default;

	private:
		std::vector<DebugObject*> mDebugObjects;
	};
}

