#include "TimerManager.h"

TimerManager& TimerManager::GetInstance()
{
	static TimerManager timerMgr;
	return timerMgr;
}

TimerManager::TimerManager()
	: m_llCurCount()
	, m_llPrevCount()
	, m_llFrequency()
	, m_dDeltaTime(0)
	, m_FPS(0)
	, m_dAcc(0)
	, m_ICallCount(0)
	, m_iFPS(0)
{

}

TimerManager::~TimerManager()
{

}

void TimerManager::Initialize()
{
	// 초당 카운트 횟수 (10,000,000), 타이머의 주파수를 반환한다.
	QueryPerformanceFrequency(&m_llFrequency);
}

void TimerManager::EndUpdate()
{
	// 현재 카운트 값 현재 count에 받아온다.
	QueryPerformanceCounter(&m_llCurCount);

	// DeltaTime 값을 구한다. (1프레임 당 걸리는 시간)
	m_dDeltaTime = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart)
		/ (double)(m_llFrequency.QuadPart); // QuadPart에 실제 longlong값이 들어있다.

	// PrevCount를 최신 값으로 갱신
	m_llPrevCount = m_llCurCount;

	++m_ICallCount;

	// deltaTime을 누적시키면, 현재까지 흐른 총 흐른 시간이 된다.
	m_dAcc += m_dDeltaTime;
	m_FPS = m_dAcc;

	if (m_dAcc >= 1)
	{
		// 초당 프레임 횟수 갱신
		m_iFPS = m_ICallCount;

		// 값들 0으로 다시 초기화
		m_dAcc = 0;
		m_ICallCount = 0;
	}
	// m_FPS = 1 / m_DT;
}

void TimerManager::StartUpdate()
{
	// 현재 카운트 값 검색, CPU의 틱을 받아온다.
	QueryPerformanceCounter(&m_llPrevCount);
}

// 프레임 당 걸린 시간 return (double형)
double TimerManager::GetDeltaTime()
{
	return m_dDeltaTime;
}

// float형 변환 후 리턴
float TimerManager::GetfDeltaTime()
{
	return (float)m_dDeltaTime;
}

double TimerManager::GetFPS()
{
	return m_FPS;
}
