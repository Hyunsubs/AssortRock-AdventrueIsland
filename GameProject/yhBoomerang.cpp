#include "yhBoomerang.h"
#include "yhTransform.h"
#include "yhSpriteRenderer.h"
#include "yhAnimator.h"
#include "yhResources.h"
#include "yhCollider.h"
#include "yhTime.h"
#include "yhInput.h"

namespace yh
{
	Boomerang::Boomerang() :
		  col(nullptr)
		, direction(Directions::End)
		, state(BoomerangState::Idle)
		, boomerang_anim(nullptr)
		, flying_time(FLYING_TIME)
	{
		this->SetState(eState::Pause);
		wstring playing_item_path = PLAYING_ITEMS_PATH;
		col = AddComponent<Collider>();
		boomerang_anim = AddComponent<Animator>();
		tr = GetComponent<Transform>();
		boomerang_anim->CreateAnimationFolder(L"BoomerangAnim", playing_item_path + L"Boomerang", Vector2::Zero, 0.05f);
		boomerang_anim->SetScale(Vector2::Double);
		boomerang_anim->PlayAnimation(L"BoomerangAnim", true);
	}

	Boomerang::~Boomerang()
	{
	}


	void Boomerang::Initialize()
	{
	}


	void Boomerang::Update()
	{
		GameObject::Update();

		switch (state)
		{
		case yh::Boomerang::BoomerangState::Idle:
			Idle();
			break;
		case yh::Boomerang::BoomerangState::Move:
			Move();
			break;
		case yh::Boomerang::BoomerangState::MoveBack:
			MoveBack(player_pos);
			break;
		case yh::Boomerang::BoomerangState::Death:
			Death();
			break;
		default:
			break;
		}

	}
	void Boomerang::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Boomerang::OnCollisionEnter(Collider* other)
	{
	}
	void Boomerang::OnCollisionStay(Collider* other)
	{
	}
	void Boomerang::OnCollisionExit(Collider* other)
	{
	}



	void Boomerang::Idle()
	{
		
	}

	void Boomerang::Move()
	{
		Vector2 cur_pos = tr->GetPosition();
		flying_time -= Time::DeltaTime();


		switch (direction)
		{
		case yh::enums::Directions::Forward:
			cur_pos.y -= 200.0f * Time::DeltaTime();
			break;
		case yh::enums::Directions::UpRight:
			cur_pos.x += 200.0f * Time::DeltaTime();
			cur_pos.y -= 200.0f * Time::DeltaTime();
			break;
		case yh::enums::Directions::UpLeft:
			cur_pos.x -= 200.0f * Time::DeltaTime();
			cur_pos.y -= 200.0f * Time::DeltaTime();
			break;
		case yh::enums::Directions::Backward:
			cur_pos.y += 200.0f * Time::DeltaTime();
			break;
		case yh::enums::Directions::DownRight:
			cur_pos.y += 200.0f * Time::DeltaTime();
			cur_pos.x += 200.0f * Time::DeltaTime();
			break;
		case yh::enums::Directions::DownLeft:
			cur_pos.y += 200.0f * Time::DeltaTime();
			cur_pos.x -= 200.0f * Time::DeltaTime();
			break;
		case yh::enums::Directions::Left:
			cur_pos.x -= 200.0f * Time::DeltaTime();
			break;
		case yh::enums::Directions::Right:
			cur_pos.x += 200.0f * Time::DeltaTime();
			break;
		case yh::enums::Directions::End:
			break;
		default:
			break;
		}
		tr->SetPosition(cur_pos);

		if (flying_time <= 0.0f)
		{
			flying_time = FLYING_TIME;
			state = BoomerangState::MoveBack;
		}
	}

	void Boomerang::MoveBack(Vector2 player_pos)
	{
		Vector2 cur_pos = tr->GetPosition();
		if (cur_pos.x > player_pos.x)
			cur_pos.x -= 200.0f * Time::DeltaTime();
		else
			cur_pos.x += 200.0f * Time::DeltaTime();
		if (cur_pos.y > player_pos.y)
			cur_pos.y -= 200.0f * Time::DeltaTime();
		else
			cur_pos.y += 200.0f * Time::DeltaTime();
		tr->SetPosition(cur_pos);
		if (abs(cur_pos.x - player_pos.x) <= 5.0f && abs(cur_pos.y - player_pos.y) <= 5.0f)
		{
			state = BoomerangState::Death;
		}

	}



	void Boomerang::Death()
	{
		SetState(eState::Pause);
		state = BoomerangState::Idle;
	}



}