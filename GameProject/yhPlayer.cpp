#include "yhPlayer.h"
#include "yhTransform.h"
#include "yhInput.h"
#include "yhTime.h"
#include "yhAnimator.h"
#include "yhSpriteRenderer.h"
#include "yhResources.h"



namespace yh
{
	Player::Player()
	{
	}

	Player::~Player()
	{
	}

	void Player::Initialize()
	{

	}




	void Player::Update()
	{
		GameObject::Update();

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		Animator* anim = GetComponent<Animator>();

		//GetKey statement
		CheckKey(tr,anim);
		//키업 Statement
		CheckKeyUp(anim);
		//키다운 Statement
		CheckKeyDown(anim);


		
	}

	void Player::Render(HDC hdc)
	{
		GameObject::Render(hdc);

	}

	void Player::CheckKeyDown(Animator* anim)
	{
		if (Input::GetKeyDown(eKeyCode::W))
		{
			anim->PlayAnimation(L"LinkBackward", true);
		}
		if (Input::GetKeyDown(eKeyCode::A))
		{
			anim->PlayAnimation(L"LinkLeft", true);
		}
		if (Input::GetKeyDown(eKeyCode::S))
		{
			anim->PlayAnimation(L"LinkForward", true);
		}
		if (Input::GetKeyDown(eKeyCode::D))
		{
			anim->PlayAnimation(L"LinkRight", true);
		}
	}

	void Player::CheckKeyUp(Animator* anim)
	{
		if (Input::GetKeyUp(eKeyCode::W))
		{
			anim->PlayAnimation(L"LinkIdleUp", false);
		}
		if (Input::GetKeyUp(eKeyCode::A))
		{
			anim->PlayAnimation(L"LinkIdleLeft", false);
		}
		if (Input::GetKeyUp(eKeyCode::S))
		{
			anim->PlayAnimation(L"LinkIdleDown", false);
		}
		if (Input::GetKeyUp(eKeyCode::D))
		{
			anim->PlayAnimation(L"LinkIdleRight", false);
		}

		
	}

	void Player::CheckKey(Transform* tr,Animator* anim)
	{
		Vector2 pos = tr->GetPosition();

		if (Input::GetKey(eKeyCode::W))
		{
			pos.y -= 120.0f * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::A))
		{
			pos.x -= 120.0f * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::S))
		{
			pos.y += 120.0f * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::D))
		{
			pos.x += 120.0f * Time::DeltaTime();
		}
		tr->SetPosition(pos);
	}




}


