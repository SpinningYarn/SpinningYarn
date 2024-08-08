#pragma once
#include <windows.h>

/// <summary>
/// DeltaTime 관련 클래스
/// </summary>
class TimerManager
{
public:
	// TimerManger 싱글톤화
	static TimerManager& GetInstance();
private:
	TimerManager();
	~TimerManager();
private:
	/// 기본 공식 주석
	// 초당 프레임 수(FPS) = (1 / Delta Time)
	// 프레임당 시간(Delta Time) = (1 / FPS)

	/// LARGE_INTEGER : 8 Byte로 구성된 __int64 형, ll(long long)
	LARGE_INTEGER m_llCurCount;		// 현재 performance counter 주파수의 포인터를 반환한다.
	LARGE_INTEGER m_llPrevCount;	// DeltaTime측정을 위해 이전 Count 값을 기록한다.
	LARGE_INTEGER m_llFrequency;	// CPU주파수에 따른 1초당 진행되는 틱수를 나타낸다. 변동이 없어서 한번만 읽어주면 된다.

	double m_dDeltaTime;	// 프레임 당(간) 걸린 시간 (d : double, DeltaTime)
	double m_FPS;			// ( 1 / m_dDeltaTime)
	double m_dAcc;			// 1초 체크를 위한 누적(accumulate) 시간

	UINT m_ICallCount;	// count 호출
	UINT m_iFPS;		// 이 클래스에서의 FPS 확인
public:
	void Initialize();
	void StartUpdate();
	void EndUpdate();
public:
	/// DeltaTime 반환
	double GetDeltaTime();
	float GetfDeltaTime();

	// 1초 프레임 반환
	double GetFPS();
};