#include "yhEnding.h"
#include "yhLayer.h"
#include "yhObject.h"
#include "yhSceneChanger.h"
#include "yhTexture.h"
#include "yhBackGround.h"
#include "yhSpriteRenderer.h"
#include "yhTransform.h"
#include "yhResources.h"
#include "yhPlayer.h"
#include "yhCamera.h"

yh::Ending::Ending()
{
}

yh::Ending::~Ending()
{
}

void yh::Ending::Initialize()
{
	SceneChanger* changer = object::Instantiate<SceneChanger>(eLayerType::Background);
	Texture* image = Resources::Load<Texture>(L"garden", L"..\\Resources\\Image\\Maps\\HyruleGarden.png");
	BackGround* bg = object::Instantiate<BackGround>(eLayerType::Background);
	bg->GetComponent<Transform>()->SetPosition(Vector2(256.0f, 256.0f));
	SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();
	bgsr->SetImage(image);
	bgsr->SetScale(Vector2(2.0f, 2.0f));


	image = Resources::Load<Texture>(L"link", L"..\\Resources\\Image\\Link\\Move_Forward\\link1.bmp");
	Player* player = object::Instantiate<Player>(eLayerType::Player);
	player->GetComponent<Transform>()->SetPosition(Vector2(256.0f, 256.0f));
	SpriteRenderer* player_sr = player->AddComponent<SpriteRenderer>();
	player_sr->SetImage(image);
	player_sr->SetScale(Vector2(2.0f, 2.0f));

	
	Camera::SetTarget(player);
	
}

void yh::Ending::Update()
{
	Scene::Update();
}

void yh::Ending::Render(HDC hdc)
{
	Scene::Render(hdc);
}
