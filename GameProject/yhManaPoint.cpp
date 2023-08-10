#include "yhManaPoint.h"
#include "yhTransform.h"
#include "yhSpriteRenderer.h"
#include "yhTexture.h"
#include "yhPlayer.h"
#include "yhObject.h"
#include "yhCollider.h"
#include "yhResources.h"
#include "yhGameObject.h"
#include "yhCollider.h"
namespace yh
{
	ManaPoint::ManaPoint()
		: image(nullptr)
		, sr(nullptr)
		, tr(nullptr)
	{
		col = AddComponent<Collider>();
		image = Resources::Load<Texture>(L"ManaPoint", L"..\\Resources\\ManaPoint.bmp");
		sr = AddComponent<SpriteRenderer>();
		sr->SetImage(image);
		sr->SetScale(Vector2(2.0f, 2.0f));
		col->SetSize(Vector2(20.0f, 20.0f));
	}
	ManaPoint::~ManaPoint()
	{
	}
	void ManaPoint::Initialize()
	{
	}
	void ManaPoint::Update()
	{
		GameObject::Update();
	}
	void ManaPoint::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void ManaPoint::OnCollisionEnter(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		int mp = player->GetMp();
		if (mp > 6)
			mp = 6;
		if (mp <= 0)
			mp = 0;
		mp++;
		player->SetMp(mp);
		Destroy(this);
	}
	void ManaPoint::OnCollisionStay(Collider* other)
	{
	}
	void ManaPoint::OnCollisionExit(Collider* other)
	{
	}
}