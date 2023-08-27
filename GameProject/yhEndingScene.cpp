#include "yhEndingScene.h"
#include "yhAsciiRender.h"
#include "yhObject.h"
#include "yhResources.h"
#include "yhBgmManager.h"
#include "yhCamera.h"
namespace yh
{
	EndingScene::EndingScene() :
		  is_played(false)
	{
	}
	EndingScene::~EndingScene()
	{
	}
	void EndingScene::Initialize()
	{
		ascii = object::Instantiate<AsciiRender>(eLayerType::Background,Vector2(0.0f,0.0f));
		ascii->SetString("THANK YOU FOR PLAYING\nMADE BY HYUNSEOP YUN");
		ascii->PrintAsciis();
		ascii->SetState(GameObject::eState::Pause);
	}
	void EndingScene::Update()
	{
		Camera::SetLookPosition(Vector2(0.0f, 0.0f));
		Camera::SetTarget(nullptr);

		if (!is_played)
		{
			is_played = true;
			BgmManager::PlayIndexSound(BgmTypes::Ending,false);
		}
		Scene::Update();
	}
	void EndingScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
}