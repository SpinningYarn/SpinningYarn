#pragma once
#include "Object.h"

class SpinningGaugeManager;
class StageManager;

/// <summary>
/// Spinning ������ ���� ��Ȳ�� �˷��ִ� Ball Object
/// Spinning ȸ���� ���� �̵��ϰ� �Ѵ�.
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

	// Gauge �� Object ��ǥ
	double m_PosX;
	double m_PosY;

	// Gauge Ball�� �̵��Ҷ� �Ǵ��� ����
	bool m_CountOn;
	int m_MinusCount;
	double m_CountNum;

	// Guage Ball�� ���� �����ϰԲ� ������ Time ����
	float m_AccTime;
	int m_CurFrame;

	// Random ��ǥ�� Ball�� ������� ó���� Time ����
	float m_AccTime2;
	int m_CurFrame2;

	// Random���� ������ ���� ���� ��ǥ ����
	double m_RandomPosX;

	// ����
	float m_AlphaValue;

	bool m_IsGameStart;
public:
	// ���� �����
	void EndGame();
	
	// GugeBar ���� ��ġ �ޱ�
	void SetRandomGaugePos();
};

