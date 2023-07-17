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
	std::wstring name = main_bg->GetName();
	main_bgsr->SetAffectCamera(false);

	
	
}

void yh::Title::Update()
{
	Scene::Update();
}

void yh::Title::Render(HDC hdc)
{
	Scene::Render(hdc);
}
