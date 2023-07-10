#include "yhPlay.h"
#include "yhLayer.h"
#include "yhObject.h"
#include "yhSceneChanger.h"


yh::Play::Play()
{
}

yh::Play::~Play()
{
}

void yh::Play::Initialize()
{
	SceneChanger* changer = object::Instantiate<SceneChanger>(eLayerType::Background);
}

void yh::Play::Update()
{
	Scene::Update();
}

void yh::Play::Render(HDC hdc)
{
	Scene::Render(hdc);
	wchar_t text[50] = {};
	swprintf_s(text, 50, L"�÷��� ���Դϴ�");
	int strLen = wcsnlen_s(text, 50);
	TextOut(hdc, 200, 300, text, strLen);
}
