#include "yhSceneManager.h"
#include "yhTitle.h"
#include "yhPlay.h"
#include "yhHouse.h"
#include "yhTitleAnimation.h"

namespace yh
{
	std::map<std::wstring, Scene*> SceneManager::mScenes = {};
	Scene* SceneManager::mActiveScenes = nullptr;

	void yh::SceneManager::Initialize()
	{
		SceneManager::CreateScene<Title>(L"TitleScene");
		SceneManager::CreateScene<Play>(L"PlayScene");
		SceneManager::CreateScene<House>(L"HouseScene");
		SceneManager::CreateScene<TitleAnimation>(L"TitleAnimScene");

		LoadScene(L"TitleAnimScene");
	}

	void yh::SceneManager::Update()
	{
		mActiveScenes->Update();
	}

	void yh::SceneManager::Render(HDC hdc)
	{
		mActiveScenes->Render(hdc);
	}

	Scene* SceneManager::LoadScene(const std::wstring& name)
	{
		std::map<std::wstring, Scene*>::iterator iter = 
			mScenes.find(name);

		if (iter == mScenes.end())
			return nullptr;

		mActiveScenes = iter->second;

		return iter->second;
	}

}

