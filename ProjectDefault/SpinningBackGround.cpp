#include "SpinningBackGround.h"
#include "../D2DEngine//D2DEngine.h"
#include "TimerManager.h"
#include "MouseManager.h"

SpinningBackGround::SpinningBackGround(const int objectNum, std::string objectName)
	: Object(objectNum, objectName, 0, 0), m_ScreenSizeX(1920), m_ScreenSizeY(1080)
{
	this->renderOrder = BACKGROUND_ORDER;
}

SpinningBackGround::SpinningBackGround(const int objectNum, const std::string& objectName, const double posX, const double posY)
	: Object(objectNum, objectName, posX, posY), m_ScreenSizeX(1920), m_ScreenSizeY(1080)
{
	this->renderOrder = BACKGROUND_ORDER;		// 제일 아래로 깔리게
}

SpinningBackGround::~SpinningBackGround()
{

}

void SpinningBackGround::UpdateObject()
{
}

void SpinningBackGround::RenderObject()
{
	D2DEngine::GetInstance()->DrawSprite(eObjectDefine::SpinningMainScreen, 0, 0);
}
