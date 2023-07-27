#pragma once
#include "yhComponent.h"


namespace yh
{
	using namespace math;
	class Rigidbody : public Component
	{
	public:
		Rigidbody();
		~Rigidbody();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		void AddForce(Vector2 force) { mForce += force; }
		void SetMass(float mass) { mMass = mass; }
		void SetGround(bool ground) { mbGround = ground; }
		Vector2 GetVelocity() { return mVelocity; }
		void SetVelocity(Vector2 velocity) { mVelocity = velocity; }

	private:
		float mMass;

		float mFriction;
		float mStaticFriction;
		float mKineticFriction;
		float mCoefficientFriction;

		Vector2 mForce;
		Vector2 mAcceleration;
		Vector2 mVelocity;
		Vector2 mGravity;
		Vector2 mLimitedVelocity;

		bool mbGround;
	};
}


