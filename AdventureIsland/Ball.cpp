#include "Ball.h"


math::Vector2 Ball::GetCoor()
{
	return mBallPos;
}

void Ball::Move(HDC hdc,int direction)
{
	
	math::Vector2 cur_direction = mDirections[direction];
	mBallPos.x += cur_direction.x * Time::DelataTime() * 100;
	mBallPos.y += cur_direction.y * Time::DelataTime() * 100;

	Ellipse(hdc, mBallPos.x, mBallPos.y, 100 + mBallPos.x, 100 + mBallPos.y);
}

void Ball::is_Wall()
{
	if (mBallPos.x <= 0 || mBallPos.x >= 1500 || mBallPos.y <= 0 || mBallPos.y >= 750)
	{
		rand_num = rand() % 8;
	}
}
