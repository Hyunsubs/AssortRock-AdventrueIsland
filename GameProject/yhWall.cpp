#include "yhWall.h"
#include "yhObject.h"
#include "yhCollider.h"
#include "yhTransform.h"
#include "yhPlayer.h"
namespace yh
{
	Wall::Wall()
	{
		col = AddComponent<Collider>();

	}
	Wall::~Wall()
	{
	}
	void Wall::Initialize()
	{
	}
	void Wall::Update()
	{
		GameObject::Update();
	}
	void Wall::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Wall::OnCollisionEnter(Collider* other)
	{
		Player* dest = dynamic_cast<Player*>(other->GetOwner());
		Directions cur_direction = dest->GetDirection();
		Transform* tr = dest->GetComponent<Transform>();
		Vector2 cur_pos = tr->GetPosition();

		
		if (cur_direction == yh::Directions::Forward)
		{
			cur_pos.y += 2.0f;
			tr->SetPosition(cur_pos);
			dest->SetState(Player::PlayerState::Move);
		}
		if (cur_direction == yh::Directions::Backward)
		{
			cur_pos.y -= 2.0f;
			tr->SetPosition(cur_pos);
			dest->SetState(Player::PlayerState::Move);
		}
		if (cur_direction == yh::Directions::Left)
		{
			cur_pos.x += 2.0f;
			tr->SetPosition(cur_pos);
			dest->SetState(Player::PlayerState::Move);
		}
		if (cur_direction == yh::Directions::Right)
		{
			cur_pos.x -= 2.0f;
			tr->SetPosition(cur_pos);
			dest->SetState(Player::PlayerState::Move);
		}

		dest->SetIsWall(true);
	}

	//벽에 끼었을때
	void Wall::OnCollisionStay(Collider* other)
	{
		Player* dest = dynamic_cast<Player*>(other->GetOwner());
		Directions cur_direction = dest->GetDirection();
		Transform* player_pos = dest->GetComponent<Transform>();
		Vector2 correction_pos = player_pos->GetPosition();
		Vector2 wall_pos = GetComponent<Transform>()->GetPosition();

		//왼쪽 벽에 끼인 경우
		if ((cur_direction == yh::Directions::Forward || cur_direction == yh::Directions::Backward) && wall_pos.x > correction_pos.x)
		{
			correction_pos.x -= 2.0f;
		}
		//오른쪽 벽에 끼인 경우
		else if ((cur_direction == yh::Directions::Forward || cur_direction == yh::Directions::Backward) && wall_pos.x < correction_pos.x)
		{
			correction_pos.x += 2.0f;
		}
		//위 벽에 끼인 경우
		else if ((cur_direction == yh::Directions::Right || cur_direction == yh::Directions::Left) && wall_pos.y > correction_pos.y)
		{
			correction_pos.y -= 2.0f;
		}
		//아래 벽에 끼인 경우
		else if ((cur_direction == yh::Directions::Right || cur_direction == yh::Directions::Left) && wall_pos.y < correction_pos.y)
		{
			correction_pos.y += 2.0f;
		}

		player_pos->SetPosition(correction_pos);
		
	}


	void Wall::OnCollisionExit(Collider* other)
	{
		Player* dest = dynamic_cast<Player*>(other->GetOwner());
		dest->SetIsWall(false);
	}

	void Wall::SetWallSize(Vector2 size)
	{
		col->SetSize(size);
	}

	
}