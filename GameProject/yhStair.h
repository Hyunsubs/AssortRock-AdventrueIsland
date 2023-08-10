#pragma once
#include "yhGameObject.h"
//�ö󰥶� -110 �������� +110


namespace yh
{
	class Stair : public GameObject
	{
	public:
		Stair();
		virtual ~Stair() override;


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




