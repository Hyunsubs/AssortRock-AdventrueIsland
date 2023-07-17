#include "yhTitleAnimation.h"
#include "yhTime.h"
#include "yhTransform.h"
#include "yhResources.h"
#include "yhGameObject.h"
#include "yhAnimator.h"
#include "yhSceneChanger.h"
#include "yhSceneManager.h"
#include "yhBackGround.h"
#include "yhObject.h"
#include "yhSpriteRenderer.h"

namespace yh
{

	TitleAnimation::TitleAnimation()
	{
	}

	TitleAnimation::~TitleAnimation()
	{
	}

	void TitleAnimation::Initialize()
	{
		SceneChanger* changer = object::Instantiate<SceneChanger>(eLayerType::Background);
		BackGround* tri_up = object::Instantiate<BackGround>(eLayerType::Background);
		Transform* tr = tri_up->GetComponent<Transform>();
		tr->SetPosition(Vector2(256.0f, 256.0f));

		Texture* image = Resources::Load<Texture>(L"title", L"..\\Resources\\Image\\Title\\titlescreen.bmp");

		Animator* up_at = tri_up->AddComponent<Animator>();
		up_at->CreateAnimation(L"TriUpAnim",image,Vector2(0.0f,40.0f),Vector2(30.0f,40.0f),9);
		up_at->PlayAnimation(L"TriUpAnim",false);

		

	}

	void TitleAnimation::Update()
	{
		Scene::Update();

		float time = m_change_time;
		time += Time::DeltaTime();
		m_change_time = time;
		if (m_change_time >= 10.0f)
		{
			SceneManager::LoadScene(L"TitleScene");
		}

	}

	void TitleAnimation::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
}

