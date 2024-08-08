#pragma once
#include <windows.h>

/// <summary>
/// DeltaTime ���� Ŭ����
/// </summary>
class TimerManager
{
public:
	// TimerManger �̱���ȭ
	static TimerManager& GetInstance();
private:
	TimerManager();
	~TimerManager();
private:
	/// �⺻ ���� �ּ�
	// �ʴ� ������ ��(FPS) = (1 / Delta Time)
	// �����Ӵ� �ð�(Delta Time) = (1 / FPS)

	/// LARGE_INTEGER : 8 Byte�� ������ __int64 ��, ll(long long)
	LARGE_INTEGER m_llCurCount;		// ���� performance counter ���ļ��� �����͸� ��ȯ�Ѵ�.
	LARGE_INTEGER m_llPrevCount;	// DeltaTime������ ���� ���� Count ���� ����Ѵ�.
	LARGE_INTEGER m_llFrequency;	// CPU���ļ��� ���� 1�ʴ� ����Ǵ� ƽ���� ��Ÿ����. ������ ��� �ѹ��� �о��ָ� �ȴ�.

	double m_dDeltaTime;	// ������ ��(��) �ɸ� �ð� (d : double, DeltaTime)
	double m_FPS;			// ( 1 / m_dDeltaTime)
	double m_dAcc;			// 1�� üũ�� ���� ����(accumulate) �ð�

	UINT m_ICallCount;	// count ȣ��
	UINT m_iFPS;		// �� Ŭ���������� FPS Ȯ��
public:
	void Initialize();
	void StartUpdate();
	void EndUpdate();
public:
	/// DeltaTime ��ȯ
	double GetDeltaTime();
	float GetfDeltaTime();

	// 1�� ������ ��ȯ
	double GetFPS();
};