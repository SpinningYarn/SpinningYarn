#include "TestWool2.h"
#include "../D2DEngine/D2DEngine.h"
#include "MouseManager.h"

TestWool2::TestWool2(const int& objectNum, std::string objectName)
	:IWool(objectNum, objectName, 35, 20, 50, 40, 40, 1, false, eObjectDefine::ANGORA, WoolSpcAbility::NONE, WoolSpcAbility::NONE),
	returnItemBox2(false), returnStatBox2(false)
{
	m_pMouseManager = MouseManager::GetInstance();
}

TestWool2::TestWool2(int objectNum, std::string objectName, double posX, double posY)
	:IWool(objectNum, objectName,posX, posY, 35, 20, 50, 40, 40, 1, false, eObjectDefine::ANGORA, WoolSpcAbility::NONE, WoolSpcAbility::NONE),
	returnItemBox2(false), returnStatBox2(false)
{
	m_pMouseManager = MouseManager::GetInstance();
}

TestWool2::~TestWool2()
{
}

void TestWool2::UpdateObject()
{
	SendImage2();
	SendStat2();
}

void TestWool2::RenderObject()
{
	D2DEngine::GetInstance()->DrawRect(GetPositionX(), GetPositionY(), GetPositionX() + 100, GetPositionY() + 100);
}

bool TestWool2::SendImage2()
{
	if (m_pMouseManager->GetLeftButtonDownState() == true
		&& GetPositionX() <= m_pMouseManager->GetXPos()
		&& GetPositionX() + 100 >= m_pMouseManager->GetXPos()
		&& GetPositionY() <= m_pMouseManager->GetYPos()
		&& GetPositionY() + 100 >= m_pMouseManager->GetYPos())
	{
		returnItemBox2 = true;
		return returnItemBox2;
	}
	else return false;
}

bool TestWool2::SendStat2()
{
	if (m_pMouseManager->GetLeftButtonDownState() == true
		&& GetPositionX() <= m_pMouseManager->GetXPos()
		&& GetPositionX() + 100 >= m_pMouseManager->GetXPos()
		&& GetPositionY() <= m_pMouseManager->GetYPos()
		&& GetPositionY() + 100 >= m_pMouseManager->GetYPos())
	{
		//mouseCount++;
		returnStatBox2 = true;
		return returnStatBox2;
	}
}
