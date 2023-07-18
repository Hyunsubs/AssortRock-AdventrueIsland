#include "yhBackGroundAnimation.h"
#include "yhTransform.h"
#include "yhTime.h"

yh::BackGroundAnimation::BackGroundAnimation()
{
}

yh::BackGroundAnimation::~BackGroundAnimation()
{
}

void yh::BackGroundAnimation::Initialize()
{
}

void yh::BackGroundAnimation::Update()
{
	GameObject::Update();
	Transform* tr = GetComponent<Transform>();
	if (tr->GetPosition().y < 250.0f)
	{
		Vector2 temp = tr->GetPosition();
		temp.y += 30.0f * Time::DeltaTime();
		tr->SetPosition(temp);
	}

	else if (tr->GetPosition().y > 256.0f && tr->GetPosition().x < 250.0f)
	{
		Vector2 temp = tr->GetPosition();
		temp.y -= 30.0f * Time::DeltaTime();
		temp.x += 30.0f * Time::DeltaTime();
		tr->SetPosition(temp);
	}

	else if (tr->GetPosition().y > 256.0f && tr->GetPosition().x > 256.0f)
	{
		Vector2 temp = tr->GetPosition();
		temp.y -= 30.0f * Time::DeltaTime();
		temp.x -= 30.0f * Time::DeltaTime();
		tr->SetPosition(temp);
	}


}

void yh::BackGroundAnimation::Render(HDC hdc)
{
	GameObject::Render(hdc);
}
