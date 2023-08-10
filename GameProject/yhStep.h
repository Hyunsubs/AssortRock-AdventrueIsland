#pragma once
#include "yhGameObject.h"

namespace yh
{
	class Step : public GameObject
	{
	public:
		Step();
		virtual ~Step() override;


		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

		void SetColSize(Vector2 input);

	private:
		class Transform* tr;
		class Collider* col;
	};
}