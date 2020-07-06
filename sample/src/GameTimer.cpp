#include "GameTimer.h"
#include <profileapi.h>
namespace FluidEngine
{
	GameTimer::GameTimer() : m_SecondsPerCount(0), m_DeltaTime(-1.0), m_BaseTime(0), m_StopTime(0),
		m_PausedTime(0), m_PrevTime(0), m_CurrTime(0), m_Stopped(false)
	{
		__int64 countsPerSecond;
		QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSecond);
		m_SecondsPerCount = 1.0 / (double)countsPerSecond;

	}
	void GameTimer::Tick()
	{
		if (m_Stopped)
		{
			m_DeltaTime = 0;
			return;
		}

		__int64 currTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
		m_CurrTime = currTime;

		m_DeltaTime = (m_CurrTime - m_PrevTime) * m_SecondsPerCount;

		m_PrevTime = m_CurrTime;

		if (m_DeltaTime < 0)
		{
			m_DeltaTime = 0;
		}
	}


	float GameTimer::DeltaTime() const
	{
		return (float)m_DeltaTime;
	}

	void GameTimer::Reset()
	{
		__int64 currTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

		m_BaseTime = currTime;
		m_PrevTime = currTime;
		m_StopTime = 0;
		m_Stopped = false;
	}

	void GameTimer::Stop()
	{
		if (!m_Stopped)
		{
			__int64 currTime;
			QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

			m_StopTime = currTime;
			m_Stopped = true;
		}
	}

	void GameTimer::Start()
	{
		__int64 startTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&startTime);

		if (m_Stopped)
		{
			m_PausedTime += (startTime - m_StopTime);

			m_PrevTime = startTime;

			m_StopTime = 0;
			m_Stopped = false;

		}
	}

	float GameTimer::TotalTime() const
	{
		if (m_Stopped)
		{
			return (float)(((m_StopTime - m_PausedTime) - m_BaseTime) * m_SecondsPerCount);
		}
		else
		{
			return (float)(((m_CurrTime - m_PausedTime) - m_BaseTime) * m_SecondsPerCount);
		}

	}

}