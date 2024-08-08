#pragma once
#include "Object.h"

/// <summary>
/// 
/// 뜨개질 바늘
/// 고양이가 방해를 하면
/// 움직일 예정
/// 
/// 2022.02.16 YJH
/// </summary>

class Needle : public Object
{
public:
	Needle(const int objectNum, std::string objectName);
	Needle(const int objectNum, const std::string& objectName, const double posX, const double posY);
	~Needle();

	virtual void UpdateObject() override;
	virtual void RenderObject() override;

	void MoveNeedleX(double MoveSize);			// SIZE만큼 움직임
	void MoveNeedleY(double MoveSize);			// SIZE만큼 움직임
	double GetNeedleX();
	void SetOriginX();


private:
	double m_NeedleX;
	double m_NeedleY;
};

