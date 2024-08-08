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
	// �ʴ� ī��Ʈ Ƚ�� (10,000,000), Ÿ�̸��� ���ļ��� ��ȯ�Ѵ�.
	QueryPerformanceFrequency(&m_llFrequency);
}

void TimerManager::EndUpdate()
{
	// ���� ī��Ʈ �� ���� count�� �޾ƿ´�.
	QueryPerformanceCounter(&m_llCurCount);

	// DeltaTime ���� ���Ѵ�. (1������ �� �ɸ��� �ð�)
	m_dDeltaTime = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart)
		/ (double)(m_llFrequency.QuadPart); // QuadPart�� ���� longlong���� ����ִ�.

	// PrevCount�� �ֽ� ������ ����
	m_llPrevCount = m_llCurCount;

	++m_ICallCount;

	// deltaTime�� ������Ű��, ������� �帥 �� �帥 �ð��� �ȴ�.
	m_dAcc += m_dDeltaTime;
	m_FPS = m_dAcc;

	if (m_dAcc >= 1)
	{
		// �ʴ� ������ Ƚ�� ����
		m_iFPS = m_ICallCount;

		// ���� 0���� �ٽ� �ʱ�ȭ
		m_dAcc = 0;
		m_ICallCount = 0;
	}
	// m_FPS = 1 / m_DT;
}

void TimerManager::StartUpdate()
{
	// ���� ī��Ʈ �� �˻�, CPU�� ƽ�� �޾ƿ´�.
	QueryPerformanceCounter(&m_llPrevCount);
}

// ������ �� �ɸ� �ð� return (double��)
double TimerManager::GetDeltaTime()
{
	return m_dDeltaTime;
}

// float�� ��ȯ �� ����
float TimerManager::GetfDeltaTime()
{
	return (float)m_dDeltaTime;
}

double TimerManager::GetFPS()
{
	return m_FPS;
}
