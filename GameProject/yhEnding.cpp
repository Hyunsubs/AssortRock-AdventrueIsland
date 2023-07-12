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
}
