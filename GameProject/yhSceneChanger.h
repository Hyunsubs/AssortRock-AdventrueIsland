#pragma once
#include "yhGameObject.h"


namespace yh
{
	class SceneChanger : public GameObject
	{
	public:
		SceneChanger();
		virtual ~SceneChanger();


		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;
	private:

	};
}

