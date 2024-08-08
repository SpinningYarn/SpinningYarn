#pragma once
#include "Object.h"

class SpinningGaugeManager;
class StageManager;

/// <summary>
/// Spinning 게이지 진행 상황을 알려주는 Ball Object
/// Spinning 회전에 따라 이동하게 한다.
/// 
/// 2023.02.15 KIM
/// </summary>
class SpinningGaugBall : public Object
{
public:
	SpinningGaugBall(const int objectNum, std::string objectName);
	SpinningGaugBall(const int objectNum, const std::string& objectName, const double posX, const double posY);
	~SpinningGaugBall();

	virtual void UpdateObject() override;
	virtual void RenderObject() override;

private:
	SpinningGaugeManager* m_pSpinningGaugeManger;
	StageManager* m_pStageManager;

	// Gauge 볼 Object 좌표
	double m_PosX;
	double m_PosY;

	// Gauge Ball이 이동할때 판단할 변수
	bool m_CountOn;
	int m_MinusCount;
	double m_CountNum;

	// Guage Ball이 점점 증가하게끔 관리할 Time 변수
	float m_AccTime;
	int m_CurFrame;

	// Random 좌표에 Ball이 있을경우 처리할 Time 변수
	float m_AccTime2;
	int m_CurFrame2;

	// Random으로 나오는 지정 범위 좌표 변수
	double m_RandomPosX;

	// 투명도
	float m_AlphaValue;

	bool m_IsGameStart;
public:
	// 게임 종료시
	void EndGame();
	
	// GugeBar 랜덤 수치 받기
	void SetRandomGaugePos();
};

