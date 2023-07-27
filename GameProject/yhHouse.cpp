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
	House::House()
	{
	}
	House::~House()
	{
	}

	void House::Initialize()
	{
		object::Instantiate<SceneChanger>(eLayerType::Background);
		Player* player = object::Instantiate<Player>(eLayerType::Player);

		Transform* tr = player->GetComponent<Transform>();
		tr->SetPosition(Vector2(256.0f, 256.0f));
		
	}

	void House::Update()
	{
		Scene::Update();
	}

	void House::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
}