#pragma once
#include "Object.h"

/// <summary>
/// 
/// 직조 시스템 진입때부터 끝날때까지 유지될 배경화면 오브젝트
/// 레이어를 최하단으로 설정하여 항상 가장 아래에 위치함
/// 
/// 2022.02.09 YJH
/// </summary>

class KnttingBackGround : public Object
{
public:
	KnttingBackGround(const int objectNum, std::string objectName);
	KnttingBackGround(const int objectNum, const std::string& objectName, const double posX, const double posY);
	~KnttingBackGround();

	virtual void UpdateObject() override;		// 객체에서 업데이트 하는 것을 오버라이딩
	virtual void RenderObject() override;		// 객체에서 그리는 것을 오버라이딩	

private:
	int m_ScreenSizeX;
	int m_ScreenSizeY;
};

