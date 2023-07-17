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

	Texture* image = Resources::Load<Texture>(L"nameinput", L"..\\Resources\\Image\\UI\\NameInput.png");
	BackGround* bg = object::Instantiate<BackGround>(eLayerType::Background);
	bg->GetComponent<Transform>()->SetPosition(Vector2(256.0f, 256.0f));
	SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();
	bgsr->SetImage(image);
	bgsr->SetScale(Vector2(2.0f, 2.3f));
	bgsr->SetAffectCamera(false);

	image = Resources::Load<Texture>(L"names", L"..\\Resources\\Image\\Title\\letters.png");
	BackGround* letter = object::Instantiate<BackGround>(eLayerType::Background);
	letter->GetComponent<Transform>()->SetPosition(Vector2(256.0f, 360.0f));
	SpriteRenderer* letter_sr = letter->AddComponent<SpriteRenderer>();
	letter_sr->SetImage(image);
	letter_sr->SetScale(Vector2(2.0f, 2.3f));
	letter_sr->SetAffectCamera(false);


	


}

void yh::NameInput::Update()
{
	Scene::Update();
}

void yh::NameInput::Render(HDC hdc)
{
	Scene::Render(hdc);
}
