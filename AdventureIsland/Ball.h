#pragma once
#include "CommonInclude.h"
#include "math_thing.h"
#include "Time.h"
using namespace key_logic;

class Ball
{
public:

	math::Vector2 GetCoor();
	void Move(HDC hdc,int direction);
	void is_Wall();

	int rand_num = rand() % 8;

	Ball():
		mBallPos(800.0f,450.0f)
	{

	}
	

private:
	math::Vector2 mDirections[8] =
	{
		math::Vector2(-1.0f,-1.0f), //좌측위
		math::Vector2(0.0f,-1.0f), //위
		math::Vector2(1.0f, -1.0f), //우측위
		math::Vector2(1.0f, 0.0f), //우
		math::Vector2(1.0f, 1.0f), //우측아래
		math::Vector2(0.0f, 1.0f), //아래
		math::Vector2(-1.0f, 1.0f), //좌측 아래
		math::Vector2(-1.0f, 0.0f) //좌
		
	};

	math::Vector2 mBallPos;
};

