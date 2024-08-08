#include "StatBox2.h"

#include "IWool.h"
#include "SceneManager.h"
#include "MouseManager.h"
#include "../D2DEngine/D2DEngine.h"


StatBox2::StatBox2(const int objectNum, std::string objectName)
	:Object(objectNum, objectName), targetWarmth2(0), targetAbsoptivity2(0), targetAeration2(0), targetPrice2(0), targetQuantity2(0)
	, MouseCount2(1), returnTestWool2(false), m_MouseClickOnce(true)
	, changeBox(false), InactivateButton2(false)
{
	this->renderOrder = OBJECT_ORDER + 1;

	this->renderOrder = 50;
	m_pMouseManager = MouseManager::GetInstance();
	//AverageCount2 = 1;
}

StatBox2::StatBox2(const int objectNum, const std::string& objectName, const double posX, const double posY)
	:Object(objectNum, objectName, posX, posY), targetWarmth2(0), targetAbsoptivity2(0), targetAeration2(0), targetPrice2(0), targetQuantity2(0)
	, MouseCount2(1), returnTestWool2(false), m_MouseClickOnce(true)
	, changeBox(false), InactivateButton2(false)
{
	this->renderOrder = OBJECT_ORDER + 1;

	m_pMouseManager = MouseManager::GetInstance();
}

StatBox2::~StatBox2()
{
}

void StatBox2::UpdateObject()
{
	PlusMinus2();													// 오브젝트의 수치값

	if (returnTestWool2 == true
		&& m_pMouseManager->GetRightButtonDownState() == true
		&& 283 <= m_pMouseManager->GetXPos()
		&& 411 >= m_pMouseManager->GetXPos()
		&& 560 <= m_pMouseManager->GetYPos()
		&& 688 >= m_pMouseManager->GetYPos())
	{
		EmptyStatBox();
	}
	SetEmpty();
}

void StatBox2::RenderObject()
{
	//D2DEngine::GetInstance()->DrawRect(529, 800, 559, 830);			// 증가버튼
	//D2DEngine::GetInstance()->DrawRect(470, 800, 500, 830);			// 감소버튼

	D2DEngine::GetInstance()->DrawSprite(eObjectDefine::STATBOX, 283, 560);
	if (returnTestWool2 == true)
	{

	//	D2DEngine::GetInstance()->DrawRect(283, 560, 411, 688);		// 이미지파일

		D2DEngine::GetInstance()->DrawSprite(eOD, 298, 575);
	}
	if (returnTestWool2 == true && this->targetPrice2 != 0)
	{
		eObjectDefine newEOD = eObjectDefine::EMPTYEMPTY;

		switch (eOD)
		{
			case eObjectDefine::SPIDERWEB:
			{
				newEOD = eObjectDefine::SPIDERWEB_EMPTY;
				break;
			}
			case eObjectDefine::LAMBSWOOL:
			{
				newEOD = eObjectDefine::LAMBSWOOL_EMPTY;
				break;
			}
			case eObjectDefine::COTTON:
			{
				newEOD = eObjectDefine::COTTON_EMPTY;
				break;
			}
			case eObjectDefine::HEMP:
			{
				newEOD = eObjectDefine::HEMP_EMPTY;
				break;
			}
			case eObjectDefine::ANGORA:
			{
				newEOD = eObjectDefine::ANGORA_EMPTY;
				break;
			}
			case eObjectDefine::CASHMERE:
			{
				newEOD = eObjectDefine::CASHMERE_EMPTY;
				break;
			}

			default:
				break;
		}

		D2DEngine::GetInstance()->DrawSprite(newEOD, 395, 627);
		D2DEngine::GetInstance()->DrawTextInt(370, 709, this->targetWarmth2 * (MouseCount2));
		D2DEngine::GetInstance()->DrawTextInt(370, 743, this->targetAbsoptivity2 * (MouseCount2));
		D2DEngine::GetInstance()->DrawTextInt(370, 776, this->targetAeration2 * (MouseCount2));
		D2DEngine::GetInstance()->DrawTextInt(370, 810, this->targetPrice2 * (MouseCount2));
		D2DEngine::GetInstance()->DrawTextInt(466, 810, this->targetQuantity2 * (MouseCount2));
		// 오브젝트의 수치값
	}
}


