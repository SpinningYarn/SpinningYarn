#include "HowtoPlay.h"
#include "MouseManager.h"
#include "../D2DEngine/D2DEngine.h"


HowtoPlay::HowtoPlay(const int& objectNum, std::string objectName)
	: Object(objectNum, objectName, 0, 0), ScreenOn(false)
	,Count(0)
{
	this->renderOrder = SHOP_ORDER + 1;

	m_pMouseManager = MouseManager::GetInstance();
}

HowtoPlay::HowtoPlay(int objectNum, std::string objectName, double posX, double posY)
	: Object(objectNum, objectName, posX, posY), ScreenOn(false)
	,Count(0)
{
	this->renderOrder = SHOP_ORDER + 1;

	m_pMouseManager = MouseManager::GetInstance();
}

HowtoPlay::~HowtoPlay()
{
}

void HowtoPlay::UpdateObject()
{
	ExitWindow();
	ChangePages();
}

void HowtoPlay::RenderObject()
{
	DrawHowtoPlay();
	Pages();

}


void HowtoPlay::DrawHowtoPlay()
{
	if (ScreenOn == true)
	{
		D2DEngine::GetInstance()->DrawSprite(eObjectDefine::HOWTOPLAY, 260, 39);
		D2DEngine::GetInstance()->DrawSprite(eObjectDefine::HTPLEFT, 810, 927);
		D2DEngine::GetInstance()->DrawSprite(eObjectDefine::HTPRIGHT, 1043, 927);
		D2DEngine::GetInstance()->DrawSprite(eObjectDefine::HTPEND, 1515, 55);


	}
}

void HowtoPlay::ExitWindow()
{

	if (m_pMouseManager->GetLeftOneDownClickState() == true
		&& 1515 <= m_pMouseManager->GetXPos()
		&& 1615 >= m_pMouseManager->GetXPos()
		&& 55 <= m_pMouseManager->GetYPos()
		&& 155 >= m_pMouseManager->GetYPos()
		&& ScreenOn == true)
	{
		ScreenOn = false;
	}

}

void HowtoPlay::ChangePages()
{
	if (ScreenOn == true && Count < 3)
	{
		if (m_pMouseManager->GetLeftOneDownClickState() == true
			&& 1043 <= m_pMouseManager->GetXPos()
			&& 1107 >= m_pMouseManager->GetXPos()
			&& 927 <= m_pMouseManager->GetYPos()
			&& 1015 >= m_pMouseManager->GetYPos()
			&& ScreenOn == true)
		{
			Count++;
		}
		if (m_pMouseManager->GetLeftOneDownClickState() == true
			&& 810 <= m_pMouseManager->GetXPos()
			&& 874 >= m_pMouseManager->GetXPos()
			&& 927 <= m_pMouseManager->GetYPos()
			&& 1015 >= m_pMouseManager->GetYPos()
			&& ScreenOn == true)
		{
			Count--;
		}
		
	}
}

void HowtoPlay::Pages()
{
	if (ScreenOn == true)
	{
		if (Count == 0)
		{
			D2DEngine::GetInstance()->DrawSprite(eObjectDefine::GAMERULE1, 260, 39);

		}
		if (Count == 1)
		{
			D2DEngine::GetInstance()->DrawSprite(eObjectDefine::GAMERULE2, 260, 39);

		}
		if (Count == 2)
		{
			D2DEngine::GetInstance()->DrawSprite(eObjectDefine::GAMERULE3, 260, 39);

		}
		if (Count >= 3)
		{
			Count = 0;
		}
		if (Count < 0)
		{
			Count = 2;
		}
	}
}