#pragma once


namespace yh::math
{
	struct Vector2
	{
		static Vector2 Zero;
		static Vector2 One;
		static Vector2 Right;
		static Vector2 Up;

		float x;
		float y;

		Vector2():
			x(0.0f),
			y(0.0f)
		{

		}

		Vector2(float _x, float _y) :
			x(_x),
			y(_y)
		{

		}

	};



}