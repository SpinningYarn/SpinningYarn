#include "AverageBackground.h"
#include "../D2DEngine/D2DEngine.h"

AverageBackground::AverageBackground(const int& objectNum, std::string objectName)
	: Object(objectNum, objectName, 0, 0), m_ScreenSizeX(1920), m_ScreenSizeY(1080)
{
	this->renderOrder = BACKGROUND_ORDER;		// 제일 아래로 깔리게
}

AverageBackground::AverageBackground(int objectNum, std::string objectName, double posX, double posY)
	: Object(objectNum, objectName, posX, posY), m_ScreenSizeX(1920), m_ScreenSizeY(1080)
{
	this->renderOrder = BACKGROUND_ORDER;		// 제일 아래로 깔리게
}

AverageBackground::~AverageBackground()
{
}

void AverageBackground::UpdateObject()
{
}

void AverageBackground::RenderObject()
{
	D2DEngine::GetInstance()->DrawSprite(eObjectDefine::SpinningMainScreen, 0, 0);
	D2DEngine::GetInstance()->DrawSprite(eObjectDefine::SpinningWheel, 872, 222);
}
