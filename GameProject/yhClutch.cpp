#include "yhClutch.h"
#include "yhClutchParts.h"
#include "yhTexture.h"
#include "yhTransform.h"
#include "yhCollider.h"
#include "yhObject.h"
#include "yhTime.h"
#include "yhInput.h"
#include "yhMonsterTemplate.h"


namespace yh
{
	Clutch::Clutch() :
		  direction(Directions::End)
		, tr(nullptr)
		, clutches({})
		, execute_time(0.5f)
		, state(MainClutchState::Pause)
	{
		tr = GetComponent<Transform>();
		ClutchParts* clutch_start = object::Instantiate<ClutchParts>(eLayerType::Sword);
		clutch_start->SetDirection(direction);
		clutch_start->SetTypes(ClutchTypes::Start);
		clutch_start->SetState(eState::Pause);
		clutches.push_back(clutch_start);
		for (int i = 0; i < 8; i++)
		{
			ClutchParts* clutch_middle = object::Instantiate<ClutchParts>(eLayerType::Sword);
			clutch_middle->SetTypes(ClutchTypes::Middle);
			clutch_middle->SetState(eState::Pause);
			clutches.push_back(clutch_middle);
		}
		ClutchParts* clutch_end = object::Instantiate<ClutchParts>(eLayerType::Sword);
		clutch_end->SetTypes(ClutchTypes::End);
		clutch_end->SetState(eState::Pause);
		clutches.push_back(clutch_end);
		SetState(eState::Active);
	}

	Clutch::~Clutch()
	{
	}

	void Clutch::Initialize()
	{
	}

	void Clutch::Update()
	{
		GameObject::Update();
		switch (state)
		{
		case yh::MainClutchState::Pause:
			Pause();
			break;
		case yh::MainClutchState::Move:
			Move();
			break;
		case yh::MainClutchState::MoveBack:
			MoveBack();
			break;
		default:
			break;
		}
	}

	void Clutch::Render(HDC hdc)
	{
		GameObject::Render(hdc);

	}

	void Clutch::OnCollisionEnter(Collider* other)
	{
		MonsterTemplate* monster = dynamic_cast<MonsterTemplate*>(other->GetOwner());
		if (monster != nullptr)
		{
			monster->SetClutch(true);
			Transform* clutch_tr = clutches[9]->GetComponent<Transform>();
			Transform* monster_tr = monster->GetComponent<Transform>();
			monster_tr->SetPosition(clutch_tr->GetPosition());
		}
	}

	void Clutch::OnCollisionStay(Collider* other)
	{
		MonsterTemplate* monster = dynamic_cast<MonsterTemplate*>(other->GetOwner());
		if (monster != nullptr)
		{
			Transform* clutch_tr = clutches[9]->GetComponent<Transform>();
			Transform* monster_tr = monster->GetComponent<Transform>();
			monster_tr->SetPosition(clutch_tr->GetPosition());
		}
	}

	void Clutch::OnCollisionExit(Collider* other)
	{
		MonsterTemplate* monster = dynamic_cast<MonsterTemplate*>(other->GetOwner());
		if (monster != nullptr)
		{
			monster->SetClutch(false);
		}
	}

	void Clutch::Pause()
	{
		for (int i = 0; i < 10; i++)
		{
			Transform* clutch_tr = clutches[i]->GetComponent<Transform>();
			clutch_tr->SetPosition(tr->GetPosition());
			clutches[i]->SetState(eState::Pause);
		}
	}

	void Clutch::Move()
	{
		for (int i = 0; i < 10; i++)
		{
			clutches[i]->SetDirection(direction);
			clutches[i]->SetState(eState::Active);
			Transform* clutch_tr = clutches[i]->GetComponent<Transform>();
			Vector2 cur_pos = clutch_tr->GetPosition();
			switch (direction)
			{
			case yh::enums::Directions::Forward:
				cur_pos.y -= (30.0f * i) * Time::DeltaTime();
				break;
			case yh::enums::Directions::Backward:
				cur_pos.y += (30.0f * i) * Time::DeltaTime();
				break;
			case yh::enums::Directions::Left:
				cur_pos.x -= (30.0f * i) * Time::DeltaTime();
				break;
			case yh::enums::Directions::Right:
				cur_pos.x += (30.0f * i) * Time::DeltaTime();
				break;
			case yh::enums::Directions::End:
				break;
			default:
				break;
			}
			clutch_tr->SetPosition(cur_pos);
		}

		execute_time -= Time::DeltaTime();
		if (execute_time <= 0.0f)
		{
			state = MainClutchState::MoveBack;
			execute_time = 0.5f;
		}
			
	}

	void Clutch::MoveBack()
	{
		execute_time -= Time::DeltaTime();
		if (execute_time <= 0.0f)
		{
			state = MainClutchState::Pause;
			execute_time = 0.5f;
		}

		for (int i = 0; i < 10; i++)
		{
			Transform* clutch_tr = clutches[i]->GetComponent<Transform>();
			Vector2 cur_pos = clutch_tr->GetPosition();
			switch (direction)
			{
			case yh::enums::Directions::Forward:
				cur_pos.y += (30.0f * i) * Time::DeltaTime();
				break;
			case yh::enums::Directions::Backward:
				cur_pos.y -= (30.0f * i) * Time::DeltaTime();
				break;
			case yh::enums::Directions::Left:
				cur_pos.x += (30.0f * i) * Time::DeltaTime();
				break;
			case yh::enums::Directions::Right:
				cur_pos.x -= (30.0f * i) * Time::DeltaTime();
				break;
			case yh::enums::Directions::End:
				break;
			default:
				break;
			}
			clutch_tr->SetPosition(cur_pos);
		}
	}

}