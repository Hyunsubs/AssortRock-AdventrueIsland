#include "yhComponent.h"

yh::Component::Component(eComponentType type) : mType(type),mOwner(nullptr)
{
}

yh::Component::~Component()
{
}

void yh::Component::Initialize()
{
}

void yh::Component::Update()
{
}

void yh::Component::Render(HDC hdc)
{
}


