#include "yhGreenKnight.h"
#include "yhAnimator.h"
#include "yhTransform.h"
#include "yhTexture.h"
#include "yhCollider.h"

namespace yh
{
	GreenKnight::GreenKnight()
	{
		Animator* anim = AddComponent<Animator>();
		Collider* col = AddComponent<Collider>();

		anim->CreateAnimationFolder(L"movingBack", L"..\\Resources\\Image\\Monster\\GreenKnight\\Moving\\Backward");
		col->SetSize(Vector2(50.0f, 50.0f));
		anim->SetScale(Vector2(2.0f, 2.0f));
		anim->PlayAnimation(L"movingBack", true);
	}
	GreenKnight::~GreenKnight()
	{
	}
	void GreenKnight::Initialize()
	{
		
	}
	void GreenKnight::Update()
	{
		GameObject::Update();
	}
	void GreenKnight::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void GreenKnight::OnCollisionEnter(Collider* other)
	{
		
	}
	void GreenKnight::OnCollisionStay(Collider* other)
	{
	}
	void GreenKnight::OnCollisionExit(Collider* other)
	{
	}
}