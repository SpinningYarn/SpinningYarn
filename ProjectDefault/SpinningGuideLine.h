#pragma once
#include "Object.h"

/// <summary>
/// ���� ���� ���̵� ����
/// ���콺 Ŭ���� �����ǰ� �ִ� ���¸� ���̵� ���� ȭ��ǥ�� ���´�.
/// 
/// 2023.02.14
/// </summary>
class SpinningGuideLine : public Object
{
public:
	SpinningGuideLine(const int objectNum, std::string objectName);
	SpinningGuideLine(const int objectNum, const std::string& objectName, const double posX, const double posY);

	virtual void UpdateObject() override;
	virtual void RenderObject() override;

private:
	// Object ��ǥ
	float m_PosX;
	float m_PosY;
};