void StatBox2::PlusMinus2()
{
	if (InactivateButton2 == false)
	{ // 특정 버튼을 누르면 울의 수치가 증가한다
		if (m_pMouseManager->GetLeftButtonDownState() == true
			&& m_MouseClickOnce == true
			&& 529 <= m_pMouseManager->GetXPos()
			&& 800 <= m_pMouseManager->GetYPos()
			&& 559 >= m_pMouseManager->GetXPos()
			&& 830 >= m_pMouseManager->GetYPos())
		{
			MouseCount2++;
			m_MouseClickOnce = false;
		}

		if (m_pMouseManager->GetLeftButtonUpState() == true
			&& m_MouseClickOnce == false
			&& 529 <= m_pMouseManager->GetXPos()
			&& 800 <= m_pMouseManager->GetYPos()
			&& 559 >= m_pMouseManager->GetXPos()
			&& 830 >= m_pMouseManager->GetYPos())
		{
			m_MouseClickOnce = true;
		}
	}
	// 특정 버튼을 누르면 울의 수치가 감소한다
	if (m_pMouseManager->GetLeftButtonDownState() == true
		&& m_MouseClickOnce == true
		&& 470 <= m_pMouseManager->GetXPos()
		&& 800 <= m_pMouseManager->GetYPos()
		&& 500 >= m_pMouseManager->GetXPos()
		&& 830 >= m_pMouseManager->GetYPos())
	{
		MouseCount2--;
		m_MouseClickOnce = false;
	}

	if (m_pMouseManager->GetLeftButtonUpState() == true
		&& m_MouseClickOnce == false
		&& 470 <= m_pMouseManager->GetXPos()
		&& 800 <= m_pMouseManager->GetYPos()
		&& 500 >= m_pMouseManager->GetXPos()
		&& 830 >= m_pMouseManager->GetYPos())
	{
		m_MouseClickOnce = true;
	}
}

void StatBox2::UpdateStat2(IWool* targetWool)
{
	if (targetWool == nullptr)
	{
		EmptyStatBox();
		return;
	}

	this->targetWarmth2 = targetWool->m_Warmth;
	this->targetAbsoptivity2 = targetWool->m_Durability;
	this->targetAeration2 = targetWool->m_Aeration;
	this->targetPrice2 = targetWool->m_Price;
	this->targetQuantity2 = targetWool->m_Quantity;

	eOD = targetWool->GetObjectDefine();

	m_spcAbil1 = targetWool->m_abil1;
	m_spcAbil2 = targetWool->m_abil2;
}

void StatBox2::EmptyStatBox()
{
	UnDo2();

	this->targetWarmth2 = 0;
	this->targetAbsoptivity2 = 0;
	this->targetAeration2 = 0;
	this->targetPrice2 = 0;
	this->targetQuantity2 = 0;
}

void StatBox2::SetEmpty()
{
	if (this->targetWarmth2 + this->targetAbsoptivity2 + this->targetAeration2 + this->targetPrice2 + this->targetQuantity2 > 0)
	{
		this->returnTestWool2 = true;
	}
	else
	{
		this->returnTestWool2 = false;
	}
}

bool StatBox2::IsEmpty()
{
	if (this->targetWarmth2 + this->targetAbsoptivity2 + this->targetAeration2 + this->targetPrice2 + this->targetQuantity2 > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//void StatBox2::GetStat2()
//{
//	returnWoolStat2 = true;
//}
//
//void StatBox2::GetImage2()
//{
//	returnTestWool2 = true;
//}

void StatBox2::UnDo2()
{
	returnTestWool2 = false;

	changeBox = false;

	MouseCount2 = 1;
}
