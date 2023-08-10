#include "yhScene.h"
#include "yhPlayer.h"
#include "yhSpriteRenderer.h"

yh::Scene::Scene() :
	is_loaded(false)
{
	mLayers.resize((int)eLayerType::End);
}

yh::Scene::~Scene()
{
}

void yh::Scene::Initialize()
{
	
}

void yh::Scene::Update()
{
	for (Layer& layer : mLayers)
	{
		layer.Update();
	}
}

void yh::Scene::Render(HDC hdc)
{
	for (Layer& layer : mLayers)
	{
		layer.Render(hdc);
	}
}


