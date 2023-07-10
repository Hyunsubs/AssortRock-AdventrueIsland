#include "yhGameObject.h"
#include "yhTransform.h"
#include "yhSpriteRenderer.h"

yh::GameObject::GameObject() : mComponents()
{
	AddComponent<Transform>();
}

yh::GameObject::~GameObject()
{
}

void yh::GameObject::Initialize()
{
}

void yh::GameObject::Update()
{
	for (Component* comp :mComponents )
	{
		comp->Update();
	}
}

void yh::GameObject::Render(HDC hdc)
{
	for (Component* comp : mComponents)
	{
		comp->Render(hdc);
	}
}
