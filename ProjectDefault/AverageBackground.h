#pragma once
#include "Object.h"
#include "Common.h"
/// <summary>
/// 방직 시스템 기본 배경화면
/// 
/// </summary>
class AverageBackground : public Object
{
public:
	AverageBackground(const int& objectNum, std::string objectName);
	AverageBackground(int objectNum, std::string objectName, double posX, double posY);
	~AverageBackground();

	virtual void UpdateObject() override;	// 업데이트
	virtual void RenderObject() override;	// 렌더


private:
	int m_ScreenSizeX;
	int m_ScreenSizeY;
};

