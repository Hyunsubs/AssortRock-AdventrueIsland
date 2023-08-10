#pragma once
#include "yhGameObject.h"

namespace yh
{
	class Grass : public GameObject
	{
	public:
		Grass();
		virtual ~Grass() override;


		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other) override;
		virtual void OnCollisionStay(class Collider* other) override;
		virtual void OnCollisionExit(class Collider* other) override;

	private:
		std::wstring name;
		std::wstring path;

		class Transform* tr;
		class Texture* image;
		class Collider* col;
		class SpriteRenderer* sr;

	};
}


