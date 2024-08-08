#include "SpinningGuideLine.h"
#include "../D2DEngine/D2DEngine.h"
#include "MouseManager.h"
#include "SpinningWheel.h"

SpinningGuideLine::SpinningGuideLine(const int objectNum, std::string objectName)
	: Object(objectNum, objectName, 0, 0)
	, m_PosX(0), m_PosY(0)
{
	this->renderOrder = OBJECT_ORDER;
}

SpinningGuideLine::SpinningGuideLine(const int objectNum, const std::string& objectName, const double posX, const double posY)
	: Object(objectNum, objectName, posX, posY)
	, m_PosX((const float)posX), m_PosY((const float)posY)
{
	this->renderOrder = OBJECT_ORDER;
}

void SpinningGuideLine::UpdateObject()
{

}

void SpinningGuideLine::RenderObject()
{
	// 마우스 (좌)클릭이 유지되고 있는 상태면 돌리는 방향 가이드라인 표시
	if (MouseManager::GetInstance()->GetLeftButtonDownState() == true)
	{
		D2DEngine::GetInstance()->DrawSprite(eObjectDefine::SpinningGuideLine, m_PosX, m_PosY);
	}
}
