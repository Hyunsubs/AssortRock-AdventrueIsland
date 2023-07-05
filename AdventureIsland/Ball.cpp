#include "Ball.h"


math::Vector2 Ball::GetCoor()
{
	return mBallPos;
}

void Ball::Move(HDC hdc,int direction)
{
	
	math::Vector2 cur_direction = mDirections[direction];
	mBallPos.x += cur_direction.x * Time::DelataTime() * 300.0f;
	mBallPos.y += cur_direction.y * Time::DelataTime() * 300.0f;

	Ellipse(hdc, mBallPos.x, mBallPos.y, 100 + mBallPos.x, 100 + mBallPos.y);
}

void Ball::is_Wall()
{
	if (mBallPos.x <= 0 || mBallPos.x >= 1500 || mBallPos.y <= 0 || mBallPos.y >= 780)
	{
		//위 충돌
		//아래 혹은 좌측 아래 혹은 우측 아래로 감
		if (mBallPos.y <= 0)
		{
			rand_num = rand() % 3 + 4; //4~6번 인덱스
		}

		//우 충돌
		//좌측 아래 혹은 좌 혹은 좌측 위로 감
		else if (mBallPos.x >= 1500)
		{
			rand_num = rand() % 3 + 6; //6,7 혹은 1번 인덱스
			if (rand_num == 8)
				rand_num = 0;
		}

		//아래 충돌
		//위 혹은 우측 위 혹은 좌측 위로 감
		else if (mBallPos.y >= 780)
		{
			rand_num = rand() % 3; //0~2번 인덱스 
		}

		//좌 충돌
		//우측위 혹은 우 혹은 우측아래로 감
		else if (mBallPos.x <= 0)
		{
			rand_num = rand() % 3 + 2; //2~4번 인덱스
		}
	}
}
