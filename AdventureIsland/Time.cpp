#include "Time.h"



namespace key_logic
{

	//����ƽ ������ �����ο��� �ʱ�ȭ�� �ʼ���.
	LARGE_INTEGER Time::mCpuFrequency = {};
	LARGE_INTEGER Time::mPrevFrequency = {};
	LARGE_INTEGER Time::mCurFrequency = {};
	float Time::mDeltaTime = 0.0f; 

	//�ʱ�ȭ
	void Time::Initialize()
	{
		//CPU ���� �������� �����´�.
		QueryPerformanceFrequency(&mCpuFrequency);

		//���α׷��� ���۵����� �������� �����´�.
		QueryPerformanceCounter(&mPrevFrequency);

	}

	void Time::Update()
	{
		QueryPerformanceCounter(&mCurFrequency);
		float differenceFrequency = static_cast<float>(mCurFrequency.QuadPart - mPrevFrequency.QuadPart);
		mDeltaTime = differenceFrequency / static_cast<float>(mCpuFrequency.QuadPart);
		mPrevFrequency.QuadPart = mCurFrequency.QuadPart;
	}

	
	bool Time::Render(HDC hdc)
	{
		
		static float timeCheck = 0.0f;
		
		timeCheck += mDeltaTime; //
		//1�ʸ��� fps ȭ�鿡 ������Ʈ ���ֱ�
		//1�� ���� ���
		//������ ����ɶ����� timeCheck ������ ��Ÿ Ÿ���� �����ָ�
		//timeCheck�� 1�� �� ������ 1�ʰ� �ȰͰ� ���� ������
		//if���� ������ timeCheck >= 1.0f�� �����Ѵ�.
		if (timeCheck >= 1.0f)
		{
			wchar_t szFloat[50] = {};
			float fps = 1.0f / mDeltaTime;
			
			//swprintf_s ����ϴ� ����?
			swprintf_s(szFloat, 50, L"fps : %f", fps);
			int strLen = wcsnlen_s(szFloat, 50);

			//�޾ƿ� hdc�� ȭ�鿡 �ؽ�Ʈ ���
			TextOut(hdc, 10, 10, szFloat, strLen);

			timeCheck = 0.0f;
			return true;
		}
		return false;

	}

}


