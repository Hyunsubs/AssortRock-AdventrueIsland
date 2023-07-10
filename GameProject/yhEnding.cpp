#include "yhEnding.h"
#include "yhLayer.h"
#include "yhObject.h"
#include "yhSceneChanger.h"

yh::Ending::Ending()
{
}

yh::Ending::~Ending()
{
}

void yh::Ending::Initialize()
{
	SceneChanger* changer = object::Instantiate<SceneChanger>(eLayerType::Background);
}

void yh::Ending::Update()
{
	Scene::Update();
}

void yh::Ending::Render(HDC hdc)
{
	Scene::Render(hdc);
	wchar_t text[50] = {};
	swprintf_s(text, 50, L"엔딩 씬입니다");
	int strLen = wcsnlen_s(text, 50);
	TextOut(hdc, 200, 300, text, strLen);
}
