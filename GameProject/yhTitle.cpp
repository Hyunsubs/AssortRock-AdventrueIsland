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
	main_bg->GetComponent<Transform>()->SetPosition(Vector2(256.0f, 256.0f));
	SpriteRenderer* main_bgsr = main_bg->AddComponent<SpriteRenderer>();
	main_bgsr->SetImage(image);
	main_bgsr->SetScale(Vector2(2.0f, 3.56f));
	std::wstring name = main_bg->GetName();

	image = Resources::Load<Texture>(L"Sword", L"..\\Resources\\image\\Title\\Sword.png");
	BackGround* sword_bg = object::Instantiate<BackGround>(eLayerType::Background);
	sword_bg->GetComponent<Transform>()->SetPosition(Vector2(170.0f, 240.0f));
	SpriteRenderer* sword_bgsr = sword_bg->AddComponent<SpriteRenderer>();
	sword_bgsr->SetImage(image);
	sword_bgsr->SetScale(Vector2(2.0f, 2.0f));

	image = Resources::Load<Texture>(L"Triforce", L"..\\Resources\\image\\Title\\Triforce.png");
	BackGround* tri_bg = object::Instantiate<BackGround>(eLayerType::Background);
	tri_bg->GetComponent<Transform>()->SetPosition(Vector2(256.0f,200.0f));
	SpriteRenderer* tri_bgsr = tri_bg->AddComponent<SpriteRenderer>();
	tri_bgsr->SetImage(image);
	tri_bgsr->SetScale(Vector2(1.7f, 1.7f));

	image = Resources::Load<Texture>(L"TitleBG", L"..\\Resources\\image\\Title\\TitleName.png");
	BackGround* title_bg = object::Instantiate<BackGround>(eLayerType::Player);
	title_bg->GetComponent<Transform>()->SetPosition(Vector2(256.0f, 256.0f));
	SpriteRenderer* title_bgsr = title_bg->AddComponent<SpriteRenderer>();
	title_bgsr->SetImage(image);
	title_bgsr->SetScale(Vector2(1.5f,1.5f));

	
}

void yh::Title::Update()
{
	Scene::Update();
}

void yh::Title::Render(HDC hdc)
{
	Scene::Render(hdc);
}
