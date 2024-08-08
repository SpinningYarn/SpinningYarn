#include "../D2DEngine/D2DEngine.h"
#include "StartButton.h"
#include "KeyManager.h"
#include "MouseManager.h"
#include "Dantto.h"

StartButton::StartButton(const int objectNum, std::string objectName)
	: Object(objectNum, objectName, 342, 453), m_ButtonSizeX(128), m_ButtonSizeY(64), m_DrawFlag(true)
{
	this->renderOrder = OBJECT_ORDER;
}

StartButton::StartButton(const int objectNum, const std::string& objectName, const double posX, const double posY)
	: Object(objectNum, objectName, posX, posY), m_ButtonSizeX(128), m_ButtonSizeY(64), m_DrawFlag(true)
{
	this->renderOrder = OBJECT_ORDER;
}

StartButton::~StartButton()
{

}

void StartButton::UpdateObject()
{

}

void StartButton::RenderObject() 
{
	if (m_DrawFlag == true)
	{
		D2DEngine::GetInstance()->DrawSprite(eObjectDefine::StartButton, GetPositionX(), GetPositionY());
	}
}

bool StartButton::RetryButtonClick()
{
	if (KeyManager::GetInstance().GetKnittingKey() == SPACE)
	{
		return true;
	}
	else return false;
}

/// 마우스 매니저에서 nullptr 오류 발생하는 중 ...
bool StartButton::GameStartButtonClick(Dantto* p_Dantto)
{
	if (MouseManager::GetInstance()->GetLeftOneDownClickState() == true &&
		MouseManager::GetInstance()->GetXPos() >= GetPositionX() &&
		MouseManager::GetInstance()->GetXPos() <= GetPositionX() + m_ButtonSizeX &&
		MouseManager::GetInstance()->GetYPos() >= GetPositionY() &&
		MouseManager::GetInstance()->GetYPos() <= GetPositionY() + m_ButtonSizeY &&
		p_Dantto->GetEnterFlag() == true
		)
	{
		return true;
	}
	else
		return false;
}

bool StartButton::GetDrawFlag()
{
	return m_DrawFlag;
}

void StartButton::SetDrawFlag(bool OX)
{
	m_DrawFlag = OX;
}
