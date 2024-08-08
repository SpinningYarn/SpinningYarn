#include "MainBackground.h"
#include "../D2DEngine/D2DEngine.h"

MainBackground::MainBackground(const int& objectNum, std::string objectName)
	: Object(objectNum, objectName, 0, 0), m_ScreenSizeX(1920), m_ScreenSizeY(1080),
	m_exitButtonSrcX(13), m_exitButtonSrcY(968), m_exitButtonDstX(113), m_exitButtonDstY(1068)
{
	this->renderOrder = BACKGROUND_ORDER;		// 제일 아래로 깔리게
}

MainBackground::MainBackground(int objectNum, std::string objectName, double posX, double posY)
	: Object(objectNum, objectName, posX, posY), m_ScreenSizeX(1920), m_ScreenSizeY(1080),
	m_exitButtonSrcX(13), m_exitButtonSrcY(968), m_exitButtonDstX(113), m_exitButtonDstY(1068)
{
	this->renderOrder = BACKGROUND_ORDER;		// 제일 아래로 깔리게
}

MainBackground::~MainBackground()
{
}

void MainBackground::UpdateObject()
{

}

void MainBackground::RenderObject()
{
	D2DEngine::GetInstance()->DrawSprite(eObjectDefine::MainScreen, 0, 0);
	D2DEngine::GetInstance()->DrawSprite(eObjectDefine::MAIN_EXIT, m_exitButtonSrcX, m_exitButtonSrcY);
}
