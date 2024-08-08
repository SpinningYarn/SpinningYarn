#pragma once
#include "Object.h"
/// <summary>
/// ���� �ý��� �⺻ ���ȭ��
/// 
/// </summary>
class MainBackground : public Object
{
public:
	MainBackground(const int& objectNum, std::string objectName);
	MainBackground(int objectNum, std::string objectName, double posX, double posY);
	~MainBackground();

	virtual void UpdateObject() override;	// ������Ʈ
	virtual void RenderObject() override;	// ����

private:
	int m_ScreenSizeX;
	int m_ScreenSizeY;

	float m_exitButtonSrcX;
	float m_exitButtonSrcY;
	float m_exitButtonDstX;
	float m_exitButtonDstY;
};
