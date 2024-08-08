#pragma once
#include "Object.h"

class MouseManager;
class Matrix2;
class StageManager;

/// <summary>
/// 물레 Object 명시적으로 보이는 부분
/// 마우스로 원을 돌리면 물레 object를 애니메이션으로 회전시키는 담당
/// 
/// 2023.02.09 kimdowoo
/// </summary>
class SpinningWheel : public Object
{
public:
	SpinningWheel(const int objectNum, std::string objectName);
	SpinningWheel(const int objectNum, const std::string& objectName, const double posX, const double posY);
	~SpinningWheel();

	virtual void UpdateObject() override;		// 객체에서 업데이트
	virtual void RenderObject() override;		// 객체에서 그리기

	double GetRotateScale();
	void SetRotateScale(double scale);

private:
	MouseManager* m_pMouseManager;
	StageManager* m_pStageManager;

	// Object 좌표
	float m_PosX;
	float m_PosY;

	double m_rotateScale;		//회전값

public:
	bool GetMoveState();
};

