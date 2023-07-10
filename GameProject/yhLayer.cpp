#include "yhLayer.h"

yh::Layer::Layer()
{
}

yh::Layer::~Layer()
{
}

void yh::Layer::Initialize()
{
}

void yh::Layer::Update()
{
	for (GameObject* obj : mGameObjects)
	{
		obj->Update();
	}
}

void yh::Layer::Render(HDC hdc)
{
	for (GameObject* obj : mGameObjects)
	{
		obj->Render(hdc);
	}
}
