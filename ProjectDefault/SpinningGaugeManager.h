#pragma once

/// <summary>
/// Spinning Gauge에 대한 상태, 값들을 관리하는 곳
/// 
/// 2023.02.15 KIM
/// </summary>
class SpinningGaugeManager
{
public:
	static SpinningGaugeManager* GetInstance();

private:
	static SpinningGaugeManager* m_pInstance;

private:
	SpinningGaugeManager();
	~SpinningGaugeManager();

private:
	// Gauge Bar Stat
	const int m_MaxGaugeBar = 1200;		// Gauge Bar 최대 수치
	const int m_Preheat = 180;			// 예열 수치 (1 ~ 30%)
	const int m_Overload = 541;			// 과부하 수치 (91 ~ 100%)
	const int m_Percent10Gauge = 60;	// 10% 당 거리
	int m_GaugeBarCount;				// Gauge Bar 카운트

	// Gauge Bar Pos
	int m_GauageBarPosX;
	int m_GauageBarPosY;

public:
	// Gauge Ball Pos
	int m_GauageBallPosX;
	int m_GauageBallPosY;

private:
	// Gauge count
	int m_GauageNumCount;

	// 지정 게이지
	float m_RandomGauge;			// 랜덤 값 지정
	int m_RandomGaugeTimeCount;		// 랜덤 범위에 1초간 카운트할 변수
	float m_AlphaValue;				// 랜덤 범위 Render 투명도 값
	bool m_IsRandomCount;			// 랜덤 범위 카운트 판단

	// 애니메이션 판단
	bool m_FailAnimation;
	bool m_SucessAnimation;
	bool m_BallAnimation;

public:
	/// 세팅
	void SetGauageBarPos(int posX, int posY);	// Gauage Bar 좌표 세팅
	void SetGauageBallPos(int posX, int posY);	// Gauage Ball 좌표 세팅
	void SetRandomPos();		// 랜덤 좌표 세팅 (예열수치와 과열수치 사이 - 120)
	void SetFailAnimation(bool state);		// 실패 Object 애니메이션 세팅
	void SetSucessAnimation(bool state);		// 성공 Object 애니메이션 세팅
	void SetBallAnimation(bool state);		// Ball Object 애니메이션 세팅

	/// 기능들
	void CountIncrease(int num);	// Gauge를 움직이게 판단할 카운트 값 증가
	void RandomPosCounting();		// 랜덤좌표에 있을경우 1초에 1증가
	void RandomPosCountInit();		// 랜덤 카운팅 초기화
	void RandomIsCountChage(bool isRandom);		// 랜덤 카운트 상태 변환
	void RandomGaugeAlphaValue(float value);	// 랜덤 범위 Render 투명도 변환
	
	/// 반환
	int GetGauageCount();		// 몇번 카운트했는지
	int GetMaxGaugeBar();		// Gauge 최대 크기
	int GetPreheatSize();		// 예열 size
	int GetOverloadSize();		// 과열 size
	int GetPercent10Gauge();	// 10% 수치
	float GetRandomGaugePosX();	// 랜덤 좌표 반환
	int GetRandomTimeCount();	// 랜덤 타임 카운트 반환
	bool GetRandomIsCount();	// 랜덤 카운트 상태 반환
	float GetRandomGaugeAlphaValue();	// 랜덤 범위 Render 투명도 반환
	bool IsFailAnimation();			// 실패 Object 애니메이션
	bool IsSucessAnimation();			// 성공 Object 애니메이션
	bool IsBallAnimation();		// Ball Object 애니메이션
private:
};

