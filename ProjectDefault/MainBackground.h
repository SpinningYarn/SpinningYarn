#pragma once
#include "Object.h"
/// <summary>
/// 방직 시스템 기본 배경화면
/// 
/// </summary>
class MainBackground : public Object
{
public:
	MainBackground(const int& objectNum, std::string objectName);
	MainBackground(int objectNum, std::string objectName, double posX, double posY);
	~MainBackground();

	virtual void UpdateObject() override;	// 업데이트
	virtual void RenderObject() override;	// 렌더

private:
	int m_ScreenSizeX;
	int m_ScreenSizeY;

	float m_exitButtonSrcX;
	float m_exitButtonSrcY;
	float m_exitButtonDstX;
	float m_exitButtonDstY;
};
