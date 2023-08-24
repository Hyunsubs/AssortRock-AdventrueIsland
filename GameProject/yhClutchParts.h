#pragma once
#include "yhGameObject.h"

#define FLYING_TIME 1.0f


namespace yh
{
	enum class ClutchTypes
	{
		Start,
		Middle,
		End
	};


	class ClutchParts : public GameObject
	{
	public:
		ClutchParts();
		virtual ~ClutchParts();


		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		void SetDirection(Directions direct) { direction = direct; }
		void SetTypes(ClutchTypes input) { type = input; }

		void SetActivated(bool input) { is_activated = input; }

		ClutchTypes GetClutchType() { return type; }
	private:
		Directions direction;
		ClutchTypes type;


		class Transform* tr;
		class Texture* image;
		class SpriteRenderer* sr;
		class Collider* col;

		bool is_captured;
		bool is_activated;
	};
}


