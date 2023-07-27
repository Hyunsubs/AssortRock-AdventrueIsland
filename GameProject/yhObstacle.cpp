#include "yhObstacle.h"
#include "yhPlayer.h"
#include "yhRigidbody.h"
#include "yhTransform.h"
#include "yhCollider.h"
#include "yhAnimator.h"
namespace yh
{
	Obstacle::Obstacle()
	{
	}
	Obstacle::~Obstacle()
	{
	}
	void Obstacle::Initialize()
	{
	}
	void Obstacle::Update()
	{
		GameObject::Update();
	}
	void Obstacle::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Obstacle::OnCollisionEnter(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		Animator* anim = player->GetComponent<Animator>();
		anim->PlayAnimation(L"LinkCarrying", false);
		player->SetState(Player::PlayerState::Carrying);

	}
	void Obstacle::OnCollisionStay(Collider* other)
	{
	}
	void Obstacle::OnCollisionExit(Collider* other)
	{
	}
}