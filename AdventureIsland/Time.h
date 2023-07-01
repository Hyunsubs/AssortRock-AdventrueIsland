#pragma once
#include "CommonInclude.h"

//union �ڷ���
//���Ͽ��� �ȿ� ������ �ڷ���� �޸𸮸� ���� �����ϰ� ������ش�.




//delta time�̶�
//��Ÿ�� ���� ���̸� ���Ѵ�
//��Ÿ Ÿ�� ����� �ɸ� �ð��� �����Ͽ� ������ ���� Ƚ���� �����Ҽ� �ִ� ����̴�.

//CPU�� ��Ȯ�� �ð��� ����� ������
//CPU ������ ������ Ȱ���Ͽ� ������ �ð��� ���� �� �ִ�.



//CPU�� ���� �������� ���ϴ� �Լ�
//QueryPerformanceFrequency() ���ڷ� �ּҸ� �޾ƿ�


//���α׷��� ���۵����� �������� �������� �Լ�
//QueryPerformanceCounter()
namespace key_logic
{
	class Time
	{
	public:
		static void Initialize();
		static void Update();
		static void Render(HDC hdc);

		__forceinline static float DelataTime() { return mDeltaTime; }

	
		//LARGE_INTERGER�� 16����Ʈ ¥�� �����͸� ����ü�� �����Ѱ��̴�.4
		//Low Part High Part�� �������� �ְ�
		//�ѹ��� �ҷ��ö� QuadPart�� �ҷ��´�.

		//static casting
		//static_cast<�ڷ���>
		//c++ ��Ÿ�� ����ȯ ���� �� �����ϴ�.


		//��Ÿ Ÿ�� ���ϱ� ���� 
		//���� �������� ���� ���� ���̸� CPU ���� �������� ������.
		//

	private:
		static LARGE_INTEGER mCpuFrequency; 
		static LARGE_INTEGER mPrevFrequency;
		static LARGE_INTEGER mCurFrequency;

		static float mDeltaTime;
	};
}


