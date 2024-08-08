#pragma once
#include "Object.h"

class SpinningGaugeManager;

/// <summary>
/// 물레 회전 시 작동하는 게이지Bar
/// 방적 성공 여부를 판단하기 위한 게이지이다.
/// 
/// 2023.02.15 KDW
/// </summary>
class SpinningGaugeBar : public Object
{
public:
	SpinningGaugeBar(const int objectNum, std::string objectName);
	SpinningGaugeBar(const int objectNum, const std::string& objectName, const double posX, const double posY);
	~SpinningGaugeBar();

	virtual void UpdateObject() override;
	virtual void RenderObject() override;

private:
	SpinningGaugeManager* m_pSpinningGaugeManager;

	// Gauge Bar Object 좌표
	float m_PosX;
	float m_PosY;

	// Gauge 랜덤 범위 판단
	bool m_IsRandomX;

	// Gauge 랜덤 범위 Render 투명도
	float m_AlphaValue;
};

