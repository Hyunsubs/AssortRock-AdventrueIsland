#include "yhLayer.h"

yh::Layer::Layer()
{
}

yh::Layer::~Layer()
{
	for (GameObject* obj : mGameObjects)
	{
		delete obj;
		obj = nullptr;
	}
}

void yh::Layer::Initialize()
{
}

void yh::Layer::Update()
{
	for (GameObject* obj : mGameObjects)
	{
		if (obj->GetState() == GameObject::eState::Pause)
			continue;

		obj->Update();
	}
}

void yh::Layer::Render(HDC hdc)
{
	for (GameObject* obj : mGameObjects)
	{
		if (obj->GetState() == GameObject::eState::Pause)
			continue;

		obj->Render(hdc);
	}

	for (std::vector<GameObject*>::iterator iter = mGameObjects.begin()
		; iter != mGameObjects.end()
		;)
	{
		if ((*iter)->GetState() == GameObject::eState::Dead)
		{
			iter = mGameObjects.erase(iter);
		}
		else
		{
			iter++;
		}
	}
}
