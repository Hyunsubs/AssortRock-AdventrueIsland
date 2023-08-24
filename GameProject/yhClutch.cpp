#include "yhClutch.h"
#include "yhClutchParts.h"
#include "yhTexture.h"
#include "yhTransform.h"
#include "yhCollider.h"
#include "yhObject.h"
#include "yhTime.h"
#include "yhInput.h"
#include "yhMonsterTemplate.h"
#include "yhArrghus.h"

namespace yh
{
	Clutch::Clutch() :
		  direction(Directions::End)
		, tr(nullptr)
		, clutches({})
		, execute_time(0.5f)
		, state(MainClutchState::Pause)
		, is_executed(false)
	{
		tr = GetComponent<Transform>();
		col = AddComponent<Collider>();
		ClutchParts* clutch_start = object::Instantiate<ClutchParts>(eLayerType::Clutch);
		clutch_start->SetDirection(direction);
		clutch_start->SetTypes(ClutchTypes::Start);
		clutch_start->SetState(eState::Dead);
		clutches.push_back(clutch_start);
		for (int i = 0; i < 8; i++)
		{
			ClutchParts* clutch_middle = object::Instantiate<ClutchParts>(eLayerType::Clutch);
			clutch_middle->SetTypes(ClutchTypes::Middle);
			clutch_middle->SetState(eState::Dead);
			clutches.push_back(clutch_middle);
		}
		ClutchParts* clutch_end = object::Instantiate<ClutchParts>(eLayerType::Clutch);
		clutch_end->SetTypes(ClutchTypes::End);
		clutch_end->SetState(eState::Dead);
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

	}

	void Clutch::OnCollisionStay(Collider* other)
	{

	}

	void Clutch::OnCollisionExit(Collider* other)
	{

	}

	void Clutch::Pause()
	{
		for (int i = 0; i < 10; i++)
		{
			Transform* clutch_tr = clutches[i]->GetComponent<Transform>();
			clutch_tr->SetPosition(tr->GetPosition());
			clutches[i]->SetState(eState::Dead);
		}
	}

	void Clutch::Move()
	{
		clutches[9]->SetActivated(true);
		if (!is_executed)
		{
			is_executed = true;
			for (int i = 0; i < 10; i++)
			{
				clutches[i] = object::Instantiate<ClutchParts>(eLayerType::Clutch, tr->GetPosition());
				if (i == 0)
				{
					clutches[i]->SetTypes(ClutchTypes::Start);
				}
				else if (i == 9)
				{
					clutches[i]->SetTypes(ClutchTypes::End);
				}
				else
				{
					clutches[i]->SetTypes(ClutchTypes::Middle);
				}
				clutches[i]->SetDirection(direction);
				clutches[i]->SetState(eState::Active);
				Transform* clutch_tr = clutches[i]->GetComponent<Transform>();
				Vector2 cur_pos = clutch_tr->GetPosition();
				switch (direction)
				{
				case yh::enums::Directions::Forward:
					cur_pos.y -= 20.0f;
					break;
				case yh::enums::Directions::Backward:
					cur_pos.y += 20.0f;
					break;
				case yh::enums::Directions::Left:
					cur_pos.x -= 20.0f;
					break;
				case yh::enums::Directions::Right:
					cur_pos.x += 20.0f;
					break;
				case yh::enums::Directions::End:
					break;
				default:
					break;
				}
				clutch_tr->SetPosition(cur_pos);
			}
		}

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
			is_executed = false;
			state = MainClutchState::MoveBack;
			execute_time = 0.5f;
		}
			
	}

	void Clutch::MoveBack()
	{
		for (int i = 0; i < 10; i++)
		{
			Transform* clutch_tr = clutches[i]->GetComponent<Transform>();
			Vector2 cur_pos = clutch_tr->GetPosition();
			switch (direction)
			{
			case yh::enums::Directions::Forward:
				cur_pos.y += (25.0f * i) * Time::DeltaTime();
				break;
			case yh::enums::Directions::Backward:
				cur_pos.y -= (25.0f * i) * Time::DeltaTime();
				break;
			case yh::enums::Directions::Left:
				cur_pos.x += (25.0f * i) * Time::DeltaTime();
				break;
			case yh::enums::Directions::Right:
				cur_pos.x -= (25.0f * i) * Time::DeltaTime();
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
			is_executed = false;
			state = MainClutchState::Pause;
			execute_time = 0.5f;
			clutches[9]->SetActivated(false);
		}

	}

}