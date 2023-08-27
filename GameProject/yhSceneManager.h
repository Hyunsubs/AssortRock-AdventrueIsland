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
		//Ʈ�� �ڷᱸ��
		static std::map<std::wstring, Scene*> mScenes;
		static Scene* mActiveScenes;
		//key value ������ �̷���� �ִ�.
		//key�� �����͸� �˻��ϴ� �뵵
		//value�� ���� �츮�� ��� �� ������

	
	};
}


