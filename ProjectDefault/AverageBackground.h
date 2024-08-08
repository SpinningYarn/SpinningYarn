#pragma once
#include "Object.h"
#include "Common.h"
/// <summary>
/// ���� �ý��� �⺻ ���ȭ��
/// 
/// </summary>
class AverageBackground : public Object
{
public:
	AverageBackground(const int& objectNum, std::string objectName);
	AverageBackground(int objectNum, std::string objectName, double posX, double posY);
	~AverageBackground();

	virtual void UpdateObject() override;	// ������Ʈ
	virtual void RenderObject() override;	// ����


private:
	int m_ScreenSizeX;
	int m_ScreenSizeY;
};

