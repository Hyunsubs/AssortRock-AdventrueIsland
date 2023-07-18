#pragma once
#include "yhGameObject.h"

namespace yh
{
	class FadeInBackground : public GameObject
	{
	public:
		FadeInBackground();
		virtual ~FadeInBackground();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
		float time = 0.0f;
	};
}