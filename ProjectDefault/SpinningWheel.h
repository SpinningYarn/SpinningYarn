#pragma once
#include "Object.h"

class MouseManager;
class Matrix2;
class StageManager;

/// <summary>
/// ���� Object ��������� ���̴� �κ�
/// ���콺�� ���� ������ ���� object�� �ִϸ��̼����� ȸ����Ű�� ���
/// 
/// 2023.02.09 kimdowoo
/// </summary>
class SpinningWheel : public Object
{
public:
	SpinningWheel(const int objectNum, std::string objectName);
	SpinningWheel(const int objectNum, const std::string& objectName, const double posX, const double posY);
	~SpinningWheel();

	virtual void UpdateObject() override;		// ��ü���� ������Ʈ
	virtual void RenderObject() override;		// ��ü���� �׸���

	double GetRotateScale();
	void SetRotateScale(double scale);

private:
	MouseManager* m_pMouseManager;
	StageManager* m_pStageManager;

	// Object ��ǥ
	float m_PosX;
	float m_PosY;

	double m_rotateScale;		//ȸ����

public:
	bool GetMoveState();
};

