#include "yhHouse.h"
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
#include "yhResources.h"
#include "yhAnimator.h"

namespace yh
{
	House::House() : player(nullptr)
	{
	}
	House::~House()
	{
	}

	void House::Initialize()
	{
		PlayerTemplate::Initialize();

		//배경 세팅
		Texture* image = Resources::Load<Texture>(L"LinkHouseOutside", L"..\\Resources\\Image\\Maps\\link_house.bmp");
		BackGround* bg = object::Instantiate<BackGround>(eLayerType::Background,Vector2(256.0f,256.0f));
		SpriteRenderer* bgsr = bg->AddComponent<SpriteRenderer>();
		bgsr->SetImage(image);
		bgsr->SetScale(Vector2(2.0f, 2.0f));
		

		object::Instantiate<SceneChanger>(eLayerType::Background);
		player = object::Instantiate<Player>(eLayerType::Player);

		

		Transform* tr = player->GetComponent<Transform>();
		tr->SetPosition(Vector2(256.0f, 256.0f));
		
	}

	void House::Update()
	{
		PlayerTemplate::Update(Vector2(512.0f,512.0f));
	}

	void House::Render(HDC hdc)
	{
		PlayerTemplate::Render(hdc);
	}
}