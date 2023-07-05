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
		//�� �浹
		//�Ʒ� Ȥ�� ���� �Ʒ� Ȥ�� ���� �Ʒ��� ��
		if (mBallPos.y <= 0)
		{
			rand_num = rand() % 3 + 4; //4~6�� �ε���
		}

		//�� �浹
		//���� �Ʒ� Ȥ�� �� Ȥ�� ���� ���� ��
		else if (mBallPos.x >= 1500)
		{
			rand_num = rand() % 3 + 6; //6,7 Ȥ�� 1�� �ε���
			if (rand_num == 8)
				rand_num = 0;
		}

		//�Ʒ� �浹
		//�� Ȥ�� ���� �� Ȥ�� ���� ���� ��
		else if (mBallPos.y >= 780)
		{
			rand_num = rand() % 3; //0~2�� �ε��� 
		}

		//�� �浹
		//������ Ȥ�� �� Ȥ�� �����Ʒ��� ��
		else if (mBallPos.x <= 0)
		{
			rand_num = rand() % 3 + 2; //2~4�� �ε���
		}
	}
}
