#include "yhThrowing.h"


namespace yh
{
	Throwing::Throwing()
	{
	}
	Throwing::~Throwing()
	{
	}
	void Throwing::Initialize()
	{
	}
	void Throwing::Update()
	{
		GameObject::Update();
	}
	void Throwing::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Throwing::OnCollisionEnter(Collider* other)
	{
	}
	void Throwing::OnCollisionStay(Collider* other)
	{
	}
	void Throwing::OnCollisionExit(Collider* other)
	{
	}
}