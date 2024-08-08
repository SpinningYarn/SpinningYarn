#include "TestWool.h"
#include "../D2DEngine/D2DEngine.h"
#include "MouseManager.h"



TestWool::TestWool(const int& objectNum, std::string objectName)
	:IWool(objectNum, objectName, 30, 30, 30, 30,30, 1, false, eObjectDefine::ANGORA, WoolSpcAbility::NONE, WoolSpcAbility::NONE),
	returnItemBox(false) ,returnStatBox(false)
{
	m_pMouseManager = MouseManager::GetInstance();

}

TestWool::TestWool(int objectNum, std::string objectName, double posX, double posY)
	:IWool(objectNum, objectName, posX, posY, 30, 30, 30, 30,30, 1, false, eObjectDefine::ANGORA, WoolSpcAbility::NONE, WoolSpcAbility::NONE),
	returnItemBox(false), returnStatBox(false)
{
	m_pMouseManager = MouseManager::GetInstance();
}

TestWool::~TestWool()
{
}

void TestWool::UpdateObject()
{
	SendImage();
	SendStat();
}

void TestWool::RenderObject()
{
	//D2DEngine::GetInstance()->DrawRect(GetPositionX(), GetPositionY(), GetPositionX() + 100, GetPositionY() + 100);
	
	/*if (SendImage() == true)
	{
		D2DEngine::GetInstance()->DrawRect(100, 100, 200, 200);
	}*/

}

bool TestWool::SendImage()
{
	if (m_pMouseManager->GetLeftButtonDownState() == true
		&& GetPositionX() <= m_pMouseManager->GetXPos()
		&& GetPositionX() + 100 >= m_pMouseManager->GetXPos()
		&& GetPositionY() <= m_pMouseManager->GetYPos()
		&& GetPositionY() + 100 >= m_pMouseManager->GetYPos())
	{
		returnItemBox = true;
		return returnItemBox;
	}
	else return false;
}

bool TestWool::SendStat()
{
	if (m_pMouseManager->GetLeftButtonDownState() == true
		&& GetPositionX() <= m_pMouseManager->GetXPos()
		&& GetPositionX() + 100 >= m_pMouseManager->GetXPos()
		&& GetPositionY() <= m_pMouseManager->GetYPos()
		&& GetPositionY() + 100 >= m_pMouseManager->GetYPos())
	{
		//mouseCount++;
		returnStatBox = true;
		return returnStatBox;
	}
	//else if (mouseCount > 0)
	//{
	//	return true;
	//}	
}


