#pragma once
#include "Object.h"

/// <summary>
/// 물레 방향 가이드 라인
/// 마우스 클릭이 유지되고 있는 상태면 가이드 라인 화살표가 나온다.
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
	// Object 좌표
	float m_PosX;
	float m_PosY;
};

