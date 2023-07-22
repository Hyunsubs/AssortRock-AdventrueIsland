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

		Vector2 operator+(const Vector2 other)
		{
			Vector2 temp;
			temp.x = this->x + other.x;
			temp.y = this->y + other.y;
			return temp;
		}

		Vector2 operator-(const Vector2 other)
		{
			Vector2 temp;
			temp.x = this->x - other.x;
			temp.y = this->y - other.y;
			return temp;
		}

		Vector2 operator/(const float value)
		{
			Vector2 temp;
			temp.x = this->x / value;
			temp.y = this->y / value;
			return temp;
		}

		Vector2 operator*(const Vector2 other)
		{
			Vector2 temp;
			temp.x = this->x * other.x;
			temp.y = this->y * other.y;
			return temp;
		}

		Vector2 operator+=(const float value)
		{
			Vector2 temp;
			temp.x = this->x += value;
			temp.y = this->y += value;
			return temp;
		}

		Vector2 operator+=(const Vector2 other)
		{
			//위에 만든 + 오퍼레이터 활용
			Vector2 temp;
			temp = temp + other;
			return temp;
		}

	};



}