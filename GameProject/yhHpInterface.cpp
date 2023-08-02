#include "yhHpInterface.h"
#include "yhTransform.h"
#include "yhTexture.h"
#include "yhResources.h"
#include "yhSpriteRenderer.h"

namespace yh
{

	HpInterface::HpInterface() : image(nullptr)
							   , sr(nullptr)
						       , tr(nullptr)
	{
		sr = AddComponent<SpriteRenderer>();
		tr = GetComponent<Transform>();
		image = Resources::Load<Texture>(L"heartcontainer", L"..\\Resources\\Image\\UI\\Hearts\\heart.png");
		sr->SetImage(image);
		sr->SetScale(Vector2(2.0f, 2.0f));
		SetState(eState::Pause);
	}
	HpInterface::~HpInterface()
	{
	}
	void HpInterface::Initialize()
	{
	}
	void HpInterface::Update()
	{
		GameObject::Update();

	}
	void HpInterface::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void HpInterface::OnCollisionEnter(Collider* other)
	{
	}
	void HpInterface::OnCollisionStay(Collider* other)
	{
	}
	void HpInterface::OnCollisionExit(Collider* other)
	{
	}
}