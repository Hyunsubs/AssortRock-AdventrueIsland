#include "yhStair.h"
#include "yhTransform.h"
#include "yhSpriteRenderer.h"
#include "yhCollider.h"
#include "yhResources.h"
#include "yhPlayer.h"
#include "yhAnimator.h"

namespace yh
{
	Stair::Stair() :
		  tr(nullptr)
		, col(nullptr)
	{
		tr = GetComponent<Transform>();
		col = AddComponent<Collider>();

		col->SetSize(Vector2(40.0f,60.0f));
		
	}
	Stair::~Stair()
	{
	}
	void Stair::Initialize()
	{
	}
	void Stair::Update()
	{
		GameObject::Update();
	}
	void Stair::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Stair::OnCollisionEnter(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		if (player == nullptr)
			return;
		Animator* anim = player->GetComponent<Animator>();
		Directions direct = player->GetDirection();
		Transform* stair_tr = GetComponent<Transform>();
		Vector2 stair_pos = stair_tr->GetPosition();
		Transform* player_tr = player->GetComponent<Transform>();
		player_tr->SetPosition(Vector2(stair_pos.x, player_tr->GetPosition().y));
		switch (direct)
		{
		case yh::enums::Directions::Forward:
			anim->PlayAnimation(L"LinkBackward", true);
			break;
		case yh::enums::Directions::Backward:
			anim->PlayAnimation(L"LinkForward", true);
			break;
		default:
			break;
		}
		player->SetState(Player::PlayerState::In_Stair);
	}

	void Stair::OnCollisionStay(Collider* other)
	{
	}
	void Stair::OnCollisionExit(Collider* other)
	{
	}

	void Stair::SetColSize(Vector2 input)
	{
		col->SetSize(input);
	}

}