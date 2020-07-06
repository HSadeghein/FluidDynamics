#pragma once


//*****************************
//Windows Only
//*****************************
#define WIN32_LEAN_AND_MEAN      // Exclude rarely-used stuff from Windows headers

#include <windows.h>

namespace FluidEngine
{

	class GameTimer
	{
	public:
		GameTimer();

		//in seconds
		float TotalTime() const;
		float DeltaTime() const;

		void Reset();
		void Start();
		void Stop();
		void Tick();

	private:
		double m_SecondsPerCount;
		double m_DeltaTime;


		//Microsoft visual C++ based
		//Counted as clocks
		__int64 m_BaseTime;
		__int64 m_PausedTime;
		__int64 m_StopTime;
		__int64 m_PrevTime;
		__int64 m_CurrTime;

		bool m_Stopped = false;
	};
}
