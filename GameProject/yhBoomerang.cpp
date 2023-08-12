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
		, direction(Directions::Backward)
		, state(BoomerangState::Idle)
		, is_Throwing(false)
		, boomerang_anim(nullptr)
		, flying_time(FLYING_TIME)
	{
		std::wstring playing_item_path = PLAYING_ITEMS_PATH;
		col = AddComponent<Collider>();
		boomerang_anim = AddComponent<Animator>();
		tr = GetComponent<Transform>();
		boomerang_anim->CreateAnimationFolder(L"BoomerangAnim", playing_item_path + L"Boomerang", Vector2::Zero, 0.05f);


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
		if (Input::GetKeyDown(eKeyCode::N))
		{
			state = BoomerangState::Move;
		}
	}


	void Boomerang::Move()
	{
		Vector2 cur_pos = tr->GetPosition();
		flying_time -= Time::DeltaTime();
		switch (direction)
		{
		case yh::enums::Directions::Forward:
			cur_pos.y -= 100.0f * Time::DeltaTime();
			break;
		case yh::enums::Directions::UpRight:
			cur_pos.x += 100.0f * Time::DeltaTime();
			cur_pos.y -= 100.0f * Time::DeltaTime();
			break;
		case yh::enums::Directions::UpLeft:
			cur_pos.x -= 100.0f * Time::DeltaTime();
			cur_pos.y -= 100.0f * Time::DeltaTime();
			break;
		case yh::enums::Directions::Backward:
			cur_pos.y += 100.0f * Time::DeltaTime();
			break;
		case yh::enums::Directions::DownRight:
			cur_pos.y += 100.0f * Time::DeltaTime();
			cur_pos.x += 100.0f * Time::DeltaTime();
			break;
		case yh::enums::Directions::DownLeft:
			cur_pos.y += 100.0f * Time::DeltaTime();
			cur_pos.x -= 100.0f * Time::DeltaTime();
			break;
		case yh::enums::Directions::Left:
			cur_pos.x -= 100.0f * Time::DeltaTime();
			break;
		case yh::enums::Directions::Right:
			cur_pos.x += 100.0f * Time::DeltaTime();
			break;
		case yh::enums::Directions::End:
			break;
		default:
			break;
		}
	}

	void Boomerang::MoveBack(Vector2 player_pos)
	{

	}



	void Boomerang::Death()
	{
		Destroy(this);
	}



}