#pragma once
#include "yhGameObject.h"




namespace yh
{
	using namespace math;
	class Camera
	{
	public:
		static void Initialize();
		static void Update();

		static Vector2 CalculatePosition(Vector2 pos) { return pos - mDistance; }
		static Vector2 CalculateUIPosition(Vector2 pos) { return pos + mDistance; }
		static void SetTarget(GameObject* target) { mTarget = target; }
		static bool Is_Following() 
		{
			if (mTarget == nullptr) 
				return false;
			else 
				return true;
		}
		static void ResetCamera();
		static void SetLookPosition(Vector2 input) { mLookPosition = input; }



	private:
		static Vector2 mResolution;
		static Vector2 mLookPosition;
		static Vector2 mDistance;
		static GameObject* mTarget;

	};
}


