#include "jhTime.h"

namespace jh
{
	LARGE_INTEGER Time::mCPUFrequency;
	float Time::mDeltaTime = 0.0f;
	HWND Time::mHwnd;

	float Time::mScale = 1.0f;
	double Time::mdSecondPerCount{ 0.0 };
	long long Time::mllBaseTime{ 0 };
	long long Time::mllPausedTime{ 0 };
	long long Time::mllStopTime{ 0 };
	long long Time::mllPrevTime{ 0 };
	long long Time::mllCurrTime{ 0 };
	bool Time::mbIsStoped = false;

	void Time::Initialize()
	{
		// �ý����� ���� ī���ʹ� ���ļ� ���·� ���� ��ȯ�Ѵ�. ������ �츮���� �ʿ��� ���� �ð�!
		// ����, ���ļ�(Hz)���¸� ���ؿͼ� ������ 1 Cycle �� ��� �ð��� ���صд�.
		// �� ���� ������ �ʴ� ������ ������ ���ؿ� ���ļ��� �� ���� ���ϸ�, ���ϴ� �ð�(��)�� ���� �� �ְ� ��.

		QueryPerformanceFrequency(&mCPUFrequency);			// CPU �ʴ� �ݺ� �Ǵ� �������� ������ �Լ� ó���� 0��.


		//QueryPerformanceCounter(&mPrevFrequency);			// ���α׷� ���� ���� ���� CPU�� Ŭ���� 

		// ADD PART
		mdSecondPerCount = 1.0 / static_cast<double>(mCPUFrequency.QuadPart);


		// ADD PART END

		mHwnd = D3DApp::GetInstance().GetHwnd();
		StartTimeCounting();

	}

	void Time::Update()
	{
		//QueryPerformanceCounter(&mCurFrequency);
		//float differntFrequency
		//	= static_cast<float>(mCurFrequency.QuadPart - mPrevFrequency.QuadPart);
		//mDeltaTime = differntFrequency / mCPUFrequency.QuadPart;
		//mPrevFrequency.QuadPart = mCurFrequency.QuadPart;	// ����

		// ADD PART
		if (mbIsStoped)
		{
			mDeltaTime = 0.0f;
			return;
		}

		long long currTime;
		QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currTime));

		mllCurrTime = currTime;
		mDeltaTime = static_cast<float>((mllCurrTime - mllPrevTime) * mdSecondPerCount);
		mllPrevTime = mllCurrTime;
		if (mDeltaTime < 0.0f)
		{
			mDeltaTime = 0.0f;
		}
	}

	void Time::Render(HDC hdc)
	{
		static int frameCnt = 0;
		static float timeElapsed = 0.0f;

		++frameCnt;

		// 1�� ������ ��� ������ ���� ����Ѵ�.

		if ((TotalTime() - timeElapsed) >= 1.0f)
		{
			wchar_t buffer[128] = {};
			float fps = (float)frameCnt;
			float mspf = 1000.0f / fps;

			swprintf_s(buffer, 128, L"FramePerSecond : %.3f, FrameTime : %.3f", fps, mspf);
			//size_t strLen = static_cast<size_t>(wcsnlen_s(buffer, 128));

			SetWindowText(mHwnd, buffer);

			// ���� ����� ���� �ʱ�ȭ �Ѵ�.
			frameCnt = 0;
			timeElapsed += 1.0f;
		}
	}

	void Time::StartTimeCounting()
	{
		long long currTime;
		QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currTime));

		mllBaseTime = currTime;
		mllPrevTime = currTime;
		mllStopTime = 0;
		mllPausedTime = 0;
		mbIsStoped = false;
	}

	void Time::Reset()
	{
		long long currTime;
		QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currTime));
		mllBaseTime = 0;
		mllPrevTime = currTime;
		mllStopTime = 0;
		mllPausedTime = 0;
		mbIsStoped = false;
	}

	void Time::Stop()
	{
		if (!mbIsStoped)
		{
			long long currTime;
			QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currTime));

			mllStopTime = currTime;
			mbIsStoped = true;
		}
	}

	void Time::Resume()
	{
		long long startTime;
		QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&startTime));

		if (mbIsStoped)
		{
			mllPausedTime += (startTime - mllStopTime);

			mllPrevTime = startTime;
			mllStopTime = 0;
			mbIsStoped = false;
		}

	}

	float Time::TotalTime()
	{
		if (mbIsStoped)
		{
			return static_cast<float>(((mllStopTime - mllPausedTime) - mllBaseTime) * mdSecondPerCount);
		}
		else
		{
			return static_cast<float>(((mllCurrTime - mllPausedTime) - mllBaseTime) * mdSecondPerCount);
		}
	}

	void Time::SetScale(float scale)
	{
		mScale = scale;
	}

}