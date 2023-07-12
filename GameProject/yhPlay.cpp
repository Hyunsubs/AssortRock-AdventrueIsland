#include "yhPlay.h"
#include "yhLayer.h"
#include "yhObject.h"
#include "yhSceneChanger.h"
#include "yhPlayer.h"
#include "yhTransform.h"
#include "yhResources.h"
#include "yhBackGround.h"

yh::Play::Play()
{
}

yh::Play::~Play()
{
}

void yh::Play::Initialize()
{
	SceneChanger* changer = object::Instantiate<SceneChanger>(eLayerType::Background);
	Texture* image = Resources::Load<Texture>(L"overworld1", L"..\\Resources\\image\\Maps\\overworld1.bmp");
	BackGround* bg = object::Instantiate<BackGround>(eLayerType::Background);
	SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();
	bgsr->SetImage(image);
	


	image = Resources::Load<Texture>(L"link", L"..\\Resources\\image\\Link\\link1.png");
	Player* player = object::Instantiate<Player>(eLayerType::Player);
	player->GetComponent<Transform>()->SetPosition(Vector2(256.0f,224.0f));
	SpriteRenderer* player_sr = player->AddComponent<SpriteRenderer>();
	player_sr->SetImage(image);
	player_sr->SetScale(Vector2(1.3f, 1.3f));
}

void yh::Play::Update()
{
	Scene::Update();
}

void yh::Play::Render(HDC hdc)
{
	Scene::Render(hdc);
}
