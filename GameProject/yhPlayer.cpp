#include "yhPlayer.h"
#include "yhTransform.h"
#include "yhInput.h"
#include "yhTime.h"
#include "yhGameObject.h"

yh::Player::Player()
{
}

yh::Player::~Player()
{
}

void yh::Player::Initialize()
{
}

void yh::Player::Update()
{
	GameObject::Update();

	Transform* tr = GetComponent<Transform>();
	Vector2 pos = tr->GetPosition();

	if (Input::GetKey(eKeyCode::W))
	{
		pos.y -= 300.0f * Time::DeltaTime();
	}
	if (Input::GetKey(eKeyCode::A))
	{
		pos.x -= 300.0f * Time::DeltaTime();
	}
	if (Input::GetKey(eKeyCode::S))
	{
		pos.y += 300.0f * Time::DeltaTime();
	}
	if (Input::GetKey(eKeyCode::D))
	{
		pos.x += 300.0f * Time::DeltaTime();
	}
	tr->SetPosition(pos);
}

void yh::Player::Render(HDC hdc)
{
	GameObject::Render(hdc);

}
