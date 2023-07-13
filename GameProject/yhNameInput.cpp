#include "yhNameInput.h"
#include "yhLayer.h"
#include "yhObject.h"
#include "yhSceneChanger.h"
#include "yhPlayer.h"
#include "yhTransform.h"
#include "yhResources.h"
#include "yhBackGround.h"
#include "yhTexture.h"
#include "yhSpriteRenderer.h"

yh::NameInput::NameInput()
{
}

yh::NameInput::~NameInput()
{
}

void yh::NameInput::Initialize()
{
	SceneChanger* changer = object::Instantiate<SceneChanger>(eLayerType::Background);

	Texture* image = Resources::Load<Texture>(L"nameinput",L"..\\Resources\\image\\UI\\NameInput.png");
	BackGround* bg = object::Instantiate<BackGround>(eLayerType::Background);
	bg->GetComponent<Transform>()->SetPosition(Vector2(256.0f,256.0f));
	SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();
	bgsr->SetImage(image);
	bgsr->SetScale(Vector2(2.0f, 2.3f));

}

void yh::NameInput::Update()
{
	Scene::Update();
}

void yh::NameInput::Render(HDC hdc)
{
	Scene::Render(hdc);
}
