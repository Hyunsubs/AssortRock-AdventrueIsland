#include "yhBackGround.h"
#include "yhTransform.h"
#include "yhInput.h"
#include "yhTime.h"

yh::BackGround::BackGround()
{
}

yh::BackGround::~BackGround()
{
}

void yh::BackGround::Initialize()
{
}

void yh::BackGround::Update()
{
	GameObject::Update();
}

void yh::BackGround::Render(HDC hdc)
{
	GameObject::Render(hdc);
}
