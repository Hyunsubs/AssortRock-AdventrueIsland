#include "yhPlay.h"
#include "yhLayer.h"
#include "yhObject.h"
#include "yhSceneChanger.h"
#include "yhPlayer.h"


yh::Play::Play()
{
}

yh::Play::~Play()
{
}

void yh::Play::Initialize()
{
	SceneChanger* changer = object::Instantiate<SceneChanger>(eLayerType::Background);
	Player* player = object::Instantiate<Player>(eLayerType::Player);
	player->AddComponent<SpriteRenderer>();
}

void yh::Play::Update()
{
	Scene::Update();
}

void yh::Play::Render(HDC hdc)
{
	Scene::Render(hdc);
}
