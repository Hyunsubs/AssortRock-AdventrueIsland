#include "yhPlayerShield.h"
#include "yhSpriteRenderer.h"
#include "yhTransform.h"
#include "yhTexture.h"
#include "yhResources.h"
#include "yhAnimator.h"

namespace yh
{

	PlayerShield::PlayerShield() :
		 state(PlayerShield::ShieldState::Idle)
		, image(nullptr)
		, sr(nullptr)
		, tr(nullptr)
		, direction(Directions::Backward)
		, anim(nullptr)
	{
		std::wstring player_path = PLAYER_PATH;
		anim = AddComponent<Animator>();
		tr = AddComponent<Transform>();
		sr = AddComponent<SpriteRenderer>();
		anim->SetScale(Vector2(2.0f, 2.0f));
		image = Resources::Load<Texture>(L"ShieldBackward", player_path + L"Link_Shield\\shield_backward.bmp");
		anim->CreateAnimation(L"ShieldBackwardAnim", image, Vector2(0.0f,0.0f),Vector2(8.0f,10.0f),1,Vector2(-15.0f,7.0f));
		image = Resources::Load<Texture>(L"ShieldForward", player_path + L"Link_Shield\\shield_forward.bmp");
		anim->CreateAnimation(L"ShieldForwardAnim", image, Vector2(0.0f, 0.0f), Vector2(8.0f, 10.0f), 1, Vector2(0.0f, 0.0f));
		image = Resources::Load<Texture>(L"ShieldLeft", player_path + L"Link_Shield\\shield_left.bmp");
		anim->CreateAnimation(L"ShieldLeftAnim", image, Vector2(0.0f, 0.0f), Vector2(4.0f, 10.0f), 1, Vector2(-20.0f, 0.0f));
		image = Resources::Load<Texture>(L"ShieldRight", player_path + L"Link_Shield\\shield_right.bmp");
		anim->CreateAnimation(L"ShieldRightAnim", image, Vector2(0.0f, 0.0f), Vector2(4.0f, 10.0f), 1, Vector2(20.0f, 0.0f));
		
		
		
	}

	PlayerShield::~PlayerShield()
	{
	}
	
	void PlayerShield::Initialize()
	{
	}

	void PlayerShield::Update()
	{
		GameObject::Update();
		
	/*	switch (direction)
		{
		case yh::Directions::Forward:
			anim->PlayAnimation(L"ShieldForwardAnim", false);
			break;
		case yh::Directions::Backward:
			anim->PlayAnimation(L"ShieldBackwardAnim", false);
			break;
		case yh::Directions::Left:
			anim->PlayAnimation(L"ShieldLeftAnim", false);
			break;
		case yh::Directions::Right:
			anim->PlayAnimation(L"ShieldRightAnim", false);
			break;
		default:
			break;
		}*/
	}

	void PlayerShield::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void PlayerShield::Idle()
	{
	}

	void PlayerShield::Move()
	{
	}

	void PlayerShield::Attack()
	{
	}

	void PlayerShield::Death()
	{
	}

	void PlayerShield::Map()
	{
	}

	void PlayerShield::Falling()
	{
	}

	void PlayerShield::Ui()
	{
	}

}