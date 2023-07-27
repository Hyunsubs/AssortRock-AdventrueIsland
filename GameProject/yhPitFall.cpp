#include "yhPitFall.h"
#include "yhPlayer.h"
#include "yhAnimator.h"
#include "yhCollider.h"
#include "yhTransform.h"

namespace yh
{
	PitFall::PitFall()
	{
	}
	PitFall::~PitFall()
	{
	}
	void PitFall::Initialize()
	{
	}
	void PitFall::Update()
	{
		GameObject::Update();
	}
	void PitFall::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void PitFall::OnCollisionEnter(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		Animator* anim = player->GetComponent<Animator>();
		Transform* tr = player->GetComponent<Transform>();
		tr->SetPosition(GetComponent<Transform>()->GetPosition());
		anim->PlayAnimation(L"LinkFalling", false);
		player->SetState(Player::PlayerState::Falling);
	}
	void PitFall::OnCollisionStay(Collider* other)
	{
	}
	void PitFall::OnCollisionExit(Collider* other)
	{
	}
}