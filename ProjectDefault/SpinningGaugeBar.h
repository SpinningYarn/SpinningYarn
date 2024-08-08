#pragma once
#include "Object.h"

class SpinningGaugeManager;

/// <summary>
/// ���� ȸ�� �� �۵��ϴ� ������Bar
/// ���� ���� ���θ� �Ǵ��ϱ� ���� �������̴�.
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

	// Gauge Bar Object ��ǥ
	float m_PosX;
	float m_PosY;

	// Gauge ���� ���� �Ǵ�
	bool m_IsRandomX;

	// Gauge ���� ���� Render ����
	float m_AlphaValue;
};

