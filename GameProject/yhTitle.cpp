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
#include "yhAnimator.h"

yh::Title::Title()
{
}

yh::Title::~Title()
{
}

void yh::Title::Initialize()
{
	using namespace math;
	Texture* image = Resources::Load<Texture>(L"MainBG",L"..\\Resources\\Image\\Title\\title_bg.bmp");


	SceneChanger* changer = object::Instantiate<SceneChanger>(eLayerType::Background);
	BackGround* main_bg = object::Instantiate<BackGround>(eLayerType::Background);
	main_bg->GetComponent<Transform>()->SetPosition(Vector2(256.0f, 256.0f));
	SpriteRenderer* main_bgsr = main_bg->AddComponent<SpriteRenderer>();
	main_bgsr->SetImage(image);
	main_bgsr->SetScale(Vector2(2.0f, 3.56f));

	image = Resources::Load<Texture>(L"Sword", L"..\\Resources\\Image\\Title\\sword.bmp");
	BackGround* sword = object::Instantiate<BackGround>(eLayerType::Background);
	sword->GetComponent<Transform>()->SetPosition(Vector2(130.0f, 256.0f));
	SpriteRenderer* sword_bgsr = sword->AddComponent<SpriteRenderer>();
	sword_bgsr->SetImage(image);
	sword_bgsr->SetScale(Vector2(2.0f, 2.0f));

	image = Resources::Load<Texture>(L"Triforce", L"..\\Resources\\Image\\Title\\triforce.bmp");
	BackGround* tri = object::Instantiate<BackGround>(eLayerType::Background);
	tri->GetComponent<Transform>()->SetPosition(Vector2(256.0f, 230.0f));
	SpriteRenderer* tri_bgsr = tri->AddComponent<SpriteRenderer>();
	tri_bgsr->SetImage(image);
	tri_bgsr->SetScale(Vector2(2.0f, 2.0f));

	image = Resources::Load<Texture>(L"Title", L"..\\Resources\\Image\\Title\\title.bmp");
	BackGround* main_title = object::Instantiate<BackGround>(eLayerType::Background);
	main_title->GetComponent<Transform>()->SetPosition(Vector2(256.0f, 256.0f));
	SpriteRenderer* title_bgsr = main_title->AddComponent<SpriteRenderer>();
	title_bgsr->SetImage(image);
	title_bgsr->SetScale(Vector2(2.0f, 2.0f));


	
	
}

void yh::Title::Update()
{
	Scene::Update();
}

void yh::Title::Render(HDC hdc)
{
	Scene::Render(hdc);
}
