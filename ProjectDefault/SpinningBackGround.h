#pragma once
#include "Object.h"

/// <summary>
/// 방적 작업 시작부터 끝날때까지 보여주는 배경 오브젝트
/// 레이어 최하단 설정 가장 아래에 위치함
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
	// 배경 size
	int m_ScreenSizeX;
	int m_ScreenSizeY;
};

