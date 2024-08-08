#pragma once
#include "Object.h"

/// <summary>
/// ���� �۾� ���ۺ��� ���������� �����ִ� ��� ������Ʈ
/// ���̾� ���ϴ� ���� ���� �Ʒ��� ��ġ��
/// 
/// 2022.02.09 KDW
/// </summary>
class SpinningBackGround : public Object
{
public:
	SpinningBackGround(const int objectNum, std::string objectName);
	SpinningBackGround(const int objectNum, const std::string& objectName, const double posX, const double posY);
	~SpinningBackGround();

	virtual void UpdateObject() override;
	virtual void RenderObject() override;

private:
	// ��� size
	int m_ScreenSizeX;
	int m_ScreenSizeY;
};

