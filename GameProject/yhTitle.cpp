#include "yhTitle.h"
#include "yhPlayer.h"
#include "yhSpriteRenderer.h"
#include "yhLayer.h"
#include "yhObject.h"
#include "yhSceneChanger.h"
#include "yhTexture.h"
#include "yhResources.h"
#include "yhBackGround.h"
#include "yhTransform.h"

yh::Title::Title()
{
}

yh::Title::~Title()
{
}

void yh::Title::Initialize()
{
	using namespace math;
	Texture* image = Resources::Load<Texture>(L"MainBG",L"..\\Resources\\image\\Title\\MainBG.bmp");


	SceneChanger* changer = object::Instantiate<SceneChanger>(eLayerType::Background);
	BackGround* main_bg = object::Instantiate<BackGround>(eLayerType::Background);
	SpriteRenderer* main_bgsr = main_bg->AddComponent<SpriteRenderer>();
	main_bgsr->SetImage(image);
	main_bgsr->SetScale(Vector2(2.0f, 3.12f));
	std::wstring name = main_bg->GetName();


	image = Resources::Load<Texture>(L"TitleBG", L"..\\Resources\\image\\Title\\TitleName.png");
	BackGround* title_bg = object::Instantiate<BackGround>(eLayerType::Background);
	title_bg->GetComponent<Transform>()->SetPosition(Vector2(120.0f, 140.0f));
	SpriteRenderer* title_bgsr = title_bg->AddComponent<SpriteRenderer>();
	title_bgsr->SetImage(image);
	title_bgsr->SetScale(Vector2(1.5f,1.5f));

	image = Resources::Load<Texture>(L"Maker", L"..\\Resources\\image\\Title\\Maker.png");
	BackGround* maker = object::Instantiate<BackGround>(eLayerType::Background);
	maker->GetComponent<Transform>()->SetPosition(Vector2(240.0f, 300.0f));
	SpriteRenderer* maker_sr = maker->AddComponent<SpriteRenderer>();
	maker_sr->SetImage(image);
	
}

void yh::Title::Update()
{
	Scene::Update();
}

void yh::Title::Render(HDC hdc)
{
	Scene::Render(hdc);
}
