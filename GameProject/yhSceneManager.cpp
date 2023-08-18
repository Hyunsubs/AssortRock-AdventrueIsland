#include "yhSceneManager.h"
#include "yhTitle.h"
#include "yhPlay.h"
#include "yhHouse.h"
#include "yhTitleAnimation.h"
#include "yhNearHouseScene.h"
#include "yhInsideCastleFirst.h"
#include "yhInsideCastleSecond.h"
#include "yhInsideCastleThird.h"
#include "yhGetSwordScene.h"
#include "yhArrghusScene.h"

namespace yh
{
	std::map<std::wstring, Scene*> SceneManager::mScenes = {};
	Scene* SceneManager::mActiveScenes = nullptr;

	void yh::SceneManager::Initialize()
	{
		SceneManager::CreateScene<TitleAnimation>(L"TitleAnimScene");
		SceneManager::CreateScene<Title>(L"TitleScene");
		SceneManager::CreateScene<House>(L"HouseScene");
		SceneManager::CreateScene<NearHouseScene>(L"NearHouseScene");
		SceneManager::CreateScene<Play>(L"CastleGardenScene");
		SceneManager::CreateScene<InsideCastleFirst>(L"InsideCastleFirstScene");
		SceneManager::CreateScene<InsideCastleSecond>(L"InsideCastleSecondScene");
		SceneManager::CreateScene<InsideCastleThird>(L"InsideCastleThirdScene");
		SceneManager::CreateScene<GetSwordScene>(L"GetSwordScene");
		SceneManager::CreateScene<ArrghusScene>(L"ArrghusScene");

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

	void SceneManager::Release()
	{
		for (auto iter : mScenes)
		{
			delete iter.second;
			iter.second = nullptr;
		}
	}

	Scene* SceneManager::LoadScene(const std::wstring& name)
	{
		std::map<std::wstring, Scene*>::iterator iter = 
			mScenes.find(name);

		if (iter == mScenes.end())
			return nullptr;
		mActiveScenes->SetLoaded(false);
		mActiveScenes = iter->second;

		return iter->second;
	}

}

