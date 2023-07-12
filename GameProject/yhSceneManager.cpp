#include "yhSceneManager.h"
#include "yhTitle.h"
#include "yhPlay.h"
#include "yhEnding.h"
#include "yhNameInput.h"
namespace yh
{
	std::map<std::wstring, Scene*> SceneManager::mScenes = {};
	Scene* SceneManager::mActiveScenes = nullptr;

	void yh::SceneManager::Initialize()
	{
		SceneManager::CreateScene<Title>(L"TitleScene");
		SceneManager::CreateScene<Play>(L"PlayScene");
		SceneManager::CreateScene<Ending>(L"EndingScene");
		SceneManager::CreateScene<NameInput>(L"NameInputScene");


		LoadScene(L"TitleScene");
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

