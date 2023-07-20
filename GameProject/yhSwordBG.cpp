#include "yhSwordBG.h"
#include "yhTransform.h"
#include "yhTime.h"
namespace yh
{
	SwordBG::SwordBG()
	{
	}
	SwordBG::~SwordBG()
	{
	}
	void SwordBG::Initialize()
	{
	}
	void SwordBG::Update()
	{

		GameObject::Update();
		Transform* tr = GetComponent<Transform>();
		Vector2 temp = tr->GetPosition();
		if (temp.y < 255.0f)
		{
			temp.y += 300.0f * Time::DeltaTime();
			tr->SetPosition(temp);
		}

	}
	void SwordBG::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}