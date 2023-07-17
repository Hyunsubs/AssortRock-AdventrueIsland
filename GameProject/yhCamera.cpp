#include "yhCamera.h"
#include "yhApplication.h"
#include "yhTransform.h"
#include "yhInput.h"
#include "yhTime.h"

extern yh::Application application;

namespace yh
{
	Vector2 Camera::mResolution = Vector2::Zero;
	Vector2 Camera::mLookPosition = Vector2::Zero;
	Vector2 Camera::mDistance = Vector2::Zero;
	GameObject* Camera::mTarget = nullptr;


	void Camera::Initialize()
	{
		mResolution.x = application.GetWidth();
		mResolution.y = application.GetHeight();
		mLookPosition = mResolution / 2.0f;

	}

	void Camera::Update()
	{
		if (Input::GetKey(eKeyCode::W))
		{
			mLookPosition.y -= 120.0f * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::S))
		{
			mLookPosition.x -= 120.0f * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::A))
		{
			mLookPosition.y += 120.0f * Time::DeltaTime();
		}
		if (Input::GetKey(eKeyCode::D))
		{
			mLookPosition.x += 120.0f * Time::DeltaTime();
		}

		if (mTarget)
		{
			Transform* tr = mTarget->GetComponent<Transform>();
			mLookPosition = tr->GetPosition();
		}

		mDistance = mLookPosition - (mResolution / 2.0f);


	}

}
