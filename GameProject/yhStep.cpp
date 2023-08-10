#include "yhStep.h"
#include "yhTransform.h"
#include "yhCollider.h"
#include "yhPlayer.h"

namespace yh
{
	Step::Step() :
		  tr(nullptr)
		, col(nullptr)
	{
		tr = GetComponent<Transform>();
		col = AddComponent<Collider>();

		col->SetSize(Vector2(20.0f,20.0f));
	}
	Step::~Step()
	{
	}
	void Step::Initialize()
	{
	}
	void Step::Update()
	{
		GameObject::Update();
	}
	void Step::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Step::OnCollisionEnter(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		Transform* player_tr = player->GetComponent<Transform>();
		Vector2 player_pos = player_tr->GetPosition();
		if (player == nullptr)
			return;
		if (player->GetIsDown() == false)
		{
			player_pos.y += 100.0f;
			player->SetIsDown(true);
		}

		player_tr->SetPosition(player_pos);

	}
	void Step::OnCollisionStay(Collider* other)
	{
	}
	void Step::OnCollisionExit(Collider* other)
	{
	}

	void Step::SetColSize(Vector2 input)
	{
		col->SetSize(input);
	}
}