#include "SpinningWheel.h"
#include "../D2DEngine/D2DEngine.h"
#include "MouseManager.h"
#include "Matrix2.h"
#include "TimerManager.h"
#include "StageManager.h"

#include <algorithm>
#include <cmath>

SpinningWheel::SpinningWheel(const int objectNum, std::string objectName)
	: Object(objectNum, objectName)
	, m_PosX(0)
	, m_PosY(0)
	, m_rotateScale(0.0)
{
	this->renderOrder = OBJECT_ORDER;
	m_pMouseManager = MouseManager::GetInstance();
	m_pStageManager = StageManager::GetInstance();
}

SpinningWheel::SpinningWheel(const int objectNum, const std::string& objectName, const double posX, const double posY)
	: Object(objectNum, objectName, posX, posY)
	, m_PosX((float)posX)
	, m_PosY((float)posY)
	, m_rotateScale(0.0)
{
	this->renderOrder = OBJECT_ORDER;
	m_pMouseManager = MouseManager::GetInstance();
	m_pStageManager = StageManager::GetInstance();
}

SpinningWheel::~SpinningWheel()
{

}

void SpinningWheel::UpdateObject()
{
}

void SpinningWheel::RenderObject()
{
	D2DEngine::GetInstance()->DrawSprite(eObjectDefine::SpinningWheel, m_PosX, m_PosY, (float)this->m_rotateScale);
	
	/// 회전 속도 (디버그용 표시)
	//D2DEngine::GetInstance()->DrawText(
	//	100 + 200,
	//	100,
	//	(int)m_rotateScale
	//);
}

bool SpinningWheel::GetMoveState()
{
	return true;
}

double SpinningWheel::GetRotateScale()
{
	return this->m_rotateScale;
}

void SpinningWheel::SetRotateScale(double scale)
{
	this->m_rotateScale = scale;
}
