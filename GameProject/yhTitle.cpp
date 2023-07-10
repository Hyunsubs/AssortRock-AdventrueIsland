#include "yhTitle.h"
#include "yhPlayer.h"
#include "yhSpriteRenderer.h"
#include "yhLayer.h"
#include "yhObject.h"
#include "yhSceneChanger.h"

yh::Title::Title()
{
}

yh::Title::~Title()
{
}

void yh::Title::Initialize()
{
	SceneChanger* changer = object::Instantiate<SceneChanger>(eLayerType::Background);
	Player* player = object::Instantiate<Player>(eLayerType::Player);
	player->AddComponent<SpriteRenderer>();

	

}

void yh::Title::Update()
{
	Scene::Update();
}

void yh::Title::Render(HDC hdc)
{
	Scene::Render(hdc);
	wchar_t text[50] = {};
	swprintf_s(text, 50, L"타이틀 씬입니다");
	int strLen = wcsnlen_s(text, 50);
	TextOut(hdc, 200, 300, text, strLen);
}
