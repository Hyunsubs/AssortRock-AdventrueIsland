#include "yhPlay.h"
#include "yhPlayer.h"
#include "yhSpriteRenderer.h"
#include "yhObject.h"
#include "yhInput.h"
#include "yhPlayer.h"
#include "yhSpriteRenderer.h"
#include "yhObject.h"
#include "yhInput.h"
#include "yhTexture.h"
#include "yhTransform.h"
#include "yhResources.h"
#include "yhBackGround.h"
#include "yhCamera.h"
#include "yhAnimator.h"
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
	
	BackGround* stage = object::Instantiate<BackGround>(eLayerType::Background);
	Player* player = object::Instantiate<Player>(eLayerType::Player);
	Transform* tr = player->GetComponent<Transform>();

	tr->SetPosition(Vector2(256.0f, 256.0f));
	tr = stage->GetComponent<Transform>();
	tr->SetPosition(Vector2(256.0f, 256.0f));

	SpriteRenderer* stage_sr = stage->AddComponent<SpriteRenderer>();
	Texture* image = Resources::Load<Texture>(L"stage",L"..\\Resources\\Image\\Maps\\castle_garden.png");

	stage_sr->SetImage(image);
	stage_sr->SetScale(Vector2(2.0f, 2.0f));

	image = Resources::Load<Texture>(L"Link"
		, L"..\\Resources\\Image\\Player\\link1.bmp");

	Animator* at = player->AddComponent<Animator>();
	at->CreateAnimation(L"LinkForward",image,Vector2(0.0f,0.0f),Vector2(17.2f,27.0f),9);
	at->CreateAnimation(L"LinkIdleDown", image, Vector2(0.0f, 0.0f), Vector2(17.2f, 27.0f), 1);
	at->CreateAnimation(L"LinkBackward", image, Vector2(0.0f, 108.0f), Vector2(17.2f, 27.0f), 9);
	at->CreateAnimation(L"LinkIdleUp", image, Vector2(0.0f, 108.0f), Vector2(17.2f, 27.0f), 1);
	at->CreateAnimation(L"LinkRight", image, Vector2(0.0f, 54.0f), Vector2(17.9f, 27.0f), 11);
	at->CreateAnimation(L"LinkIdleRight", image, Vector2(0.0f, 54.0f), Vector2(17.9f, 27.0f), 1);

	image = Resources::Load<Texture>(L"LinkLeftSide", L"..\\Resources\\Image\\Player\\leftside.bmp");
	at->CreateAnimation(L"LinkIdleLeft", image, Vector2(0.0f, 0.0f), Vector2(17.9f, 24.0f), 1);
	at->CreateAnimation(L"LinkLeft", image, Vector2(0.0f, 0.0f), Vector2(17.9f, 24.0f), 12);
	at->SetAffectedCamera(true);
	at->SetScale(Vector2(2.0f,2.0f));

	at->PlayAnimation(L"LinkIdleDown");

	Camera::SetTarget(player);
}

void yh::Play::Update()
{
	Scene::Update();
}

void yh::Play::Render(HDC hdc)
{
	Scene::Render(hdc);
}
