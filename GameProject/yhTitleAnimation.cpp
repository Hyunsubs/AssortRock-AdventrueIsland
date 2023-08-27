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
#include "yhBackGroundAnimation.h"
#include "yhSound.h"
#include "yhBgmManager.h"

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
		BgmManager::Init();

		SceneChanger* changer = object::Instantiate<SceneChanger>(eLayerType::Background);
		BackGroundAnimation* tri_up = object::Instantiate<BackGroundAnimation>(eLayerType::Background);
		BackGroundAnimation* tri_left = object::Instantiate<BackGroundAnimation>(eLayerType::Background);
		BackGroundAnimation* tri_right = object::Instantiate<BackGroundAnimation>(eLayerType::Background);
		Transform* up = tri_up->GetComponent<Transform>();
		up->SetPosition(Vector2(256.0f, 25.0f));
		Transform* left = tri_left->GetComponent<Transform>();
		left->SetPosition(Vector2(0.0f, 512.0f));
		Transform* right = tri_right->GetComponent<Transform>();
		right->SetPosition(Vector2(512.0f, 512.0f));
	

		Animator* up_at = tri_up->AddComponent<Animator>();
		Animator* left_at = tri_left->AddComponent<Animator>();
		Animator* right_at = tri_right->AddComponent<Animator>();

		up_at->CreateAnimationFolder(L"TriUpAnim",L"..\\Resources\\Image\\Title\\TriforceParts",Vector2::Zero,0.085f);
		left_at->CreateAnimationFolder(L"TriLeftAnim", L"..\\Resources\\Image\\Title\\TriforceParts", Vector2::Zero, 0.085f);
		right_at->CreateAnimationFolder(L"TriRightAnim", L"..\\Resources\\Image\\Title\\TriforceParts", Vector2::Zero, 0.085f);
		up_at->SetScale(Vector2(2.0f, 2.0f));
		left_at->SetScale(Vector2(2.0f, 2.0f));
		right_at->SetScale(Vector2(2.0f, 2.0f));
		up_at->PlayAnimation(L"TriUpAnim",false);
		left_at->PlayAnimation(L"TriLeftAnim", false);
		right_at->PlayAnimation(L"TriRightAnim", false);
		
		Sound* sound = Resources::Load<Sound>(L"TitleSound",L"..\\Resources\\sound\\Title\\Title.wav");
		sound->Play(false);

	}

	void TitleAnimation::Update()
	{
		Scene::Update();

		float time = m_change_time;
		time += Time::DeltaTime();
		m_change_time = time;
		if (m_change_time >= 6.2f)
		{
			SceneManager::LoadScene(L"TitleScene");
		}

	}

	void TitleAnimation::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
}

