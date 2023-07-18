#include "yhSceneChanger.h"
#include "yhTransform.h"
#include "yhInput.h"
#include "yhTime.h"
#include "yhScene.h"
#include "yhSceneManager.h"

yh::SceneChanger::SceneChanger()
{
}

yh::SceneChanger::~SceneChanger()
{
}

void yh::SceneChanger::Initialize()
{
}

void yh::SceneChanger::Update()
{

	if (Input::GetKey(eKeyCode::Z))
	{
		SceneManager::LoadScene(L"PlayScene");
	}

	else if (Input::GetKey(eKeyCode::X))

	{
		SceneManager::LoadScene(L"EndingScene");
	}

	else if (Input::GetKey(eKeyCode::C))
	{
		SceneManager::LoadScene(L"TitleScene");
	}

	else if (Input::GetKey(eKeyCode::V))
	{
		SceneManager::LoadScene(L"TitleAnimScene");
	}


}

void yh::SceneChanger::Render(HDC hdc)
{
}
