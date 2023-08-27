#pragma once
#include "yhScene.h"

namespace yh
{
	class SceneManager
	{
	public:
		static void Initialize();
		static void Update();
		static void Render(HDC hdc);

		template <typename T>
		static T* CreateScene(const std::wstring& name)
		{
			T* scene = new T();
			scene->SetName(name);
			mScenes.insert(std::make_pair(name, scene));
			mActiveScenes = scene;
			scene->Initialize();

			return scene;
		}

		static void Release();

		static Scene* LoadScene(const std::wstring& name);
		static Scene* GetActiveScene() { return mActiveScenes; }
	private:
		//트리 자료구조
		static std::map<std::wstring, Scene*> mScenes;
		static Scene* mActiveScenes;
		//key value 구조로 이루어져 있다.
		//key는 데이터를 검색하는 용도
		//value는 실제 우리가 써야 할 데이터

	
	};
}


