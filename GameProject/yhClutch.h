#pragma once
#include "yhGameObject.h"

#define FLYING_TIME 0.2f


namespace yh
{
	enum class MainClutchState
	{
		Pause,
		Move,
		MoveBack
	};


	class Clutch : public GameObject
	{
	public:
		Clutch();
		virtual ~Clutch();


		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		void Pause();
		void Move();
		void MoveBack();

		void SetDirection(Directions direct) { direction = direct; }
		void SetClutchState(MainClutchState input) { state = input; }

		MainClutchState GetClutchState() { return state; }

	private:
		MainClutchState state;
		Directions direction;
		float execute_time;

		std::vector<class ClutchParts*> clutches;
		class Transform* tr;
	};
}


