#pragma once
#include "Object.h"

class StageManager;

/// <summary>
/// ���� �۾� ���ۺ��� ���������� �����ִ� �޸��� (��溸�� ���̾� ����)
/// 
/// 2022.02.20
/// </summary>
class SpinningOrderMemo : public Object
{
public:
	SpinningOrderMemo(const int objectNum, std::string objectName);
	SpinningOrderMemo(const int objectNum, const std::string& objectName, const double posX, const double posY);
	~SpinningOrderMemo();

	virtual void UpdateObject() override;
	virtual void RenderObject() override;

private:
	StageManager* m_pStageManager;

	float m_PosX;
	float m_PosY;
};

